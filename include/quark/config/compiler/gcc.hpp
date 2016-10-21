//  (C) Copyright John Maddock 2001 - 2003.
//  (C) Copyright Darin Adler 2001 - 2002.
//  (C) Copyright Jens Maurer 2001 - 2002.
//  (C) Copyright Beman Dawes 2001 - 2003.
//  (C) Copyright Douglas Gregor 2002.
//  (C) Copyright David Abrahams 2002 - 2003.
//  (C) Copyright Synge Todo 2003.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

//  GNU C++ compiler setup.

//
// Define QUARK_GCC so we know this is "real" GCC and not some pretender:
//
#define QUARK_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#if !defined(__CUDACC__)
#define QUARK_GCC QUARK_GCC_VERSION
#endif

#if defined(__GXX_EXPERIMENTAL_CXX0X__) || (__cplusplus >= 201103L)
#  define QUARK_GCC_CXX11
#endif

#if __GNUC__ == 3
#  if defined (__PATHSCALE__)
#     define QUARK_NO_TWO_PHASE_NAME_LOOKUP
#     define QUARK_NO_IS_ABSTRACT
#  endif

#  if __GNUC_MINOR__ < 4
#     define QUARK_NO_IS_ABSTRACT
#  endif
#  define QUARK_NO_CXX11_EXTERN_TEMPLATE
#endif
#if __GNUC__ < 4
//
// All problems to gcc-3.x and earlier here:
//
#define QUARK_NO_TWO_PHASE_NAME_LOOKUP
#  ifdef __OPEN64__
#     define QUARK_NO_IS_ABSTRACT
#  endif
#endif

// GCC prior to 3.4 had #pragma once too but it didn't work well with filesystem links
#if QUARK_GCC_VERSION >= 30400
#define QUARK_HAS_PRAGMA_ONCE
#endif

#if QUARK_GCC_VERSION < 40400
// Previous versions of GCC did not completely implement value-initialization:
// GCC Bug 30111, "Value-initialization of POD base class doesn't initialize
// members", reported by Jonathan Wakely in 2006,
// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=30111 (fixed for GCC 4.4)
// GCC Bug 33916, "Default constructor fails to initialize array members",
// reported by Michael Elizabeth Chastain in 2007,
// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=33916 (fixed for GCC 4.2.4)
// See also: http://www.quark.org/libs/utility/value_init.htm#compiler_issues
#define QUARK_NO_COMPLETE_VALUE_INITIALIZATION
#endif

#if !defined(__EXCEPTIONS) && !defined(QUARK_NO_EXCEPTIONS)
# define QUARK_NO_EXCEPTIONS
#endif


//
// Threading support: Turn this on unconditionally here (except for
// those platforms where we can know for sure). It will get turned off again
// later if no threading API is detected.
//
#if !defined(__MINGW32__) && !defined(linux) && !defined(__linux) && !defined(__linux__)
# define QUARK_HAS_THREADS
#endif

//
// gcc has "long long"
// Except on Darwin with standard compliance enabled (-pedantic)
// Apple gcc helpfully defines this macro we can query
//
#if !defined(__DARWIN_NO_LONG_LONG)
# define QUARK_HAS_LONG_LONG
#endif

//
// gcc implements the named return value optimization since version 3.1
//
#define QUARK_HAS_NRVO

// Branch prediction hints
#define QUARK_LIKELY(x) __builtin_expect(x, 1)
#define QUARK_UNLIKELY(x) __builtin_expect(x, 0)

//
// Dynamic shared object (DSO) and dynamic-link library (DLL) support
//
#if __GNUC__ >= 4
#  if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined(__CYGWIN__)
     // All Win32 development environments, including 64-bit Windows and MinGW, define
     // _WIN32 or one of its variant spellings. Note that Cygwin is a POSIX environment,
     // so does not define _WIN32 or its variants.
