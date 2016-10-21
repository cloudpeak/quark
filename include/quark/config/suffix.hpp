//  Boost config.hpp configuration header file  ------------------------------//
//  quarkinspect:ndprecated_macros -- tell the inspect tool to ignore this file

//  Copyright (c) 2001-2003 John Maddock
//  Copyright (c) 2001 Darin Adler
//  Copyright (c) 2001 Peter Dimov
//  Copyright (c) 2002 Bill Kempf
//  Copyright (c) 2002 Jens Maurer
//  Copyright (c) 2002-2003 David Abrahams
//  Copyright (c) 2003 Gennaro Prota
//  Copyright (c) 2003 Eric Friedman
//  Copyright (c) 2010 Eric Jourdanneau, Joel Falcou
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org/ for most recent version.

//  Boost config.hpp policy and rationale documentation has been moved to
//  http://www.quark.org/libs/config/
//
//  This file is intended to be stable, and relatively unchanging.
//  It should contain boilerplate code only - no compiler specific
//  code unless it is unavoidable - no changes unless unavoidable.

#ifndef QUARK_CONFIG_SUFFIX_HPP
#define QUARK_CONFIG_SUFFIX_HPP

#if defined(__GNUC__) && (__GNUC__ >= 4)
//
// Some GCC-4.x versions issue warnings even when __extension__ is used,
// so use this as a workaround:
//
#pragma GCC system_header
#endif

//
// ensure that visibility macros are always defined, thus symplifying use
//
#ifndef QUARK_SYMBOL_EXPORT
# define QUARK_SYMBOL_EXPORT
#endif
#ifndef QUARK_SYMBOL_IMPORT
# define QUARK_SYMBOL_IMPORT
#endif
#ifndef QUARK_SYMBOL_VISIBLE
# define QUARK_SYMBOL_VISIBLE
#endif

//
// look for long long by looking for the appropriate macros in <limits.h>.
// Note that we use limits.h rather than climits for maximal portability,
// remember that since these just declare a bunch of macros, there should be
// no namespace issues from this.
//
#if !defined(QUARK_HAS_LONG_LONG) && !defined(QUARK_NO_LONG_LONG)                                              \
   && !defined(QUARK_MSVC) && !defined(__BORLANDC__)
# include <limits.h>
# if (defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX))
#   define QUARK_HAS_LONG_LONG
# else
#   define QUARK_NO_LONG_LONG
# endif
#endif

// GCC 3.x will clean up all of those nasty macro definitions that
// QUARK_NO_CTYPE_FUNCTIONS is intended to help work around, so undefine
// it under GCC 3.x.
#if defined(__GNUC__) && (__GNUC__ >= 3) && defined(QUARK_NO_CTYPE_FUNCTIONS)
#  undef QUARK_NO_CTYPE_FUNCTIONS
#endif

//
// Assume any extensions are in namespace std:: unless stated otherwise:
//
#  ifndef QUARK_STD_EXTENSION_NAMESPACE
#    define QUARK_STD_EXTENSION_NAMESPACE std
#  endif

//
// If cv-qualified specializations are not allowed, then neither are cv-void ones:
//
#  if defined(QUARK_NO_CV_SPECIALIZATIONS) \
      && !defined(QUARK_NO_CV_VOID_SPECIALIZATIONS)
#     define QUARK_NO_CV_VOID_SPECIALIZATIONS
#  endif

//
// If there is no numeric_limits template, then it can't have any compile time
// constants either!
//
#  if defined(QUARK_NO_LIMITS) \
      && !defined(QUARK_NO_LIMITS_COMPILE_TIME_CONSTANTS)
#     define QUARK_NO_LIMITS_COMPILE_TIME_CONSTANTS
#     define QUARK_NO_MS_INT64_NUMERIC_LIMITS
#     define QUARK_NO_LONG_LONG_NUMERIC_LIMITS
#  endif

//
// if there is no long long then there is no specialisation
// for numeric_limits<long long> either:
//
#if !defined(QUARK_HAS_LONG_LONG) && !defined(QUARK_NO_LONG_LONG_NUMERIC_LIMITS)
#  define QUARK_NO_LONG_LONG_NUMERIC_LIMITS
#endif

//
// if there is no __int64 then there is no specialisation
// for numeric_limits<__int64> either:
//
#if !defined(QUARK_HAS_MS_INT64) && !defined(QUARK_NO_MS_INT64_NUMERIC_LIMITS)
#  define QUARK_NO_MS_INT64_NUMERIC_LIMITS
#endif

//
// if member templates are supported then so is the
// VC6 subset of member templates:
//
#  if !defined(QUARK_NO_MEMBER_TEMPLATES) \
       && !defined(QUARK_MSVC6_MEMBER_TEMPLATES)
#     define QUARK_MSVC6_MEMBER_TEMPLATES
#  endif

//
// Without partial specialization, can't test for partial specialisation bugs:
//
#  if defined(QUARK_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
      && !defined(QUARK_BCB_PARTIAL_SPECIALIZATION_BUG)
#     define QUARK_BCB_PARTIAL_SPECIALIZATION_BUG
#  endif

//
// Without partial specialization, we can't have array-type partial specialisations:
//
#  if defined(QUARK_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
      && !defined(QUARK_NO_ARRAY_TYPE_SPECIALIZATIONS)
#     define QUARK_NO_ARRAY_TYPE_SPECIALIZATIONS
#  endif

//
// Without partial specialization, std::iterator_traits can't work:
//
#  if defined(QUARK_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
      && !defined(QUARK_NO_STD_ITERATOR_TRAITS)
#     define QUARK_NO_STD_ITERATOR_TRAITS
#  endif

