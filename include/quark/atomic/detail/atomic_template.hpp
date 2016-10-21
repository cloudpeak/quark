/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.quark.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/atomic_template.hpp
 *
 * This header contains interface definition of \c atomic template.
 */

#ifndef QUARK_ATOMIC_DETAIL_ATOMIC_TEMPLATE_HPP_INCLUDED_
#define QUARK_ATOMIC_DETAIL_ATOMIC_TEMPLATE_HPP_INCLUDED_

#include <cstddef>
#include <quark/cstdint.hpp>
#include <quark/assert.hpp>
#include <quark/fixups.hpp>
#include <quark/atomic/detail/config.hpp>
#include <quark/atomic/detail/bitwise_cast.hpp>
#include <quark/atomic/detail/operations_fwd.hpp>

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(QUARK_MSVC)
#pragma warning(push)
// 'quark::atomics::atomic<T>' : multiple assignment operators specified
#pragma warning(disable: 4522)
#endif

/*
 * IMPLEMENTATION NOTE: All interface functions MUST be declared with QUARK_FORCEINLINE,
 *                      see comment for convert_memory_order_to_gcc in ops_gcc_atomic.hpp.
 */

namespace quark {
namespace atomics {
namespace detail {

QUARK_FORCEINLINE QUARK_CONSTEXPR memory_order deduce_failure_order(memory_order order) QUARK_NOEXCEPT
{
    return order == memory_order_acq_rel ? memory_order_acquire : (order == memory_order_release ? memory_order_relaxed : order);
}

QUARK_FORCEINLINE QUARK_CONSTEXPR bool cas_failure_order_must_not_be_stronger_than_success_order(memory_order success_order, memory_order failure_order) QUARK_NOEXCEPT
{
    // 15 == (memory_order_seq_cst | memory_order_consume), see memory_order.hpp
    // Given the enum values we can test the strength of memory order requirements with this single condition.
    return (failure_order & 15u) <= (success_order & 15u);
}

template< typename T, bool IsInt = quark::is_integral< T >::value >
struct classify
{
    typedef void type;
};

template< typename T >
struct classify< T, true > { typedef int type; };

template< typename T >
struct classify< T*, false > { typedef void* type; };

template< typename T, typename Kind >
class base_atomic;

//! Implementation for integers
template< typename T >
class base_atomic< T, int >
{
private:
    typedef T value_type;
    typedef T difference_type;
    typedef atomics::detail::operations< storage_size_of< value_type >::value, quark::is_signed< T >::value > operations;

protected:
    typedef value_type value_arg_type;

public:
    typedef typename operations::storage_type storage_type;

protected:
    typename operations::aligned_storage_type m_storage;

public:
    QUARK_DEFAULTED_FUNCTION(base_atomic(), {})
    QUARK_CONSTEXPR explicit base_atomic(value_type v) QUARK_NOEXCEPT : m_storage(v) {}

    QUARK_FORCEINLINE void store(value_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(order != memory_order_consume);
        QUARK_ASSERT(order != memory_order_acquire);
        QUARK_ASSERT(order != memory_order_acq_rel);

        operations::store(m_storage.value, static_cast< storage_type >(v), order);
    }

    QUARK_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(order != memory_order_release);
        QUARK_ASSERT(order != memory_order_acq_rel);

        return static_cast< value_type >(operations::load(m_storage.value, order));
    }

    QUARK_FORCEINLINE value_type fetch_add(difference_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return static_cast< value_type >(operations::fetch_add(m_storage.value, static_cast< storage_type >(v), order));
    }

    QUARK_FORCEINLINE value_type fetch_sub(difference_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return static_cast< value_type >(operations::fetch_sub(m_storage.value, static_cast< storage_type >(v), order));
    }

    QUARK_FORCEINLINE value_type exchange(value_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return static_cast< value_type >(operations::exchange(m_storage.value, static_cast< storage_type >(v), order));
    }

    QUARK_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_type desired, memory_order success_order, memory_order failure_order) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(failure_order != memory_order_release);
        QUARK_ASSERT(failure_order != memory_order_acq_rel);
        QUARK_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_strong(m_storage.value, old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = static_cast< value_type >(old_value);
        return res;
    }

    QUARK_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_type desired, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    QUARK_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_type desired, memory_order success_order, memory_order failure_order) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(failure_order != memory_order_release);
        QUARK_ASSERT(failure_order != memory_order_acq_rel);
        QUARK_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_weak(m_storage.value, old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = static_cast< value_type >(old_value);
        return res;
    }