#    define QUARK_HAS_DECLSPEC
#    define QUARK_SYMBOL_EXPORT __attribute__((__dllexport__))
#    define QUARK_SYMBOL_IMPORT __attribute__((__dllimport__))
#  else
#    define QUARK_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#    define QUARK_SYMBOL_IMPORT
#  endif
#  define QUARK_SYMBOL_VISIBLE __attribute__((__visibility__("default")))
#else
// config/platform/win32.hpp will define QUARK_SYMBOL_EXPORT, etc., unless already defined
#  define QUARK_SYMBOL_EXPORT
#endif

//
// RTTI and typeinfo detection is possible post gcc-4.3:
//
#if QUARK_GCC_VERSION > 40300
#  ifndef __GXX_RTTI
#     ifndef QUARK_NO_TYPEID
#        define QUARK_NO_TYPEID
#     endif
#     ifndef QUARK_NO_RTTI
#        define QUARK_NO_RTTI
#     endif
#  endif
#endif

//
// Recent GCC versions have __int128 when in 64-bit mode.
//
// We disable this if the compiler is really nvcc as it
// doesn't actually support __int128 as of CUDA_VERSION=5000
// even though it defines __SIZEOF_INT128__.
// See https://svn.quark.org/trac/quark/ticket/8048
// Only re-enable this for nvcc if you're absolutely sure
// of the circumstances under which it's supported:
//
#if defined(__SIZEOF_INT128__) && !defined(__CUDACC__)
#  define QUARK_HAS_INT128
#endif

// C++0x features in 4.3.n and later
//
#if (QUARK_GCC_VERSION >= 40300) && defined(QUARK_GCC_CXX11)
// C++0x features are only enabled when -std=c++0x or -std=gnu++0x are
// passed on the command line, which in turn defines
// __GXX_EXPERIMENTAL_CXX0X__.
#  define QUARK_HAS_DECLTYPE
#  define QUARK_HAS_RVALUE_REFS
#  define QUARK_HAS_STATIC_ASSERT
#  define QUARK_HAS_VARIADIC_TMPL
#else
#  define QUARK_NO_CXX11_DECLTYPE
#  define QUARK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#  define QUARK_NO_CXX11_RVALUE_REFERENCES
#  define QUARK_NO_CXX11_STATIC_ASSERT
#endif

// C++0x features in 4.4.n and later
//
#if (QUARK_GCC_VERSION < 40400) || !defined(QUARK_GCC_CXX11)
#  define QUARK_NO_CXX11_AUTO_DECLARATIONS
#  define QUARK_NO_CXX11_AUTO_MULTIDECLARATIONS
#  define QUARK_NO_CXX11_CHAR16_T
#  define QUARK_NO_CXX11_CHAR32_T
#  define QUARK_NO_CXX11_HDR_INITIALIZER_LIST
#  define QUARK_NO_CXX11_DEFAULTED_FUNCTIONS
#  define QUARK_NO_CXX11_DELETED_FUNCTIONS
#  define QUARK_NO_CXX11_TRAILING_RESULT_TYPES
#  define QUARK_NO_CXX11_INLINE_NAMESPACES
#  define QUARK_NO_CXX11_VARIADIC_TEMPLATES
#endif

#if QUARK_GCC_VERSION < 40500
#  define QUARK_NO_SFINAE_EXPR
#endif

// GCC 4.5 forbids declaration of defaulted functions in private or protected sections
#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ == 5) || !defined(QUARK_GCC_CXX11)
#  define QUARK_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS
#endif

// C++0x features in 4.5.0 and later
//
#if (QUARK_GCC_VERSION < 40500) || !defined(QUARK_GCC_CXX11)
#  define QUARK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#  define QUARK_NO_CXX11_LAMBDAS
#  define QUARK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#  define QUARK_NO_CXX11_RAW_LITERALS
#  define QUARK_NO_CXX11_UNICODE_LITERALS
#endif