//
// Without partial specialization, partial
// specialization with default args won't work either:
//
#  if defined(QUARK_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
      && !defined(QUARK_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
#     define QUARK_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS
#  endif

//
// Without member template support, we can't have template constructors
// in the standard library either:
//
#  if defined(QUARK_NO_MEMBER_TEMPLATES) \
      && !defined(QUARK_MSVC6_MEMBER_TEMPLATES) \
      && !defined(QUARK_NO_TEMPLATED_ITERATOR_CONSTRUCTORS)
#     define QUARK_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#  endif

//
// Without member template support, we can't have a conforming
// std::allocator template either:
//
#  if defined(QUARK_NO_MEMBER_TEMPLATES) \
      && !defined(QUARK_MSVC6_MEMBER_TEMPLATES) \
      && !defined(QUARK_NO_STD_ALLOCATOR)
#     define QUARK_NO_STD_ALLOCATOR
#  endif

//
// without ADL support then using declarations will break ADL as well:
//
#if defined(QUARK_NO_ARGUMENT_DEPENDENT_LOOKUP) && !defined(QUARK_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
#  define QUARK_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#endif

//
// Without typeid support we have no dynamic RTTI either:
//
#if defined(QUARK_NO_TYPEID) && !defined(QUARK_NO_RTTI)
#  define QUARK_NO_RTTI
#endif

//
// If we have a standard allocator, then we have a partial one as well:
//
#if !defined(QUARK_NO_STD_ALLOCATOR)
#  define QUARK_HAS_PARTIAL_STD_ALLOCATOR
#endif

//
// We can't have a working std::use_facet if there is no std::locale:
//
#  if defined(QUARK_NO_STD_LOCALE) && !defined(QUARK_NO_STD_USE_FACET)
#     define QUARK_NO_STD_USE_FACET
#  endif

//
// We can't have a std::messages facet if there is no std::locale:
//
#  if defined(QUARK_NO_STD_LOCALE) && !defined(QUARK_NO_STD_MESSAGES)
#     define QUARK_NO_STD_MESSAGES
#  endif

//
// We can't have a working std::wstreambuf if there is no std::locale:
//
#  if defined(QUARK_NO_STD_LOCALE) && !defined(QUARK_NO_STD_WSTREAMBUF)
#     define QUARK_NO_STD_WSTREAMBUF
#  endif

//
// We can't have a <cwctype> if there is no <cwchar>:
//
#  if defined(QUARK_NO_CWCHAR) && !defined(QUARK_NO_CWCTYPE)
#     define QUARK_NO_CWCTYPE
#  endif

//
// We can't have a swprintf if there is no <cwchar>:
//
#  if defined(QUARK_NO_CWCHAR) && !defined(QUARK_NO_SWPRINTF)
#     define QUARK_NO_SWPRINTF
#  endif

//
// If Win32 support is turned off, then we must turn off
// threading support also, unless there is some other
// thread API enabled:
//
#if defined(QUARK_DISABLE_WIN32) && defined(_WIN32) \
   && !defined(QUARK_DISABLE_THREADS) && !defined(QUARK_HAS_PTHREADS)
#  define QUARK_DISABLE_THREADS
#endif

//
// Turn on threading support if the compiler thinks that it's in
// multithreaded mode.  We put this here because there are only a
// limited number of macros that identify this (if there's any missing
// from here then add to the appropriate compiler section):
//
#if (defined(__MT__) || defined(_MT) || defined(_REENTRANT) \
    || defined(_PTHREADS) || defined(__APPLE__) || defined(__DragonFly__)) \
    && !defined(QUARK_HAS_THREADS)
#  define QUARK_HAS_THREADS
#endif

//
// Turn threading support off if QUARK_DISABLE_THREADS is defined:
//
#if defined(QUARK_DISABLE_THREADS) && defined(QUARK_HAS_THREADS)
#  undef QUARK_HAS_THREADS
#endif

//
// Turn threading support off if we don't recognise the threading API:
//
#if defined(QUARK_HAS_THREADS) && !defined(QUARK_HAS_PTHREADS)\
      && !defined(QUARK_HAS_WINTHREADS) && !defined(QUARK_HAS_BETHREADS)\
      && !defined(QUARK_HAS_MPTASKS)
#  undef QUARK_HAS_THREADS
#endif

//
// Turn threading detail macros off if we don't (want to) use threading
//
#ifndef QUARK_HAS_THREADS
#  undef QUARK_HAS_PTHREADS
#  undef QUARK_HAS_PTHREAD_MUTEXATTR_SETTYPE
#  undef QUARK_HAS_PTHREAD_YIELD
#  undef QUARK_HAS_PTHREAD_DELAY_NP
#  undef QUARK_HAS_WINTHREADS
#  undef QUARK_HAS_BETHREADS
#  undef QUARK_HAS_MPTASKS
#endif

//
// If the compiler claims to be C99 conformant, then it had better
// have a <stdint.h>:
//
#  if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#     define QUARK_HAS_STDINT_H
#     ifndef QUARK_HAS_LOG1P
#        define QUARK_HAS_LOG1P
#     endif
#     ifndef QUARK_HAS_EXPM1
#        define QUARK_HAS_EXPM1
#     endif
#  endif

//
// Define QUARK_NO_SLIST and QUARK_NO_HASH if required.
// Note that this is for backwards compatibility only.
//
#  if !defined(QUARK_HAS_SLIST) && !defined(QUARK_NO_SLIST)
#     define QUARK_NO_SLIST
#  endif

#  if !defined(QUARK_HAS_HASH) && !defined(QUARK_NO_HASH)
#     define QUARK_NO_HASH
#  endif

//
// Set QUARK_SLIST_HEADER if not set already:
//
#if defined(QUARK_HAS_SLIST) && !defined(QUARK_SLIST_HEADER)
#  define QUARK_SLIST_HEADER <slist>
#endif

//
// Set QUARK_HASH_SET_HEADER if not set already:
//
#if defined(QUARK_HAS_HASH) && !defined(QUARK_HASH_SET_HEADER)
#  define QUARK_HASH_SET_HEADER <hash_set>
#endif

//
// Set QUARK_HASH_MAP_HEADER if not set already:
//
#if defined(QUARK_HAS_HASH) && !defined(QUARK_HASH_MAP_HEADER)
#  define QUARK_HASH_MAP_HEADER <hash_map>
#endif

