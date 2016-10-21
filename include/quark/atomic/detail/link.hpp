/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.quark.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2012 Hartmut Kaiser
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/config.hpp
 *
 * This header defines macros for linking with compiled library of Boost.Atomic
 */

#ifndef QUARK_ATOMIC_DETAIL_LINK_HPP_INCLUDED_
#define QUARK_ATOMIC_DETAIL_LINK_HPP_INCLUDED_

#include <quark/atomic/detail/config.hpp>

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

///////////////////////////////////////////////////////////////////////////////
//  Set up dll import/export options
#if (defined(QUARK_ATOMIC_DYN_LINK) || defined(QUARK_ALL_DYN_LINK)) && \
    !defined(QUARK_ATOMIC_STATIC_LINK)

#if defined(QUARK_ATOMIC_SOURCE)
#define QUARK_ATOMIC_DECL QUARK_SYMBOL_EXPORT
#define QUARK_ATOMIC_BUILD_DLL
#else
#define QUARK_ATOMIC_DECL QUARK_SYMBOL_IMPORT
#endif

#endif // building a shared library

#ifndef QUARK_ATOMIC_DECL
#define QUARK_ATOMIC_DECL
#endif

///////////////////////////////////////////////////////////////////////////////
//  Auto library naming
#if !defined(QUARK_ATOMIC_SOURCE) && !defined(QUARK_ALL_NO_LIB) && \
    !defined(QUARK_ATOMIC_NO_LIB)

#define QUARK_LIB_NAME quark_atomic

// tell the auto-link code to select a dll when required:
#if defined(QUARK_ALL_DYN_LINK) || defined(QUARK_ATOMIC_DYN_LINK)
#define QUARK_DYN_LINK
#endif

#include <quark/config/auto_link.hpp>

#endif  // auto-linking disabled

#endif