// C++0x features in 4.5.1 and later
//
#if (QUARK_GCC_VERSION < 40501) || !defined(QUARK_GCC_CXX11)
// scoped enums have a serious bug in 4.4.0, so define QUARK_NO_CXX11_SCOPED_ENUMS before 4.5.1
// See http://gcc.gnu.org/bugzilla/show_bug.cgi?id=38064
#  define QUARK_NO_CXX11_SCOPED_ENUMS
#endif

// C++0x features in 4.6.n and later
//
#if (QUARK_GCC_VERSION < 40600) || !defined(QUARK_GCC_CXX11)
#define QUARK_NO_CXX11_CONSTEXPR
#define QUARK_NO_CXX11_NOEXCEPT
#define QUARK_NO_CXX11_NULLPTR
#define QUARK_NO_CXX11_RANGE_BASED_FOR
#define QUARK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#endif

// C++0x features in 4.7.n and later
//
#if (QUARK_GCC_VERSION < 40700) || !defined(QUARK_GCC_CXX11)
#  define QUARK_NO_CXX11_FINAL
#  define QUARK_NO_CXX11_TEMPLATE_ALIASES
#  define QUARK_NO_CXX11_USER_DEFINED_LITERALS
#  define QUARK_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS
#endif

// C++0x features in 4.8.n and later
//
#if (QUARK_GCC_VERSION < 40800) || !defined(QUARK_GCC_CXX11)
#  define QUARK_NO_CXX11_ALIGNAS
#endif

// C++0x features in 4.8.1 and later
//
#if (QUARK_GCC_VERSION < 40801) || !defined(QUARK_GCC_CXX11)
#  define QUARK_NO_CXX11_DECLTYPE_N3276
#  define QUARK_NO_CXX11_REF_QUALIFIERS
#  define QUARK_NO_CXX14_BINARY_LITERALS
#endif

// C++14 features in 4.9.0 and later
//
#if (QUARK_GCC_VERSION < 40900) || (__cplusplus < 201300)
#  define QUARK_NO_CXX14_RETURN_TYPE_DEDUCTION
#  define QUARK_NO_CXX14_GENERIC_LAMBDAS
#  define QUARK_NO_CXX14_DIGIT_SEPARATORS
#  define QUARK_NO_CXX14_DECLTYPE_AUTO
#  if !((QUARK_GCC_VERSION >= 40801) && (QUARK_GCC_VERSION < 40900) && defined(QUARK_GCC_CXX11))
#     define QUARK_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#  endif
#endif


// C++ 14:
#if !defined(__cpp_aggregate_nsdmi) || (__cpp_aggregate_nsdmi < 201304)
#  define QUARK_NO_CXX14_AGGREGATE_NSDMI
#endif
#if !defined(__cpp_constexpr) || (__cpp_constexpr < 201304)
#  define QUARK_NO_CXX14_CONSTEXPR
#endif
#if !defined(__cpp_variable_templates) || (__cpp_variable_templates < 201304)
#  define QUARK_NO_CXX14_VARIABLE_TEMPLATES
#endif

//
// Unused attribute:
#if __GNUC__ >= 4
#  define QUARK_ATTRIBUTE_UNUSED __attribute__((unused))
#endif

#ifndef QUARK_COMPILER
#  define QUARK_COMPILER "GNU C++ version " __VERSION__
#endif

// ConceptGCC compiler:
//   http://www.generic-programming.org/software/ConceptGCC/
#ifdef __GXX_CONCEPTS__
#  define QUARK_HAS_CONCEPTS
#  define QUARK_COMPILER "ConceptGCC version " __VERSION__
#endif

// versions check:
// we don't know gcc prior to version 3.30:
#if (QUARK_GCC_VERSION< 30300)
#  error "Compiler not configured - please reconfigure"
#endif
//
// last known and checked version is 4.9:
#if (QUARK_GCC_VERSION > 40900)
#  if defined(QUARK_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  else
// we don't emit warnings here anymore since there are no defect macros defined for
// gcc post 3.4, so any failures are gcc regressions...
//#     warning "Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif

