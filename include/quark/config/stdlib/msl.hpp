//  (C) Copyright John Maddock 2001. 
//  (C) Copyright Darin Adler 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

//  Metrowerks standard library:

#ifndef __MSL_CPP__
#  include <quark/config/no_tr1/utility.hpp>
#  ifndef __MSL_CPP__
#     error This is not the MSL standard library!
#  endif
#endif

#if __MSL_CPP__ >= 0x6000  // Pro 6
#  define QUARK_HAS_HASH
#  define QUARK_STD_EXTENSION_NAMESPACE Metrowerks
#endif
#define QUARK_HAS_SLIST

#if __MSL_CPP__ < 0x6209
#  define QUARK_NO_STD_MESSAGES
#endif

// check C lib version for <stdint.h>
#include <cstddef>

#if defined(__MSL__) && (__MSL__ >= 0x5000)
#  define QUARK_HAS_STDINT_H
#  if !defined(__PALMOS_TRAPS__)
#    define QUARK_HAS_UNISTD_H
#  endif
   // boilerplate code:
#  include <quark/config/posix_features.hpp>
#endif

#if defined(_MWMT) || _MSL_THREADSAFE
#  define QUARK_HAS_THREADS
#endif

#ifdef _MSL_NO_EXPLICIT_FUNC_TEMPLATE_ARG
#  define QUARK_NO_STD_USE_FACET
#  define QUARK_HAS_TWO_ARG_USE_FACET
#endif

//  C++0x headers not yet implemented
//
#  define QUARK_NO_CXX11_HDR_ARRAY
#  define QUARK_NO_CXX11_HDR_CHRONO
#  define QUARK_NO_CXX11_HDR_CODECVT
#  define QUARK_NO_CXX11_HDR_CONDITION_VARIABLE
#  define QUARK_NO_CXX11_HDR_FORWARD_LIST
#  define QUARK_NO_CXX11_HDR_FUTURE
#  define QUARK_NO_CXX11_HDR_INITIALIZER_LIST
#  define QUARK_NO_CXX11_HDR_MUTEX
#  define QUARK_NO_CXX11_HDR_RANDOM
#  define QUARK_NO_CXX11_HDR_RATIO
#  define QUARK_NO_CXX11_HDR_REGEX
#  define QUARK_NO_CXX11_HDR_SYSTEM_ERROR
#  define QUARK_NO_CXX11_HDR_THREAD
#  define QUARK_NO_CXX11_HDR_TUPLE
#  define QUARK_NO_CXX11_HDR_TYPE_TRAITS
#  define QUARK_NO_CXX11_HDR_TYPEINDEX
#  define QUARK_NO_CXX11_HDR_UNORDERED_MAP
#  define QUARK_NO_CXX11_HDR_UNORDERED_SET
#  define QUARK_NO_CXX11_NUMERIC_LIMITS
#  define QUARK_NO_CXX11_ALLOCATOR
#  define QUARK_NO_CXX11_ATOMIC_SMART_PTR
#  define QUARK_NO_CXX11_SMART_PTR
#  define QUARK_NO_CXX11_HDR_FUNCTIONAL
#  define QUARK_NO_CXX11_HDR_ATOMIC
#  define QUARK_NO_CXX11_STD_ALIGN
#  define QUARK_NO_CXX11_ADDRESSOF

#if defined(__has_include)
#if !__has_include(<shared_mutex>)
#  define QUARK_NO_CXX14_HDR_SHARED_MUTEX
#elif __cplusplus < 201402
#  define QUARK_NO_CXX14_HDR_SHARED_MUTEX
#endif
#else
#  define QUARK_NO_CXX14_HDR_SHARED_MUTEX
#endif

#define QUARK_STDLIB "Metrowerks Standard Library version " QUARK_STRINGIZE(__MSL_CPP__)