    QUARK_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_type desired, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    QUARK_FORCEINLINE value_type fetch_and(value_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return static_cast< value_type >(operations::fetch_and(m_storage.value, static_cast< storage_type >(v), order));
    }

    QUARK_FORCEINLINE value_type fetch_or(value_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return static_cast< value_type >(operations::fetch_or(m_storage.value, static_cast< storage_type >(v), order));
    }

    QUARK_FORCEINLINE value_type fetch_xor(value_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return static_cast< value_type >(operations::fetch_xor(m_storage.value, static_cast< storage_type >(v), order));
    }

    QUARK_FORCEINLINE bool is_lock_free() const volatile QUARK_NOEXCEPT
    {
        return operations::is_lock_free(m_storage.value);
    }

    QUARK_FORCEINLINE value_type operator++(int) volatile QUARK_NOEXCEPT
    {
        return fetch_add(1);
    }

    QUARK_FORCEINLINE value_type operator++() volatile QUARK_NOEXCEPT
    {
        return fetch_add(1) + 1;
    }

    QUARK_FORCEINLINE value_type operator--(int) volatile QUARK_NOEXCEPT
    {
        return fetch_sub(1);
    }

    QUARK_FORCEINLINE value_type operator--() volatile QUARK_NOEXCEPT
    {
        return fetch_sub(1) - 1;
    }

    QUARK_FORCEINLINE value_type operator+=(difference_type v) volatile QUARK_NOEXCEPT
    {
        return fetch_add(v) + v;
    }

    QUARK_FORCEINLINE value_type operator-=(difference_type v) volatile QUARK_NOEXCEPT
    {
        return fetch_sub(v) - v;
    }

    QUARK_FORCEINLINE value_type operator&=(value_type v) volatile QUARK_NOEXCEPT
    {
        return fetch_and(v) & v;
    }

    QUARK_FORCEINLINE value_type operator|=(value_type v) volatile QUARK_NOEXCEPT
    {
        return fetch_or(v) | v;
    }

    QUARK_FORCEINLINE value_type operator^=(value_type v) volatile QUARK_NOEXCEPT
    {
        return fetch_xor(v) ^ v;
    }

    QUARK_DELETED_FUNCTION(base_atomic(base_atomic const&))
    QUARK_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))
};

//! Implementation for bool
template< >
class base_atomic< bool, int >
{
private:
    typedef bool value_type;
    typedef atomics::detail::operations< 1u, false > operations;

protected:
    typedef value_type value_arg_type;

public:
    typedef operations::storage_type storage_type;

protected:
    operations::aligned_storage_type m_storage;

public:
    QUARK_DEFAULTED_FUNCTION(base_atomic(), {})
    QUARK_CONSTEXPR explicit base_atomic(value_type v) QUARK_NOEXCEPT : m_storage(v) {}

    QUARK_FORCEINLINE void store(value_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(order != memory_order_consume);
        QUARK_ASSERT(order != memory_order_acquire);
        QUARK_ASSERT(order != memory_order_acq_rel);

        operations::store(m_storage.value, static_cast< storage_type >(v), order);
    }

    QUARK_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(order != memory_order_release);
        QUARK_ASSERT(order != memory_order_acq_rel);

        return !!operations::load(m_storage.value, order);
    }

    QUARK_FORCEINLINE value_type exchange(value_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return !!operations::exchange(m_storage.value, static_cast< storage_type >(v), order);
    }

    QUARK_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_type desired, memory_order success_order, memory_order failure_order) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(failure_order != memory_order_release);
        QUARK_ASSERT(failure_order != memory_order_acq_rel);
        QUARK_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_strong(m_storage.value, old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = !!old_value;
        return res;
    }

    QUARK_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_type desired, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    QUARK_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_type desired, memory_order success_order, memory_order failure_order) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(failure_order != memory_order_release);
        QUARK_ASSERT(failure_order != memory_order_acq_rel);
        QUARK_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_weak(m_storage.value, old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = !!old_value;
        return res;
    }

    QUARK_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_type desired, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    QUARK_FORCEINLINE bool is_lock_free() const volatile QUARK_NOEXCEPT
    {
        return operations::is_lock_free(m_storage.value);
    }

    QUARK_DELETED_FUNCTION(base_atomic(base_atomic const&))
    QUARK_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))
};


//! Implementation for user-defined types, such as structs and enums
template< typename T >
class base_atomic< T, void >
{
private:
    typedef T value_type;
    typedef atomics::detail::operations< storage_size_of< value_type >::value, false > operations;

protected:
    typedef value_type const& value_arg_type;

public:
    typedef typename operations::storage_type storage_type;

protected:
    typename operations::aligned_storage_type m_storage;

public:
    QUARK_FORCEINLINE explicit base_atomic(value_type const& v = value_type()) QUARK_NOEXCEPT : m_storage(atomics::detail::bitwise_cast< storage_type >(v))
    {
    }