//  QUARK_HAS_ABI_HEADERS
//  This macro gets set if we have headers that fix the ABI,
//  and prevent ODR violations when linking to external libraries:
#if defined(QUARK_ABI_PREFIX) && defined(QUARK_ABI_SUFFIX) && !defined(QUARK_HAS_ABI_HEADERS)
#  define QUARK_HAS_ABI_HEADERS
#endif

#if defined(QUARK_HAS_ABI_HEADERS) && defined(QUARK_DISABLE_ABI_HEADERS)
#  undef QUARK_HAS_ABI_HEADERS
#endif

//  QUARK_NO_STDC_NAMESPACE workaround  --------------------------------------//
//  Because std::size_t usage is so common, even in quark headers which do not
//  otherwise use the C library, the <cstddef> workaround is included here so
//  that ugly workaround code need not appear in many other quark headers.
//  NOTE WELL: This is a workaround for non-conforming compilers; <cstddef>
//  must still be #included in the usual places so that <cstddef> inclusion
//  works as expected with standard conforming compilers.  The resulting
//  double inclusion of <cstddef> is harmless.

# if defined(QUARK_NO_STDC_NAMESPACE) && defined(__cplusplus)
#   include <cstddef>
    namespace std { using ::ptrdiff_t; using ::size_t; }
# endif

//  Workaround for the unfortunate min/max macros defined by some platform headers

#define QUARK_PREVENT_MACRO_SUBSTITUTION

#ifndef QUARK_USING_STD_MIN
#  define QUARK_USING_STD_MIN() using std::min
#endif

#ifndef QUARK_USING_STD_MAX
#  define QUARK_USING_STD_MAX() using std::max
#endif

//  QUARK_NO_STD_MIN_MAX workaround  -----------------------------------------//

#  if defined(QUARK_NO_STD_MIN_MAX) && defined(__cplusplus)

namespace std {
  template <class _Tp>
  inline const _Tp& min QUARK_PREVENT_MACRO_SUBSTITUTION (const _Tp& __a, const _Tp& __b) {
    return __b < __a ? __b : __a;
  }
  template <class _Tp>
  inline const _Tp& max QUARK_PREVENT_MACRO_SUBSTITUTION (const _Tp& __a, const _Tp& __b) {
    return  __a < __b ? __b : __a;
  }
}

#  endif

// QUARK_STATIC_CONSTANT workaround --------------------------------------- //
// On compilers which don't allow in-class initialization of static integral
// constant members, we must use enums as a workaround if we want the constants
// to be available at compile-time. This macro gives us a convenient way to
// declare such constants.

#  ifdef QUARK_NO_INCLASS_MEMBER_INITIALIZATION
#       define QUARK_STATIC_CONSTANT(type, assignment) enum { assignment }
#  else
#     define QUARK_STATIC_CONSTANT(type, assignment) static const type assignment
#  endif

// QUARK_USE_FACET / HAS_FACET workaround ----------------------------------//
// When the standard library does not have a conforming std::use_facet there
// are various workarounds available, but they differ from library to library.
// The same problem occurs with has_facet.
// These macros provide a consistent way to access a locale's facets.
// Usage:
//    replace
//       std::use_facet<Type>(loc);
//    with
//       QUARK_USE_FACET(Type, loc);
//    Note do not add a std:: prefix to the front of QUARK_USE_FACET!
//  Use for QUARK_HAS_FACET is analogous.

#if defined(QUARK_NO_STD_USE_FACET)
#  ifdef QUARK_HAS_TWO_ARG_USE_FACET
#     define QUARK_USE_FACET(Type, loc) std::use_facet(loc, static_cast<Type*>(0))
#     define QUARK_HAS_FACET(Type, loc) std::has_facet(loc, static_cast<Type*>(0))
#  elif defined(QUARK_HAS_MACRO_USE_FACET)
#     define QUARK_USE_FACET(Type, loc) std::_USE(loc, Type)
#     define QUARK_HAS_FACET(Type, loc) std::_HAS(loc, Type)
#  elif defined(QUARK_HAS_STLP_USE_FACET)
#     define QUARK_USE_FACET(Type, loc) (*std::_Use_facet<Type >(loc))
#     define QUARK_HAS_FACET(Type, loc) std::has_facet< Type >(loc)
#  endif
#else
#  define QUARK_USE_FACET(Type, loc) std::use_facet< Type >(loc)
#  define QUARK_HAS_FACET(Type, loc) std::has_facet< Type >(loc)
#endif

// QUARK_NESTED_TEMPLATE workaround ------------------------------------------//
// Member templates are supported by some compilers even though they can't use
// the A::template member<U> syntax, as a workaround replace:
//
// typedef typename A::template rebind<U> binder;
//
// with:
//
// typedef typename A::QUARK_NESTED_TEMPLATE rebind<U> binder;

#ifndef QUARK_NO_MEMBER_TEMPLATE_KEYWORD
#  define QUARK_NESTED_TEMPLATE template
#else
#  define QUARK_NESTED_TEMPLATE
#endif

// QUARK_UNREACHABLE_RETURN(x) workaround -------------------------------------//
// Normally evaluates to nothing, unless QUARK_NO_UNREACHABLE_RETURN_DETECTION
// is defined, in which case it evaluates to return x; Use when you have a return
// statement that can never be reached.

#ifdef QUARK_NO_UNREACHABLE_RETURN_DETECTION
#  define QUARK_UNREACHABLE_RETURN(x) return x;
#else
#  define QUARK_UNREACHABLE_RETURN(x)
#endif

// QUARK_DEDUCED_TYPENAME workaround ------------------------------------------//
//
// Some compilers don't support the use of `typename' for dependent
// types in deduced contexts, e.g.
//
//     template <class T> void f(T, typename T::type);
//                                  ^^^^^^^^
// Replace these declarations with:
//
//     template <class T> void f(T, QUARK_DEDUCED_TYPENAME T::type);

