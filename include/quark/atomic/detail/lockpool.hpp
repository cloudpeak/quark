/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.quark.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013-2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/lockpool.hpp
 *
 * This header contains declaration of the lockpool used to emulate atomic ops.
 */

#ifndef QUARK_ATOMIC_DETAIL_LOCKPOOL_HPP_INCLUDED_
#define QUARK_ATOMIC_DETAIL_LOCKPOOL_HPP_INCLUDED_

#include <quark/atomic/detail/config.hpp>
#include <quark/atomic/detail/link.hpp>

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace quark {
namespace atomics {
namespace detail {

struct lockpool
{
    class scoped_lock
    {
        void* m_lock;

    public:
        explicit QUARK_ATOMIC_DECL scoped_lock(const volatile void* addr) QUARK_NOEXCEPT;
        QUARK_ATOMIC_DECL ~scoped_lock() QUARK_NOEXCEPT;

        QUARK_DELETED_FUNCTION(scoped_lock(scoped_lock const&))
        QUARK_DELETED_FUNCTION(scoped_lock& operator=(scoped_lock const&))
    };

    static QUARK_ATOMIC_DECL void thread_fence() QUARK_NOEXCEPT;
    static QUARK_ATOMIC_DECL void signal_fence() QUARK_NOEXCEPT;
};

} // namespace detail
} // namespace atomics
} // namespace quark

#endif // QUARK_ATOMIC_DETAIL_LOCKPOOL_HPP_INCLUDED_