    QUARK_FORCEINLINE void store(value_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(order != memory_order_consume);
        QUARK_ASSERT(order != memory_order_acquire);
        QUARK_ASSERT(order != memory_order_acq_rel);

        operations::store(m_storage.value, atomics::detail::bitwise_cast< storage_type >(v), order);
    }

    QUARK_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(order != memory_order_release);
        QUARK_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(operations::load(m_storage.value, order));
    }

    QUARK_FORCEINLINE value_type exchange(value_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(operations::exchange(m_storage.value, atomics::detail::bitwise_cast< storage_type >(v), order));
    }

    QUARK_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_type desired, memory_order success_order, memory_order failure_order) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(failure_order != memory_order_release);
        QUARK_ASSERT(failure_order != memory_order_acq_rel);
        QUARK_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_strong(m_storage.value, old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }

    QUARK_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_type desired, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    QUARK_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_type desired, memory_order success_order, memory_order failure_order) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(failure_order != memory_order_release);
        QUARK_ASSERT(failure_order != memory_order_acq_rel);
        QUARK_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_weak(m_storage.value, old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }

    QUARK_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_type desired, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    QUARK_FORCEINLINE bool is_lock_free() const volatile QUARK_NOEXCEPT
    {
        return operations::is_lock_free(m_storage.value);
    }

    QUARK_DELETED_FUNCTION(base_atomic(base_atomic const&))
    QUARK_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))
};


//! Implementation for pointers
template< typename T >
class base_atomic< T*, void* >
{
private:
    typedef T* value_type;
    typedef std::ptrdiff_t difference_type;
    typedef atomics::detail::operations< storage_size_of< value_type >::value, false > operations;

protected:
    typedef value_type value_arg_type;

public:
    typedef typename operations::storage_type storage_type;

protected:
    typename operations::aligned_storage_type m_storage;

public:
    QUARK_DEFAULTED_FUNCTION(base_atomic(), {})
    QUARK_FORCEINLINE explicit base_atomic(value_type const& v) QUARK_NOEXCEPT : m_storage(atomics::detail::bitwise_cast< storage_type >(v))
    {
    }

    QUARK_FORCEINLINE void store(value_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(order != memory_order_consume);
        QUARK_ASSERT(order != memory_order_acquire);
        QUARK_ASSERT(order != memory_order_acq_rel);

        operations::store(m_storage.value, atomics::detail::bitwise_cast< storage_type >(v), order);
    }

    QUARK_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(order != memory_order_release);
        QUARK_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(operations::load(m_storage.value, order));
    }

    QUARK_FORCEINLINE value_type fetch_add(difference_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(operations::fetch_add(m_storage.value, static_cast< storage_type >(v * sizeof(T)), order));
    }

    QUARK_FORCEINLINE value_type fetch_sub(difference_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(operations::fetch_sub(m_storage.value, static_cast< storage_type >(v * sizeof(T)), order));
    }

    QUARK_FORCEINLINE value_type exchange(value_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(operations::exchange(m_storage.value, atomics::detail::bitwise_cast< storage_type >(v), order));
    }

    QUARK_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_type desired, memory_order success_order, memory_order failure_order) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(failure_order != memory_order_release);
        QUARK_ASSERT(failure_order != memory_order_acq_rel);
        QUARK_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_strong(m_storage.value, old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }

    QUARK_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_type desired, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    QUARK_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_type desired, memory_order success_order, memory_order failure_order) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(failure_order != memory_order_release);
        QUARK_ASSERT(failure_order != memory_order_acq_rel);
        QUARK_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_weak(m_storage.value, old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }

    QUARK_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_type desired, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    QUARK_FORCEINLINE bool is_lock_free() const volatile QUARK_NOEXCEPT
    {
        return operations::is_lock_free(m_storage.value);
    }

    QUARK_FORCEINLINE value_type operator++(int) volatile QUARK_NOEXCEPT
    {
        return fetch_add(1);
    }

    QUARK_FORCEINLINE value_type operator++() volatile QUARK_NOEXCEPT
    {
        return fetch_add(1) + 1;
    }

    QUARK_FORCEINLINE value_type operator--(int) volatile QUARK_NOEXCEPT
    {
        return fetch_sub(1);
    }

    QUARK_FORCEINLINE value_type operator--() volatile QUARK_NOEXCEPT
    {
        return fetch_sub(1) - 1;
    }

    QUARK_FORCEINLINE value_type operator+=(difference_type v) volatile QUARK_NOEXCEPT
    {
        return fetch_add(v) + v;
    }

    QUARK_FORCEINLINE value_type operator-=(difference_type v) volatile QUARK_NOEXCEPT
    {
        return fetch_sub(v) - v;
    }

    QUARK_DELETED_FUNCTION(base_atomic(base_atomic const&))
    QUARK_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))
};


