/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.quark.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2013 - 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/bitwise_cast.hpp
 *
 * This header defines \c bitwise_cast used to convert between storage and value types
 */

#ifndef QUARK_ATOMIC_DETAIL_BITWISE_CAST_HPP_INCLUDED_
#define QUARK_ATOMIC_DETAIL_BITWISE_CAST_HPP_INCLUDED_

#include <quark/atomic/detail/config.hpp>
#if !defined(QUARK_ATOMIC_DETAIL_HAS_BUILTIN_MEMCPY)
#include <cstring>
#endif

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace quark {
namespace atomics {
namespace detail {

template< typename To, typename From >
QUARK_FORCEINLINE To bitwise_cast(From const& from) QUARK_NOEXCEPT
{
    struct
    {
        To to;
    }
    value = {};
    QUARK_ATOMIC_DETAIL_MEMCPY
    (
        &reinterpret_cast< char& >(value.to),
        &reinterpret_cast< const char& >(from),
        (sizeof(From) < sizeof(To) ? sizeof(From) : sizeof(To))
    );
    return value.to;
}

} // namespace detail
} // namespace atomics
} // namespace quark

#endif // QUARK_ATOMIC_DETAIL_BITWISE_CAST_HPP_INCLUDED_
