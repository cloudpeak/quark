//  (C) Copyright John Maddock 2011.
//  (C) Copyright Cray, Inc. 2013
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

//  Greenhills C compiler setup:

#define QUARK_COMPILER "Cray C version " QUARK_STRINGIZE(_RELEASE)

#if _RELEASE < 8
#  error "Boost is not configured for Cray compilers prior to version 8, please try the configure script."
#endif

//
// Check this is a recent EDG based compiler, otherwise we don't support it here:
//
#ifndef __EDG_VERSION__
#  error "Unsupported Cray compiler, please try running the configure script."
#endif

#include "quark/config/compiler/common_edg.hpp"


//
//
#define QUARK_NO_CXX11_STATIC_ASSERT
#define QUARK_NO_CXX11_AUTO_DECLARATIONS
#define QUARK_NO_CXX11_AUTO_MULTIDECLARATIONS
#define QUARK_HAS_NRVO
#define QUARK_NO_CXX11_VARIADIC_MACROS
#define QUARK_NO_CXX11_VARIADIC_TEMPLATES
#define QUARK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#define QUARK_NO_CXX11_UNICODE_LITERALS
#define QUARK_NO_TWO_PHASE_NAME_LOOKUP
#define QUARK_HAS_NRVO
#define QUARK_NO_CXX11_TEMPLATE_ALIASES
#define QUARK_NO_CXX11_STATIC_ASSERT
#define QUARK_NO_SFINAE_EXPR
#define QUARK_NO_CXX11_SCOPED_ENUMS
#define QUARK_NO_CXX11_RVALUE_REFERENCES
#define QUARK_NO_CXX11_RANGE_BASED_FOR
#define QUARK_NO_CXX11_RAW_LITERALS
#define QUARK_NO_CXX11_NULLPTR
#define QUARK_NO_CXX11_NOEXCEPT
#define QUARK_NO_CXX11_LAMBDAS
#define QUARK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define QUARK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define QUARK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#define QUARK_NO_CXX11_DELETED_FUNCTIONS
#define QUARK_NO_CXX11_DEFAULTED_FUNCTIONS
#define QUARK_NO_CXX11_DECLTYPE_N3276
#define QUARK_NO_CXX11_DECLTYPE
#define QUARK_NO_CXX11_CONSTEXPR
#define QUARK_NO_CXX11_USER_DEFINED_LITERALS
#define QUARK_NO_COMPLETE_VALUE_INITIALIZATION
#define QUARK_NO_CXX11_CHAR32_T
#define QUARK_NO_CXX11_CHAR16_T
#define QUARK_NO_CXX11_REF_QUALIFIERS
#define QUARK_NO_CXX11_FINAL


//#define QUARK_BCB_PARTIAL_SPECIALIZATION_BUG
#define QUARK_MATH_DISABLE_STD_FPCLASSIFY
//#define QUARK_HAS_FPCLASSIFY

#define QUARK_SP_USE_PTHREADS 
#define QUARK_AC_USE_PTHREADS 

/* everything that follows is working around what are thought to be
 * compiler shortcomings.  Revist all of these regularly.
 */

//#define QUARK_USE_ENUM_STATIC_ASSERT
//#define QUARK_BUGGY_INTEGRAL_CONSTANT_EXPRESSIONS //(this may be implied by the previous #define

// These constants should be provided by the 
// compiler, at least when -hgnu is asserted on the command line.

#ifndef __ATOMIC_RELAXED
#define __ATOMIC_RELAXED 0
#define __ATOMIC_CONSUME 1
#define __ATOMIC_ACQUIRE 2
#define __ATOMIC_RELEASE 3
#define __ATOMIC_ACQ_REL 4
#define __ATOMIC_SEQ_CST 5
#endif