#ifndef QUARK_NO_DEDUCED_TYPENAME
#  define QUARK_DEDUCED_TYPENAME typename
#else
#  define QUARK_DEDUCED_TYPENAME
#endif

#ifndef QUARK_NO_TYPENAME_WITH_CTOR
#  define QUARK_CTOR_TYPENAME typename
#else
#  define QUARK_CTOR_TYPENAME
#endif

// long long workaround ------------------------------------------//
// On gcc (and maybe other compilers?) long long is alway supported
// but it's use may generate either warnings (with -ansi), or errors
// (with -pedantic -ansi) unless it's use is prefixed by __extension__
//
#if defined(QUARK_HAS_LONG_LONG) && defined(__cplusplus)
namespace quark{
#  ifdef __GNUC__
   __extension__ typedef long long long_long_type;
   __extension__ typedef unsigned long long ulong_long_type;
#  else
   typedef long long long_long_type;
   typedef unsigned long long ulong_long_type;
#  endif
}
#endif
// same again for __int128:
#if defined(QUARK_HAS_INT128) && defined(__cplusplus)
namespace quark{
#  ifdef __GNUC__
   __extension__ typedef __int128 int128_type;
   __extension__ typedef unsigned __int128 uint128_type;
#  else
   typedef __int128 int128_type;
   typedef unsigned __int128 uint128_type;
#  endif
}
#endif

// QUARK_[APPEND_]EXPLICIT_TEMPLATE_[NON_]TYPE macros --------------------------//

// These macros are obsolete. Port away and remove.

#  define QUARK_EXPLICIT_TEMPLATE_TYPE(t)
#  define QUARK_EXPLICIT_TEMPLATE_TYPE_SPEC(t)
#  define QUARK_EXPLICIT_TEMPLATE_NON_TYPE(t, v)
#  define QUARK_EXPLICIT_TEMPLATE_NON_TYPE_SPEC(t, v)

#  define QUARK_APPEND_EXPLICIT_TEMPLATE_TYPE(t)
#  define QUARK_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(t)
#  define QUARK_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(t, v)
#  define QUARK_APPEND_EXPLICIT_TEMPLATE_NON_TYPE_SPEC(t, v)

// When QUARK_NO_STD_TYPEINFO is defined, we can just import
// the global definition into std namespace:
#if defined(QUARK_NO_STD_TYPEINFO) && defined(__cplusplus)
#include <typeinfo>
namespace std{ using ::type_info; }
#endif

// ---------------------------------------------------------------------------//

//
// Helper macro QUARK_STRINGIZE:
// Converts the parameter X to a string after macro replacement
// on X has been performed.
//
#define QUARK_STRINGIZE(X) QUARK_DO_STRINGIZE(X)
#define QUARK_DO_STRINGIZE(X) #X

//
// Helper macro QUARK_JOIN:
// The following piece of macro magic joins the two
// arguments together, even when one of the arguments is
// itself a macro (see 16.3.1 in C++ standard).  The key
// is that macro expansion of macro arguments does not
// occur in QUARK_DO_JOIN2 but does in QUARK_DO_JOIN.
//
#define QUARK_JOIN( X, Y ) QUARK_DO_JOIN( X, Y )
#define QUARK_DO_JOIN( X, Y ) QUARK_DO_JOIN2(X,Y)
#define QUARK_DO_JOIN2( X, Y ) X##Y

//
// Set some default values for compiler/library/platform names.
// These are for debugging config setup only:
//
#  ifndef QUARK_COMPILER
#     define QUARK_COMPILER "Unknown ISO C++ Compiler"
#  endif
#  ifndef QUARK_STDLIB
#     define QUARK_STDLIB "Unknown ISO standard library"
#  endif
#  ifndef QUARK_PLATFORM
#     if defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) \
         || defined(_POSIX_SOURCE)
#        define QUARK_PLATFORM "Generic Unix"
#     else
#        define QUARK_PLATFORM "Unknown"
#     endif
#  endif

//
// Set some default values GPU support
//
#  ifndef QUARK_GPU_ENABLED
#  define QUARK_GPU_ENABLED
#  endif

// QUARK_FORCEINLINE ---------------------------------------------//
// Macro to use in place of 'inline' to force a function to be inline
#if !defined(QUARK_FORCEINLINE)
#  if defined(_MSC_VER)
#    define QUARK_FORCEINLINE __forceinline
#  elif defined(__GNUC__) && __GNUC__ > 3
     // Clang also defines __GNUC__ (as 4)
#    define QUARK_FORCEINLINE inline __attribute__ ((__always_inline__))
#  else
#    define QUARK_FORCEINLINE inline
#  endif
#endif

// QUARK_NOINLINE ---------------------------------------------//
// Macro to use in place of 'inline' to prevent a function to be inlined
#if !defined(QUARK_NOINLINE)
#  if defined(_MSC_VER)
#    define QUARK_NOINLINE __declspec(noinline)
#  elif defined(__GNUC__) && __GNUC__ > 3
     // Clang also defines __GNUC__ (as 4)
#    if defined(__CUDACC__)
       // nvcc doesn't always parse __noinline__, 
       // see: https://svn.quark.org/trac/quark/ticket/9392
#      define QUARK_NOINLINE __attribute__ ((noinline))
#    else
#      define QUARK_NOINLINE __attribute__ ((__noinline__))
#    endif
#  else
#    define QUARK_NOINLINE
#  endif
#endif

// QUARK_NORETURN ---------------------------------------------//
// Macro to use before a function declaration/definition to designate
// the function as not returning normally (i.e. with a return statement
// or by leaving the function scope, if the function return type is void).
#if !defined(QUARK_NORETURN)
#  if defined(_MSC_VER)
#    define QUARK_NORETURN __declspec(noreturn)
#  elif defined(__GNUC__)
#    define QUARK_NORETURN __attribute__ ((__noreturn__))
#  else
#    define QUARK_NO_NORETURN
#    define QUARK_NORETURN
#  endif
#endif

// Branch prediction hints
// These macros are intended to wrap conditional expressions that yield true or false
//
//  if (QUARK_LIKELY(var == 10))
//  {
//     // the most probable code here
//  }
//
#if !defined(QUARK_LIKELY)
#  define QUARK_LIKELY(x) x
#endif
#if !defined(QUARK_UNLIKELY)
#  define QUARK_UNLIKELY(x) x
#endif

// Type and data alignment specification
//
#if !defined(QUARK_NO_CXX11_ALIGNAS)
#  define QUARK_ALIGNMENT(x) alignas(x)
#elif defined(_MSC_VER)
#  define QUARK_ALIGNMENT(x) __declspec(align(x))
#elif defined(__GNUC__)
#  define QUARK_ALIGNMENT(x) __attribute__ ((__aligned__(x)))
#else
#  define QUARK_NO_ALIGNMENT
#  define QUARK_ALIGNMENT(x)
#endif

// Lack of non-public defaulted functions is implied by the lack of any defaulted functions
#if !defined(QUARK_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS) && defined(QUARK_NO_CXX11_DEFAULTED_FUNCTIONS)
#  define QUARK_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS
#endif

// Defaulted and deleted function declaration helpers
// These macros are intended to be inside a class definition.
// QUARK_DEFAULTED_FUNCTION accepts the function declaration and its
// body, which will be used if the compiler doesn't support defaulted functions.
// QUARK_DELETED_FUNCTION only accepts the function declaration. It
// will expand to a private function declaration, if the compiler doesn't support
// deleted functions. Because of this it is recommended to use QUARK_DELETED_FUNCTION
// in the end of the class definition.
//
//  class my_class
//  {
//  public:
//      // Default-constructible
//      QUARK_DEFAULTED_FUNCTION(my_class(), {})
//      // Copying prohibited
//      QUARK_DELETED_FUNCTION(my_class(my_class const&))
//      QUARK_DELETED_FUNCTION(my_class& operator= (my_class const&))
//  };
//
#if !(defined(QUARK_NO_CXX11_DEFAULTED_FUNCTIONS) || defined(QUARK_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS))
#   define QUARK_DEFAULTED_FUNCTION(fun, body) fun = default;
#else
#   define QUARK_DEFAULTED_FUNCTION(fun, body) fun body
#endif

#if !defined(QUARK_NO_CXX11_DELETED_FUNCTIONS)
#   define QUARK_DELETED_FUNCTION(fun) fun = delete;
#else
#   define QUARK_DELETED_FUNCTION(fun) private: fun;
#endif

//
// Set QUARK_NO_DECLTYPE_N3276 when QUARK_NO_DECLTYPE is defined
//
#if defined(QUARK_NO_CXX11_DECLTYPE) && !defined(QUARK_NO_CXX11_DECLTYPE_N3276)
#define QUARK_NO_CXX11_DECLTYPE_N3276 QUARK_NO_CXX11_DECLTYPE
#endif

//  -------------------- Deprecated macros for 1.50 ---------------------------
//  These will go away in a future release

//  Use QUARK_NO_CXX11_HDR_UNORDERED_SET or QUARK_NO_CXX11_HDR_UNORDERED_MAP
//           instead of QUARK_NO_STD_UNORDERED
#if defined(QUARK_NO_CXX11_HDR_UNORDERED_MAP) || defined (QUARK_NO_CXX11_HDR_UNORDERED_SET)
# ifndef QUARK_NO_CXX11_STD_UNORDERED
#  define QUARK_NO_CXX11_STD_UNORDERED
# endif
#endif

//  Use QUARK_NO_CXX11_HDR_INITIALIZER_LIST instead of QUARK_NO_INITIALIZER_LISTS
#if defined(QUARK_NO_CXX11_HDR_INITIALIZER_LIST) && !defined(QUARK_NO_INITIALIZER_LISTS)
#  define QUARK_NO_INITIALIZER_LISTS
#endif

//  Use QUARK_NO_CXX11_HDR_ARRAY instead of QUARK_NO_0X_HDR_ARRAY
#if defined(QUARK_NO_CXX11_HDR_ARRAY) && !defined(QUARK_NO_0X_HDR_ARRAY)
#  define QUARK_NO_0X_HDR_ARRAY
#endif
//  Use QUARK_NO_CXX11_HDR_CHRONO instead of QUARK_NO_0X_HDR_CHRONO
#if defined(QUARK_NO_CXX11_HDR_CHRONO) && !defined(QUARK_NO_0X_HDR_CHRONO)
#  define QUARK_NO_0X_HDR_CHRONO
#endif
//  Use QUARK_NO_CXX11_HDR_CODECVT instead of QUARK_NO_0X_HDR_CODECVT
#if defined(QUARK_NO_CXX11_HDR_CODECVT) && !defined(QUARK_NO_0X_HDR_CODECVT)
#  define QUARK_NO_0X_HDR_CODECVT
#endif
//  Use QUARK_NO_CXX11_HDR_CONDITION_VARIABLE instead of QUARK_NO_0X_HDR_CONDITION_VARIABLE
#if defined(QUARK_NO_CXX11_HDR_CONDITION_VARIABLE) && !defined(QUARK_NO_0X_HDR_CONDITION_VARIABLE)
#  define QUARK_NO_0X_HDR_CONDITION_VARIABLE
#endif
//  Use QUARK_NO_CXX11_HDR_FORWARD_LIST instead of QUARK_NO_0X_HDR_FORWARD_LIST
#if defined(QUARK_NO_CXX11_HDR_FORWARD_LIST) && !defined(QUARK_NO_0X_HDR_FORWARD_LIST)
#  define QUARK_NO_0X_HDR_FORWARD_LIST
#endif
//  Use QUARK_NO_CXX11_HDR_FUTURE instead of QUARK_NO_0X_HDR_FUTURE
#if defined(QUARK_NO_CXX11_HDR_FUTURE) && !defined(QUARK_NO_0X_HDR_FUTURE)
#  define QUARK_NO_0X_HDR_FUTURE
#endif

//  Use QUARK_NO_CXX11_HDR_INITIALIZER_LIST
//  instead of QUARK_NO_0X_HDR_INITIALIZER_LIST or QUARK_NO_INITIALIZER_LISTS
#ifdef QUARK_NO_CXX11_HDR_INITIALIZER_LIST
# ifndef QUARK_NO_0X_HDR_INITIALIZER_LIST
#  define QUARK_NO_0X_HDR_INITIALIZER_LIST
# endif
# ifndef QUARK_NO_INITIALIZER_LISTS
#  define QUARK_NO_INITIALIZER_LISTS
# endif
#endif

//  Use QUARK_NO_CXX11_HDR_MUTEX instead of QUARK_NO_0X_HDR_MUTEX
#if defined(QUARK_NO_CXX11_HDR_MUTEX) && !defined(QUARK_NO_0X_HDR_MUTEX)
#  define QUARK_NO_0X_HDR_MUTEX
#endif
//  Use QUARK_NO_CXX11_HDR_RANDOM instead of QUARK_NO_0X_HDR_RANDOM
#if defined(QUARK_NO_CXX11_HDR_RANDOM) && !defined(QUARK_NO_0X_HDR_RANDOM)
#  define QUARK_NO_0X_HDR_RANDOM
#endif
//  Use QUARK_NO_CXX11_HDR_RATIO instead of QUARK_NO_0X_HDR_RATIO
#if defined(QUARK_NO_CXX11_HDR_RATIO) && !defined(QUARK_NO_0X_HDR_RATIO)
#  define QUARK_NO_0X_HDR_RATIO
#endif
//  Use QUARK_NO_CXX11_HDR_REGEX instead of QUARK_NO_0X_HDR_REGEX
#if defined(QUARK_NO_CXX11_HDR_REGEX) && !defined(QUARK_NO_0X_HDR_REGEX)
#  define QUARK_NO_0X_HDR_REGEX
#endif
//  Use QUARK_NO_CXX11_HDR_SYSTEM_ERROR instead of QUARK_NO_0X_HDR_SYSTEM_ERROR
#if defined(QUARK_NO_CXX11_HDR_SYSTEM_ERROR) && !defined(QUARK_NO_0X_HDR_SYSTEM_ERROR)
#  define QUARK_NO_0X_HDR_SYSTEM_ERROR
#endif
//  Use QUARK_NO_CXX11_HDR_THREAD instead of QUARK_NO_0X_HDR_THREAD
#if defined(QUARK_NO_CXX11_HDR_THREAD) && !defined(QUARK_NO_0X_HDR_THREAD)
#  define QUARK_NO_0X_HDR_THREAD
#endif
//  Use QUARK_NO_CXX11_HDR_TUPLE instead of QUARK_NO_0X_HDR_TUPLE
#if defined(QUARK_NO_CXX11_HDR_TUPLE) && !defined(QUARK_NO_0X_HDR_TUPLE)
#  define QUARK_NO_0X_HDR_TUPLE
#endif
//  Use QUARK_NO_CXX11_HDR_TYPE_TRAITS instead of QUARK_NO_0X_HDR_TYPE_TRAITS
#if defined(QUARK_NO_CXX11_HDR_TYPE_TRAITS) && !defined(QUARK_NO_0X_HDR_TYPE_TRAITS)
#  define QUARK_NO_0X_HDR_TYPE_TRAITS
#endif
//  Use QUARK_NO_CXX11_HDR_TYPEINDEX instead of QUARK_NO_0X_HDR_TYPEINDEX
#if defined(QUARK_NO_CXX11_HDR_TYPEINDEX) && !defined(QUARK_NO_0X_HDR_TYPEINDEX)
#  define QUARK_NO_0X_HDR_TYPEINDEX
#endif
//  Use QUARK_NO_CXX11_HDR_UNORDERED_MAP instead of QUARK_NO_0X_HDR_UNORDERED_MAP
#if defined(QUARK_NO_CXX11_HDR_UNORDERED_MAP) && !defined(QUARK_NO_0X_HDR_UNORDERED_MAP)
#  define QUARK_NO_0X_HDR_UNORDERED_MAP
#endif
//  Use QUARK_NO_CXX11_HDR_UNORDERED_SET instead of QUARK_NO_0X_HDR_UNORDERED_SET
#if defined(QUARK_NO_CXX11_HDR_UNORDERED_SET) && !defined(QUARK_NO_0X_HDR_UNORDERED_SET)
#  define QUARK_NO_0X_HDR_UNORDERED_SET
#endif

//  ------------------ End of deprecated macros for 1.50 ---------------------------

//  -------------------- Deprecated macros for 1.51 ---------------------------
//  These will go away in a future release

//  Use     QUARK_NO_CXX11_AUTO_DECLARATIONS instead of   QUARK_NO_AUTO_DECLARATIONS
#if defined(QUARK_NO_CXX11_AUTO_DECLARATIONS) && !defined(QUARK_NO_AUTO_DECLARATIONS)
#  define QUARK_NO_AUTO_DECLARATIONS
#endif
//  Use     QUARK_NO_CXX11_AUTO_MULTIDECLARATIONS instead of   QUARK_NO_AUTO_MULTIDECLARATIONS
#if defined(QUARK_NO_CXX11_AUTO_MULTIDECLARATIONS) && !defined(QUARK_NO_AUTO_MULTIDECLARATIONS)
#  define QUARK_NO_AUTO_MULTIDECLARATIONS
#endif
//  Use     QUARK_NO_CXX11_CHAR16_T instead of   QUARK_NO_CHAR16_T
#if defined(QUARK_NO_CXX11_CHAR16_T) && !defined(QUARK_NO_CHAR16_T)
#  define QUARK_NO_CHAR16_T
#endif
//  Use     QUARK_NO_CXX11_CHAR32_T instead of   QUARK_NO_CHAR32_T
#if defined(QUARK_NO_CXX11_CHAR32_T) && !defined(QUARK_NO_CHAR32_T)
#  define QUARK_NO_CHAR32_T
#endif
//  Use     QUARK_NO_CXX11_TEMPLATE_ALIASES instead of   QUARK_NO_TEMPLATE_ALIASES
#if defined(QUARK_NO_CXX11_TEMPLATE_ALIASES) && !defined(QUARK_NO_TEMPLATE_ALIASES)
#  define QUARK_NO_TEMPLATE_ALIASES
#endif
//  Use     QUARK_NO_CXX11_CONSTEXPR instead of   QUARK_NO_CONSTEXPR
#if defined(QUARK_NO_CXX11_CONSTEXPR) && !defined(QUARK_NO_CONSTEXPR)
#  define QUARK_NO_CONSTEXPR
#endif
//  Use     QUARK_NO_CXX11_DECLTYPE_N3276 instead of   QUARK_NO_DECLTYPE_N3276
#if defined(QUARK_NO_CXX11_DECLTYPE_N3276) && !defined(QUARK_NO_DECLTYPE_N3276)
#  define QUARK_NO_DECLTYPE_N3276
#endif
//  Use     QUARK_NO_CXX11_DECLTYPE instead of   QUARK_NO_DECLTYPE
#if defined(QUARK_NO_CXX11_DECLTYPE) && !defined(QUARK_NO_DECLTYPE)
#  define QUARK_NO_DECLTYPE
#endif
//  Use     QUARK_NO_CXX11_DEFAULTED_FUNCTIONS instead of   QUARK_NO_DEFAULTED_FUNCTIONS
#if defined(QUARK_NO_CXX11_DEFAULTED_FUNCTIONS) && !defined(QUARK_NO_DEFAULTED_FUNCTIONS)
#  define QUARK_NO_DEFAULTED_FUNCTIONS
#endif
//  Use     QUARK_NO_CXX11_DELETED_FUNCTIONS instead of   QUARK_NO_DELETED_FUNCTIONS
#if defined(QUARK_NO_CXX11_DELETED_FUNCTIONS) && !defined(QUARK_NO_DELETED_FUNCTIONS)
#  define QUARK_NO_DELETED_FUNCTIONS
#endif
//  Use     QUARK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS instead of   QUARK_NO_EXPLICIT_CONVERSION_OPERATORS
#if defined(QUARK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS) && !defined(QUARK_NO_EXPLICIT_CONVERSION_OPERATORS)
#  define QUARK_NO_EXPLICIT_CONVERSION_OPERATORS
#endif
//  Use     QUARK_NO_CXX11_EXTERN_TEMPLATE instead of   QUARK_NO_EXTERN_TEMPLATE
#if defined(QUARK_NO_CXX11_EXTERN_TEMPLATE) && !defined(QUARK_NO_EXTERN_TEMPLATE)
#  define QUARK_NO_EXTERN_TEMPLATE
#endif
//  Use     QUARK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS instead of   QUARK_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS
#if defined(QUARK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS) && !defined(QUARK_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS)
#  define QUARK_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS
#endif
//  Use     QUARK_NO_CXX11_LAMBDAS instead of   QUARK_NO_LAMBDAS
#if defined(QUARK_NO_CXX11_LAMBDAS) && !defined(QUARK_NO_LAMBDAS)
#  define QUARK_NO_LAMBDAS
#endif
//  Use     QUARK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS instead of   QUARK_NO_LOCAL_CLASS_TEMPLATE_PARAMETERS
#if defined(QUARK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS) && !defined(QUARK_NO_LOCAL_CLASS_TEMPLATE_PARAMETERS)
#  define QUARK_NO_LOCAL_CLASS_TEMPLATE_PARAMETERS
#endif
//  Use     QUARK_NO_CXX11_NOEXCEPT instead of   QUARK_NO_NOEXCEPT
#if defined(QUARK_NO_CXX11_NOEXCEPT) && !defined(QUARK_NO_NOEXCEPT)
#  define QUARK_NO_NOEXCEPT
#endif
//  Use     QUARK_NO_CXX11_NULLPTR instead of   QUARK_NO_NULLPTR
#if defined(QUARK_NO_CXX11_NULLPTR) && !defined(QUARK_NO_NULLPTR)
#  define QUARK_NO_NULLPTR
#endif
//  Use     QUARK_NO_CXX11_RAW_LITERALS instead of   QUARK_NO_RAW_LITERALS
#if defined(QUARK_NO_CXX11_RAW_LITERALS) && !defined(QUARK_NO_RAW_LITERALS)
#  define QUARK_NO_RAW_LITERALS
#endif
//  Use     QUARK_NO_CXX11_RVALUE_REFERENCES instead of   QUARK_NO_RVALUE_REFERENCES
#if defined(QUARK_NO_CXX11_RVALUE_REFERENCES) && !defined(QUARK_NO_RVALUE_REFERENCES)
#  define QUARK_NO_RVALUE_REFERENCES
#endif
//  Use     QUARK_NO_CXX11_SCOPED_ENUMS instead of   QUARK_NO_SCOPED_ENUMS
#if defined(QUARK_NO_CXX11_SCOPED_ENUMS) && !defined(QUARK_NO_SCOPED_ENUMS)
#  define QUARK_NO_SCOPED_ENUMS
#endif
//  Use     QUARK_NO_CXX11_STATIC_ASSERT instead of   QUARK_NO_STATIC_ASSERT
#if defined(QUARK_NO_CXX11_STATIC_ASSERT) && !defined(QUARK_NO_STATIC_ASSERT)
#  define QUARK_NO_STATIC_ASSERT
#endif
//  Use     QUARK_NO_CXX11_STD_UNORDERED instead of   QUARK_NO_STD_UNORDERED
#if defined(QUARK_NO_CXX11_STD_UNORDERED) && !defined(QUARK_NO_STD_UNORDERED)
#  define QUARK_NO_STD_UNORDERED
#endif
//  Use     QUARK_NO_CXX11_UNICODE_LITERALS instead of   QUARK_NO_UNICODE_LITERALS
#if defined(QUARK_NO_CXX11_UNICODE_LITERALS) && !defined(QUARK_NO_UNICODE_LITERALS)
#  define QUARK_NO_UNICODE_LITERALS
#endif
//  Use     QUARK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX instead of   QUARK_NO_UNIFIED_INITIALIZATION_SYNTAX
#if defined(QUARK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX) && !defined(QUARK_NO_UNIFIED_INITIALIZATION_SYNTAX)
#  define QUARK_NO_UNIFIED_INITIALIZATION_SYNTAX
#endif
//  Use     QUARK_NO_CXX11_VARIADIC_TEMPLATES instead of   QUARK_NO_VARIADIC_TEMPLATES
#if defined(QUARK_NO_CXX11_VARIADIC_TEMPLATES) && !defined(QUARK_NO_VARIADIC_TEMPLATES)
#  define QUARK_NO_VARIADIC_TEMPLATES
#endif
//  Use     QUARK_NO_CXX11_VARIADIC_MACROS instead of   QUARK_NO_VARIADIC_MACROS
#if defined(QUARK_NO_CXX11_VARIADIC_MACROS) && !defined(QUARK_NO_VARIADIC_MACROS)
#  define QUARK_NO_VARIADIC_MACROS
#endif
//  Use     QUARK_NO_CXX11_NUMERIC_LIMITS instead of   QUARK_NO_NUMERIC_LIMITS_LOWEST
#if defined(QUARK_NO_CXX11_NUMERIC_LIMITS) && !defined(QUARK_NO_NUMERIC_LIMITS_LOWEST)
#  define QUARK_NO_NUMERIC_LIMITS_LOWEST
#endif
//  ------------------ End of deprecated macros for 1.51 ---------------------------