//! Implementation for void pointers
template< >
class base_atomic< void*, void* >
{
private:
    typedef void* value_type;
    typedef std::ptrdiff_t difference_type;
    typedef atomics::detail::operations< storage_size_of< value_type >::value, false > operations;

protected:
    typedef value_type value_arg_type;

public:
    typedef operations::storage_type storage_type;

protected:
    operations::aligned_storage_type m_storage;

public:
    QUARK_DEFAULTED_FUNCTION(base_atomic(), {})
    QUARK_FORCEINLINE explicit base_atomic(value_type const& v) QUARK_NOEXCEPT : m_storage(atomics::detail::bitwise_cast< storage_type >(v))
    {
    }

    QUARK_FORCEINLINE void store(value_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(order != memory_order_consume);
        QUARK_ASSERT(order != memory_order_acquire);
        QUARK_ASSERT(order != memory_order_acq_rel);

        operations::store(m_storage.value, atomics::detail::bitwise_cast< storage_type >(v), order);
    }

    QUARK_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(order != memory_order_release);
        QUARK_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(operations::load(m_storage.value, order));
    }

    QUARK_FORCEINLINE value_type fetch_add(difference_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(operations::fetch_add(m_storage.value, static_cast< storage_type >(v), order));
    }

    QUARK_FORCEINLINE value_type fetch_sub(difference_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(operations::fetch_sub(m_storage.value, static_cast< storage_type >(v), order));
    }

    QUARK_FORCEINLINE value_type exchange(value_type v, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(operations::exchange(m_storage.value, atomics::detail::bitwise_cast< storage_type >(v), order));
    }

    QUARK_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_type desired, memory_order success_order, memory_order failure_order) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(failure_order != memory_order_release);
        QUARK_ASSERT(failure_order != memory_order_acq_rel);
        QUARK_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_strong(m_storage.value, old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }

    QUARK_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_type desired, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    QUARK_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_type desired, memory_order success_order, memory_order failure_order) volatile QUARK_NOEXCEPT
    {
        QUARK_ASSERT(failure_order != memory_order_release);
        QUARK_ASSERT(failure_order != memory_order_acq_rel);
        QUARK_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_weak(m_storage.value, old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }

    QUARK_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_type desired, memory_order order = memory_order_seq_cst) volatile QUARK_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    QUARK_FORCEINLINE bool is_lock_free() const volatile QUARK_NOEXCEPT
    {
        return operations::is_lock_free(m_storage.value);
    }

    QUARK_FORCEINLINE value_type operator++(int) volatile QUARK_NOEXCEPT
    {
        return fetch_add(1);
    }

    QUARK_FORCEINLINE value_type operator++() volatile QUARK_NOEXCEPT
    {
        return (char*)fetch_add(1) + 1;
    }

    QUARK_FORCEINLINE value_type operator--(int) volatile QUARK_NOEXCEPT
    {
        return fetch_sub(1);
    }

    QUARK_FORCEINLINE value_type operator--() volatile QUARK_NOEXCEPT
    {
        return (char*)fetch_sub(1) - 1;
    }

    QUARK_FORCEINLINE value_type operator+=(difference_type v) volatile QUARK_NOEXCEPT
    {
        return (char*)fetch_add(v) + v;
    }

    QUARK_FORCEINLINE value_type operator-=(difference_type v) volatile QUARK_NOEXCEPT
    {
        return (char*)fetch_sub(v) - v;
    }

    QUARK_DELETED_FUNCTION(base_atomic(base_atomic const&))
    QUARK_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))
};

} // namespace detail

