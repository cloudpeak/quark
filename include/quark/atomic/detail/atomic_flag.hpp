/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.quark.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/atomic_flag.hpp
 *
 * This header contains interface definition of \c atomic_flag.
 */

#ifndef QUARK_ATOMIC_DETAIL_ATOMIC_FLAG_HPP_INCLUDED_
#define QUARK_ATOMIC_DETAIL_ATOMIC_FLAG_HPP_INCLUDED_

#include <quark/assert.hpp>
#include <quark/memory_order.hpp>
#include <quark/atomic/detail/config.hpp>
#include <quark/atomic/detail/operations_lockfree.hpp>

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

/*
 * IMPLEMENTATION NOTE: All interface functions MUST be declared with QUARK_FORCEINLINE,
 *                      see comment for convert_memory_order_to_gcc in ops_gcc_atomic.hpp.
 */

namespace quark {
namespace atomics {

#if defined(QUARK_NO_CXX11_CONSTEXPR) || defined(QUARK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX)
#define QUARK_ATOMIC_NO_ATOMIC_FLAG_INIT
#else
#define QUARK_ATOMIC_FLAG_INIT {}
#endif

struct atomic_flag
{
    typedef atomics::detail::operations< 1u, false > operations;
    typedef operations::storage_type storage_type;

    operations::aligned_storage_type m_storage;

    QUARK_FORCEINLINE QUARK_CONSTEXPR atomic_flag() QUARK_NOEXCEPT : m_storage(0)
    {
    }

    QUARK_FORCEINLINE bool test_and_set(memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return operations::test_and_set(m_storage.value, order);
    }

    QUARK_FORCEINLINE void clear(memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(order != memory_order_acquire);
        QUARK_ASSERT(order != memory_order_acq_rel);
        operations::clear(m_storage.value, order);
    }

    QUARK_DELETED_FUNCTION(atomic_flag(atomic_flag const&))
    QUARK_DELETED_FUNCTION(atomic_flag& operator= (atomic_flag const&))
};

} // namespace atomics
} // namespace quark

#endif // QUARK_ATOMIC_DETAIL_ATOMIC_FLAG_HPP_INCLUDED_
