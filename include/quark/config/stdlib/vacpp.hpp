//  (C) Copyright John Maddock 2001 - 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

#if __IBMCPP__ <= 501
#  define QUARK_NO_STD_ALLOCATOR
#endif

#define QUARK_HAS_MACRO_USE_FACET
#define QUARK_NO_STD_MESSAGES

// Apple doesn't seem to reliably defined a *unix* macro
#if !defined(CYGWIN) && (  defined(__unix__)  \
                        || defined(__unix)    \
                        || defined(unix)      \
                        || defined(__APPLE__) \
                        || defined(__APPLE)   \
                        || defined(APPLE))
#  include <unistd.h>
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

#define QUARK_STDLIB "Visual Age default standard library"
