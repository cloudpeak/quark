//  Boost compiler configuration selection header file

//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2001 - 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)


//  See http://www.quark.org for most recent version.

// locate which std lib we are using and define QUARK_STDLIB_CONFIG as needed:

// First include <cstddef> to determine if some version of STLport is in use as the std lib
// (do not rely on this header being included since users can short-circuit this header 
//  if they know whose std lib they are using.)
#ifdef __cplusplus
#  include <cstddef>
#else
#  include <stddef.h>
#endif

#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
// STLPort library; this _must_ come first, otherwise since
// STLport typically sits on top of some other library, we
// can end up detecting that first rather than STLport:
#  define QUARK_STDLIB_CONFIG "quark/config/stdlib/stlport.hpp"

#else

// If our std lib was not some version of STLport, and has not otherwise
// been detected, then include <utility> as it is about 
// the smallest of the std lib headers that includes real C++ stuff.
// Some std libs do not include their C++-related macros in <cstddef> 
// so this additional include makes sure we get those definitions.
// Note: do not rely on this header being included since users can short-circuit this 
// #include if they know whose std lib they are using.
#if !defined(__LIBCOMO__) && !defined(__STD_RWCOMPILER_H__) && !defined(_RWSTD_VER)\
   && !defined(_LIBCPP_VERSION) && !defined(__GLIBCPP__) && !defined(__GLIBCXX__)\
   && !defined(__STL_CONFIG_H) && !defined(__MSL_CPP__) && !defined(__IBMCPP__)\
   && !defined(MSIPL_COMPILE_H) && !defined(_YVALS) && !defined(_CPPLIB_VER)
#include <utility>
#endif

#if defined(__LIBCOMO__)
// Comeau STL:
#define QUARK_STDLIB_CONFIG "quark/config/stdlib/libcomo.hpp"

#elif defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
// Rogue Wave library:
#  define QUARK_STDLIB_CONFIG "quark/config/stdlib/roguewave.hpp"

#elif defined(_LIBCPP_VERSION)
// libc++
#  define QUARK_STDLIB_CONFIG "quark/config/stdlib/libcpp.hpp"

#elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
// GNU libstdc++ 3
#  define QUARK_STDLIB_CONFIG "quark/config/stdlib/libstdcpp3.hpp"

#elif defined(__STL_CONFIG_H)
// generic SGI STL
#  define QUARK_STDLIB_CONFIG "quark/config/stdlib/sgi.hpp"

#elif defined(__MSL_CPP__)
// MSL standard lib:
#  define QUARK_STDLIB_CONFIG "quark/config/stdlib/msl.hpp"

#elif defined(__IBMCPP__)
// take the default VACPP std lib
#  define QUARK_STDLIB_CONFIG "quark/config/stdlib/vacpp.hpp"

#elif defined(MSIPL_COMPILE_H)
// Modena C++ standard library
#  define QUARK_STDLIB_CONFIG "quark/config/stdlib/modena.hpp"

#elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
// Dinkumware Library (this has to appear after any possible replacement libraries):
#  define QUARK_STDLIB_CONFIG "quark/config/stdlib/dinkumware.hpp"

#elif defined (QUARK_ASSERT_CONFIG)
// this must come last - generate an error if we don't
// recognise the library:
#  error "Unknown standard library - please configure and report the results to quark.org"

#endif

#endif

#if 0
//
// This section allows dependency scanners to find all the files we *might* include:
//
#  include "quark/config/stdlib/stlport.hpp"
#  include "quark/config/stdlib/libcomo.hpp"
#  include "quark/config/stdlib/roguewave.hpp"
#  include "quark/config/stdlib/libcpp.hpp"
#  include "quark/config/stdlib/libstdcpp3.hpp"
#  include "quark/config/stdlib/sgi.hpp"
#  include "quark/config/stdlib/msl.hpp"
#  include "quark/config/stdlib/vacpp.hpp"
#  include "quark/config/stdlib/modena.hpp"
#  include "quark/config/stdlib/dinkumware.hpp"
#endif

