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
 * \file   atomic/detail/storage_type.hpp
 *
 * This header defines underlying types used as storage
 */

#ifndef QUARK_ATOMIC_DETAIL_STORAGE_TYPE_HPP_INCLUDED_
#define QUARK_ATOMIC_DETAIL_STORAGE_TYPE_HPP_INCLUDED_

#include <cstddef>
#include <quark/cstdint.hpp>
#include <quark/atomic/detail/config.hpp>
#if !defined(QUARK_ATOMIC_DETAIL_HAS_BUILTIN_MEMCMP) || !defined(QUARK_ATOMIC_DETAIL_HAS_BUILTIN_MEMCPY)
#include <cstring>
#endif

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace quark {
namespace atomics {
namespace detail {

template< typename T >
QUARK_FORCEINLINE void non_atomic_load(T const volatile& from, T& to) QUARK_NOEXCEPT
{
    to = from;
}

template< std::size_t Size >
struct buffer_storage
{
    QUARK_ALIGNMENT(16) unsigned char data[Size];

    QUARK_FORCEINLINE bool operator! () const QUARK_NOEXCEPT
    {
        return (data[0] == 0u && QUARK_ATOMIC_DETAIL_MEMCMP(data, data + 1, Size - 1) == 0);
    }

    QUARK_FORCEINLINE bool operator== (buffer_storage const& that) const QUARK_NOEXCEPT
    {
        return QUARK_ATOMIC_DETAIL_MEMCMP(data, that.data, Size) == 0;
    }

    QUARK_FORCEINLINE bool operator!= (buffer_storage const& that) const QUARK_NOEXCEPT
    {
        return QUARK_ATOMIC_DETAIL_MEMCMP(data, that.data, Size) != 0;
    }
};

template< std::size_t Size >
QUARK_FORCEINLINE void non_atomic_load(buffer_storage< Size > const volatile& from, buffer_storage< Size >& to) QUARK_NOEXCEPT
{
    QUARK_ATOMIC_DETAIL_MEMCPY(to.data, const_cast< unsigned char const* >(from.data), Size);
}

template< std::size_t Size, bool Signed >
struct make_storage_type
{
    typedef buffer_storage< Size > type;

    struct aligned
    {
        type value;

        QUARK_DEFAULTED_FUNCTION(aligned(), {})
        QUARK_FORCEINLINE QUARK_CONSTEXPR explicit aligned(type const& v) QUARK_NOEXCEPT : value(v) {}
    };
};

template< >
struct make_storage_type< 1u, false >
{
    typedef quark::uint8_t type;

    struct aligned
    {
        type value;

        QUARK_DEFAULTED_FUNCTION(aligned(), {})
        QUARK_FORCEINLINE QUARK_CONSTEXPR explicit aligned(type v) QUARK_NOEXCEPT : value(v) {}
    };
};

template< >
struct make_storage_type< 1u, true >
{
    typedef quark::int8_t type;

    struct aligned
    {
        type value;

        QUARK_DEFAULTED_FUNCTION(aligned(), {})
        QUARK_FORCEINLINE QUARK_CONSTEXPR explicit aligned(type v) QUARK_NOEXCEPT : value(v) {}
    };
};

template< >
struct make_storage_type< 2u, false >
{
    typedef quark::uint16_t type;

    struct aligned
    {
        QUARK_ALIGNMENT(2) type value;

        QUARK_DEFAULTED_FUNCTION(aligned(), {})
        QUARK_FORCEINLINE QUARK_CONSTEXPR explicit aligned(type v) QUARK_NOEXCEPT : value(v) {}
    };
};

template< >
struct make_storage_type< 2u, true >
{
    typedef quark::int16_t type;

    struct aligned
    {
        QUARK_ALIGNMENT(2) type value;

        QUARK_DEFAULTED_FUNCTION(aligned(), {})
        QUARK_FORCEINLINE QUARK_CONSTEXPR explicit aligned(type v) QUARK_NOEXCEPT : value(v) {}
    };
};

template< >
struct make_storage_type< 4u, false >
{
    typedef quark::uint32_t type;

    struct aligned
    {
        QUARK_ALIGNMENT(4) type value;

        QUARK_DEFAULTED_FUNCTION(aligned(), {})
        QUARK_FORCEINLINE QUARK_CONSTEXPR explicit aligned(type v) QUARK_NOEXCEPT : value(v) {}
    };
};

template< >
struct make_storage_type< 4u, true >
{
    typedef quark::int32_t type;

    struct aligned
    {
        QUARK_ALIGNMENT(4) type value;

        QUARK_DEFAULTED_FUNCTION(aligned(), {})
        QUARK_FORCEINLINE QUARK_CONSTEXPR explicit aligned(type v) QUARK_NOEXCEPT : value(v) {}
    };
};

template< >
struct make_storage_type< 8u, false >
{
    typedef quark::uint64_t type;

    struct aligned
    {
        QUARK_ALIGNMENT(8) type value;

        QUARK_DEFAULTED_FUNCTION(aligned(), {})
        QUARK_FORCEINLINE QUARK_CONSTEXPR explicit aligned(type v) QUARK_NOEXCEPT : value(v) {}
    };
};

template< >
struct make_storage_type< 8u, true >
{
    typedef quark::int64_t type;

    struct aligned
    {
        QUARK_ALIGNMENT(8) type value;

        QUARK_DEFAULTED_FUNCTION(aligned(), {})
        QUARK_FORCEINLINE QUARK_CONSTEXPR explicit aligned(type v) QUARK_NOEXCEPT : value(v) {}
    };
};

#if defined(QUARK_HAS_INT128)

template< >
struct make_storage_type< 16u, false >
{
    typedef quark::uint128_type type;

    struct aligned
    {
        QUARK_ALIGNMENT(16) type value;

        QUARK_DEFAULTED_FUNCTION(aligned(), {})
        QUARK_FORCEINLINE QUARK_CONSTEXPR explicit aligned(type v) QUARK_NOEXCEPT : value(v) {}
    };
};

template< >
struct make_storage_type< 16u, true >
{
    typedef quark::int128_type type;

    struct aligned
    {
        QUARK_ALIGNMENT(16) type value;

        QUARK_DEFAULTED_FUNCTION(aligned(), {})
        QUARK_FORCEINLINE QUARK_CONSTEXPR explicit aligned(type v) QUARK_NOEXCEPT : value(v) {}
    };
};

#elif !defined(QUARK_NO_ALIGNMENT)

struct storage128_t
{
    quark::uint64_t data[2];

    QUARK_FORCEINLINE bool operator! () const QUARK_NOEXCEPT
    {
        return data[0] == 0 && data[1] == 0;
    }
};

QUARK_FORCEINLINE bool operator== (storage128_t const& left, storage128_t const& right) QUARK_NOEXCEPT
{
    return left.data[0] == right.data[0] && left.data[1] == right.data[1];
}
QUARK_FORCEINLINE bool operator!= (storage128_t const& left, storage128_t const& right) QUARK_NOEXCEPT
{
    return !(left == right);
}

QUARK_FORCEINLINE void non_atomic_load(storage128_t const volatile& from, storage128_t& to) QUARK_NOEXCEPT
{
    to.data[0] = from.data[0];
    to.data[1] = from.data[1];
}

template< bool Signed >
struct make_storage_type< 16u, Signed >
{
    typedef storage128_t type;

    struct aligned
    {
        QUARK_ALIGNMENT(16) type value;

        QUARK_DEFAULTED_FUNCTION(aligned(), {})
        QUARK_FORCEINLINE QUARK_CONSTEXPR explicit aligned(type const& v) QUARK_NOEXCEPT : value(v) {}
    };
};

#endif

template< typename T >
struct storage_size_of
{
    enum _
    {
        size = sizeof(T),
        value = (size == 3 ? 4 : (size >= 5 && size <= 7 ? 8 : (size >= 9 && size <= 15 ? 16 : size)))
    };
};

} // namespace detail
} // namespace atomics
} // namespace quark

#endif // QUARK_ATOMIC_DETAIL_STORAGE_TYPE_HPP_INCLUDED_
