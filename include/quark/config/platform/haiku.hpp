//  (C) Copyright Jessica Hamilton 2014.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

//  Haiku specific config options:

#define QUARK_PLATFORM "Haiku"

#define QUARK_HAS_UNISTD_H
#define QUARK_HAS_STDINT_H

#ifndef QUARK_DISABLE_THREADS
#  define QUARK_HAS_THREADS
#endif

#define QUARK_NO_CXX11_HDR_TYPE_TRAITS
#define QUARK_NO_CXX11_ATOMIC_SMART_PTR
#define QUARK_NO_CXX11_STATIC_ASSERT
#define QUARK_NO_CXX11_VARIADIC_MACROS

//
// thread API's not auto detected:
//
#define QUARK_HAS_SCHED_YIELD
#define QUARK_HAS_GETTIMEOFDAY

// boilerplate code:
#include <quark/config/posix_features.hpp>
