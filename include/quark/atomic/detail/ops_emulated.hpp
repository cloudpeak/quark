/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.quark.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_emulated.hpp
 *
 * This header contains lockpool-based implementation of the \c operations template.
 */

#ifndef QUARK_ATOMIC_DETAIL_OPS_EMULATED_HPP_INCLUDED_
#define QUARK_ATOMIC_DETAIL_OPS_EMULATED_HPP_INCLUDED_

#include <cstddef>
#include <quark/memory_order.hpp>
#include <quark/atomic/detail/config.hpp>
#include <quark/atomic/detail/storage_type.hpp>
#include <quark/atomic/detail/operations_fwd.hpp>
#include <quark/atomic/detail/lockpool.hpp>
#include <quark/atomic/capabilities.hpp>

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace quark {
namespace atomics {
namespace detail {

template< typename T >
struct emulated_operations
{
    typedef T storage_type;

    static QUARK_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order) QUARK_NOEXCEPT
    {
        lockpool::scoped_lock lock(&storage);
        const_cast< storage_type& >(storage) = v;
    }

    static QUARK_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order) QUARK_NOEXCEPT
    {
        lockpool::scoped_lock lock(&storage);
        return const_cast< storage_type const& >(storage);
    }

    static QUARK_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order) QUARK_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        lockpool::scoped_lock lock(&storage);
        storage_type old_val = s;
        s += v;
        return old_val;
    }

    static QUARK_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order) QUARK_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        lockpool::scoped_lock lock(&storage);
        storage_type old_val = s;
        s -= v;
        return old_val;
    }

    static QUARK_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) QUARK_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        lockpool::scoped_lock lock(&storage);
        storage_type old_val = s;
        s = v;
        return old_val;
    }

    static QUARK_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) QUARK_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        lockpool::scoped_lock lock(&storage);
        storage_type old_val = s;
        const bool res = old_val == expected;
        if (res)
            s = desired;
        expected = old_val;

        return res;
    }

    static QUARK_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) QUARK_NOEXCEPT
    {
        // Note: This function is the exact copy of compare_exchange_strong. The reason we're not just forwarding the call
        // is that MSVC-12 ICEs in this case.
        storage_type& s = const_cast< storage_type& >(storage);
        lockpool::scoped_lock lock(&storage);
        storage_type old_val = s;
        const bool res = old_val == expected;
        if (res)
            s = desired;
        expected = old_val;

        return res;
    }

    static QUARK_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order) QUARK_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        lockpool::scoped_lock lock(&storage);
        storage_type old_val = s;
        s &= v;
        return old_val;
    }

    static QUARK_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order) QUARK_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        lockpool::scoped_lock lock(&storage);
        storage_type old_val = s;
        s |= v;
        return old_val;
    }

    static QUARK_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order) QUARK_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        lockpool::scoped_lock lock(&storage);
        storage_type old_val = s;
        s ^= v;
        return old_val;
    }

    static QUARK_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) QUARK_NOEXCEPT
    {
        return !!exchange(storage, (storage_type)1, order);
    }

    static QUARK_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) QUARK_NOEXCEPT
    {
        store(storage, (storage_type)0, order);
    }

    static QUARK_FORCEINLINE bool is_lock_free(storage_type const volatile&) QUARK_NOEXCEPT
    {
        return false;
    }
};

template< std::size_t Size, bool Signed >
struct operations :
    public emulated_operations< typename make_storage_type< Size, Signed >::type >
{
    typedef typename make_storage_type< Size, Signed >::aligned aligned_storage_type;
};

} // namespace detail
} // namespace atomics
} // namespace quark

#endif // QUARK_ATOMIC_DETAIL_OPS_EMULATED_HPP_INCLUDED_