template< typename T >
class atomic :
    public atomics::detail::base_atomic< T, typename atomics::detail::classify< T >::type >
{
private:
    typedef T value_type;
    typedef atomics::detail::base_atomic< T, typename atomics::detail::classify< T >::type > base_type;
    typedef typename base_type::value_arg_type value_arg_type;

public:
    typedef typename base_type::storage_type storage_type;

public:
    QUARK_DEFAULTED_FUNCTION(atomic(), QUARK_NOEXCEPT {})

    // NOTE: The constructor is made explicit because gcc 4.7 complains that
    //       operator=(value_arg_type) is considered ambiguous with operator=(atomic const&)
    //       in assignment expressions, even though conversion to atomic<> is less preferred
    //       than conversion to value_arg_type.
    QUARK_FORCEINLINE explicit QUARK_CONSTEXPR atomic(value_arg_type v) QUARK_NOEXCEPT : base_type(v) {}

    QUARK_FORCEINLINE value_type operator= (value_arg_type v) volatile QUARK_NOEXCEPT
    {
        this->store(v);
        return v;
    }

    QUARK_FORCEINLINE operator value_type() volatile const QUARK_NOEXCEPT
    {
        return this->load();
    }

    QUARK_FORCEINLINE storage_type& storage() QUARK_NOEXCEPT { return this->m_storage.value; }
    QUARK_FORCEINLINE storage_type volatile& storage() volatile QUARK_NOEXCEPT { return this->m_storage.value; }
    QUARK_FORCEINLINE storage_type const& storage() const QUARK_NOEXCEPT { return this->m_storage.value; }
    QUARK_FORCEINLINE storage_type const volatile& storage() const volatile QUARK_NOEXCEPT { return this->m_storage.value; }

    QUARK_DELETED_FUNCTION(atomic(atomic const&))
    QUARK_DELETED_FUNCTION(atomic& operator= (atomic const&))
    QUARK_DELETED_FUNCTION(atomic& operator= (atomic const&) volatile)
};

typedef atomic< char > atomic_char;
typedef atomic< unsigned char > atomic_uchar;
typedef atomic< signed char > atomic_schar;
typedef atomic< uint8_t > atomic_uint8_t;
typedef atomic< int8_t > atomic_int8_t;
typedef atomic< unsigned short > atomic_ushort;
typedef atomic< short > atomic_short;
typedef atomic< uint16_t > atomic_uint16_t;
typedef atomic< int16_t > atomic_int16_t;
typedef atomic< unsigned int > atomic_uint;
typedef atomic< int > atomic_int;
typedef atomic< uint32_t > atomic_uint32_t;
typedef atomic< int32_t > atomic_int32_t;
typedef atomic< unsigned long > atomic_ulong;
typedef atomic< long > atomic_long;
typedef atomic< uint64_t > atomic_uint64_t;
typedef atomic< int64_t > atomic_int64_t;
#ifdef QUARK_HAS_LONG_LONG
typedef atomic< quark::ulong_long_type > atomic_ullong;
typedef atomic< quark::long_long_type > atomic_llong;
#endif
typedef atomic< void* > atomic_address;
typedef atomic< bool > atomic_bool;
typedef atomic< wchar_t > atomic_wchar_t;
#if !defined(QUARK_NO_CXX11_CHAR16_T)
typedef atomic< char16_t > atomic_char16_t;
#endif
#if !defined(QUARK_NO_CXX11_CHAR32_T)
typedef atomic< char32_t > atomic_char32_t;
#endif

typedef atomic< int_least8_t > atomic_int_least8_t;
typedef atomic< uint_least8_t > atomic_uint_least8_t;
typedef atomic< int_least16_t > atomic_int_least16_t;
typedef atomic< uint_least16_t > atomic_uint_least16_t;
typedef atomic< int_least32_t > atomic_int_least32_t;
typedef atomic< uint_least32_t > atomic_uint_least32_t;
typedef atomic< int_least64_t > atomic_int_least64_t;
typedef atomic< uint_least64_t > atomic_uint_least64_t;
typedef atomic< int_fast8_t > atomic_int_fast8_t;
typedef atomic< uint_fast8_t > atomic_uint_fast8_t;
typedef atomic< int_fast16_t > atomic_int_fast16_t;
typedef atomic< uint_fast16_t > atomic_uint_fast16_t;
typedef atomic< int_fast32_t > atomic_int_fast32_t;
typedef atomic< uint_fast32_t > atomic_uint_fast32_t;
typedef atomic< int_fast64_t > atomic_int_fast64_t;
typedef atomic< uint_fast64_t > atomic_uint_fast64_t;
typedef atomic< intmax_t > atomic_intmax_t;
typedef atomic< uintmax_t > atomic_uintmax_t;

typedef atomic< std::size_t > atomic_size_t;
typedef atomic< std::ptrdiff_t > atomic_ptrdiff_t;

#if defined(QUARK_HAS_INTPTR_T)
typedef atomic< intptr_t > atomic_intptr_t;
typedef atomic< uintptr_t > atomic_uintptr_t;
#endif

} // namespace atomics
} // namespace quark

#if defined(QUARK_MSVC)
#pragma warning(pop)
#endif

#endif // QUARK_ATOMIC_DETAIL_ATOMIC_TEMPLATE_HPP_INCLUDED_
