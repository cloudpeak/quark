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
 * \file   atomic/fences.hpp
 *
 * This header contains definition of \c atomic_thread_fence and \c atomic_signal_fence functions.
 */

#ifndef QUARK_ATOMIC_FENCES_HPP_INCLUDED_
#define QUARK_ATOMIC_FENCES_HPP_INCLUDED_

#include <quark/memory_order.hpp>
#include <quark/atomic/capabilities.hpp>
#include <quark/atomic/detail/operations.hpp>

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

/*
 * IMPLEMENTATION NOTE: All interface functions MUST be declared with QUARK_FORCEINLINE,
 *                      see comment for convert_memory_order_to_gcc in ops_gcc_atomic.hpp.
 */

namespace quark {

namespace atomics {

#if QUARK_ATOMIC_THREAD_FENCE > 0
QUARK_FORCEINLINE void atomic_thread_fence(memory_order order) QUARK_NOEXCEPT
{
    detail::thread_fence(order);
}
#else
QUARK_FORCEINLINE void atomic_thread_fence(memory_order) QUARK_NOEXCEPT
{
    detail::lockpool::thread_fence();
}
#endif

#if QUARK_ATOMIC_SIGNAL_FENCE > 0
QUARK_FORCEINLINE void atomic_signal_fence(memory_order order) QUARK_NOEXCEPT
{
    detail::signal_fence(order);
}
#else
QUARK_FORCEINLINE void atomic_signal_fence(memory_order) QUARK_NOEXCEPT
{
    detail::lockpool::signal_fence();
}
#endif

} // namespace atomics

using atomics::atomic_thread_fence;
using atomics::atomic_signal_fence;

} // namespace quark

#endif // QUARK_ATOMIC_FENCES_HPP_INCLUDED_
