/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.quark.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013-2014 Andrey Semashev
 */
/*!
 * \file   lockpool.cpp
 *
 * This file contains implementation of the lockpool used to emulate atomic ops.
 */

#include <cstddef>
#include <quark/config.hpp>
#include <quark/assert.hpp>
#include <quark/memory_order.hpp>
#include <quark/atomic/capabilities.hpp>

#if QUARK_ATOMIC_FLAG_LOCK_FREE == 2
#include <quark/atomic/detail/operations_lockfree.hpp>
#elif !defined(QUARK_HAS_PTHREADS)
#error Boost.Atomic: Unsupported target platform, POSIX threads are required when native atomic operations are not available
#else
#include <pthread.h>
#define QUARK_ATOMIC_USE_PTHREAD
#endif

#include <quark/atomic/detail/lockpool.hpp>
#include <quark/atomic/detail/pause.hpp>

namespace quark {
namespace atomics {
namespace detail {

namespace {

// This seems to be the maximum across all modern CPUs
// NOTE: This constant is made as a macro because some compilers (gcc 4.4 for one) don't allow enums or namespace scope constants in alignment attributes
#define QUARK_ATOMIC_CACHE_LINE_SIZE 64

#if defined(QUARK_ATOMIC_USE_PTHREAD)
typedef pthread_mutex_t lock_type;
#else
typedef atomics::detail::operations< 1u, false > lock_operations;
typedef lock_operations::storage_type lock_type;
#endif

enum
{
    padding_size = (sizeof(lock_type) <= QUARK_ATOMIC_CACHE_LINE_SIZE ?
        (QUARK_ATOMIC_CACHE_LINE_SIZE - sizeof(lock_type)) :
        (QUARK_ATOMIC_CACHE_LINE_SIZE - sizeof(lock_type) % QUARK_ATOMIC_CACHE_LINE_SIZE))
};

template< unsigned int PaddingSize >
struct QUARK_ALIGNMENT(QUARK_ATOMIC_CACHE_LINE_SIZE) padded_lock
{
    lock_type lock;
    // The additional padding is needed to avoid false sharing between locks
    char padding[PaddingSize];
};

template< >
struct QUARK_ALIGNMENT(QUARK_ATOMIC_CACHE_LINE_SIZE) padded_lock< 0u >
{
    lock_type lock;
};

typedef padded_lock< padding_size > padded_lock_t;

static padded_lock_t g_lock_pool[41]
#if defined(QUARK_ATOMIC_USE_PTHREAD)
=
{
    { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER },
    { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER },
    { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER },
    { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER },
    { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER },
    { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER },
    { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER },
    { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER }, { PTHREAD_MUTEX_INITIALIZER },
    { PTHREAD_MUTEX_INITIALIZER }
}
#endif
;

} // namespace


#if !defined(QUARK_ATOMIC_USE_PTHREAD)

// NOTE: This function must NOT be inline. Otherwise MSVC 9 will sometimes generate broken code for modulus operation which result in crashes.
QUARK_ATOMIC_DECL lockpool::scoped_lock::scoped_lock(const volatile void* addr) QUARK_NOEXCEPT :
    m_lock(&g_lock_pool[reinterpret_cast< std::size_t >(addr) % (sizeof(g_lock_pool) / sizeof(*g_lock_pool))].lock)
{
    while (lock_operations::test_and_set(*static_cast< lock_type* >(m_lock), memory_order_acquire))
    {
        do
        {
            atomics::detail::pause();
        }
        while (!!lock_operations::load(*static_cast< lock_type* >(m_lock), memory_order_relaxed));
    }
}

QUARK_ATOMIC_DECL lockpool::scoped_lock::~scoped_lock() QUARK_NOEXCEPT
{
    lock_operations::clear(*static_cast< lock_type* >(m_lock), memory_order_release);
}

QUARK_ATOMIC_DECL void signal_fence() QUARK_NOEXCEPT;

#else // !defined(QUARK_ATOMIC_USE_PTHREAD)

QUARK_ATOMIC_DECL lockpool::scoped_lock::scoped_lock(const volatile void* addr) QUARK_NOEXCEPT :
    m_lock(&g_lock_pool[reinterpret_cast< std::size_t >(addr) % (sizeof(g_lock_pool) / sizeof(*g_lock_pool))].lock)
{
    QUARK_VERIFY(pthread_mutex_lock(static_cast< pthread_mutex_t* >(m_lock)) == 0);
}

QUARK_ATOMIC_DECL lockpool::scoped_lock::~scoped_lock() QUARK_NOEXCEPT
{
    QUARK_VERIFY(pthread_mutex_unlock(static_cast< pthread_mutex_t* >(m_lock)) == 0);
}

#endif // !defined(QUARK_ATOMIC_USE_PTHREAD)

QUARK_ATOMIC_DECL void lockpool::thread_fence() QUARK_NOEXCEPT
{
#if QUARK_ATOMIC_THREAD_FENCE > 0
    atomics::detail::thread_fence(memory_order_seq_cst);
#else
    // Emulate full fence by locking/unlocking a mutex
    scoped_lock lock(0);
#endif
}

QUARK_ATOMIC_DECL void lockpool::signal_fence() QUARK_NOEXCEPT
{
    // This function is intentionally non-inline, even if empty. This forces the compiler to treat its call as a compiler barrier.
#if QUARK_ATOMIC_SIGNAL_FENCE > 0
    atomics::detail::signal_fence(memory_order_seq_cst);
#endif
}

} // namespace detail
} // namespace atomics
} // namespace quark