//
// Helper macros QUARK_NOEXCEPT, QUARK_NOEXCEPT_IF, QUARK_NOEXCEPT_EXPR
// These aid the transition to C++11 while still supporting C++03 compilers
//
#ifdef QUARK_NO_CXX11_NOEXCEPT
#  define QUARK_NOEXCEPT
#  define QUARK_NOEXCEPT_OR_NOTHROW throw()
#  define QUARK_NOEXCEPT_IF(Predicate)
#  define QUARK_NOEXCEPT_EXPR(Expression) false
#else
#  define QUARK_NOEXCEPT noexcept
#  define QUARK_NOEXCEPT_OR_NOTHROW noexcept
#  define QUARK_NOEXCEPT_IF(Predicate) noexcept((Predicate))
#  define QUARK_NOEXCEPT_EXPR(Expression) noexcept((Expression))
#endif
//
// Helper macro QUARK_FALLTHROUGH
// Fallback definition of QUARK_FALLTHROUGH macro used to mark intended
// fall-through between case labels in a switch statement. We use a definition
// that requires a semicolon after it to avoid at least one type of misuse even
// on unsupported compilers.
//
#ifndef QUARK_FALLTHROUGH
#  define QUARK_FALLTHROUGH ((void)0)
#endif

//
// constexpr workarounds
//
#if defined(QUARK_NO_CXX11_CONSTEXPR)
#define QUARK_CONSTEXPR
#define QUARK_CONSTEXPR_OR_CONST const
#else
#define QUARK_CONSTEXPR constexpr
#define QUARK_CONSTEXPR_OR_CONST constexpr
#endif
#if defined(QUARK_NO_CXX14_CONSTEXPR)
#define QUARK_CXX14_CONSTEXPR
#else
#define QUARK_CXX14_CONSTEXPR constexpr
#endif

//
// Unused variable/typedef workarounds:
//
#ifndef QUARK_ATTRIBUTE_UNUSED
#  define QUARK_ATTRIBUTE_UNUSED
#endif

#define QUARK_STATIC_CONSTEXPR  static QUARK_CONSTEXPR_OR_CONST

//
// Set QUARK_HAS_STATIC_ASSERT when QUARK_NO_CXX11_STATIC_ASSERT is not defined
//
#if !defined(QUARK_NO_CXX11_STATIC_ASSERT) && !defined(QUARK_HAS_STATIC_ASSERT)
#  define QUARK_HAS_STATIC_ASSERT
#endif

//
// Set QUARK_HAS_RVALUE_REFS when QUARK_NO_CXX11_RVALUE_REFERENCES is not defined
//
#if !defined(QUARK_NO_CXX11_RVALUE_REFERENCES) && !defined(QUARK_HAS_RVALUE_REFS)
#define QUARK_HAS_RVALUE_REFS
#endif

//
// Set QUARK_HAS_VARIADIC_TMPL when QUARK_NO_CXX11_VARIADIC_TEMPLATES is not defined
//
#if !defined(QUARK_NO_CXX11_VARIADIC_TEMPLATES) && !defined(QUARK_HAS_VARIADIC_TMPL)
#define QUARK_HAS_VARIADIC_TMPL
#endif
//
// Set QUARK_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS when
// QUARK_NO_CXX11_VARIADIC_TEMPLATES is set:
//
#if defined(QUARK_NO_CXX11_VARIADIC_TEMPLATES) && !defined(QUARK_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS)
#  define QUARK_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS
#endif

//
// Finish off with checks for macros that are depricated / no longer supported,
// if any of these are set then it's very likely that much of Boost will no
// longer work.  So stop with a #error for now, but give the user a chance
// to continue at their own risk if they really want to:
//
#if defined(QUARK_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(QUARK_CONFIG_ALLOW_DEPRECATED)
#  error "You are using a compiler which lacks features which are now a minimum requirement in order to use Boost, define QUARK_CONFIG_ALLOW_DEPRECATED if you want to continue at your own risk!!!"
#endif

#endif
