//  (C) Copyright Bryce Lelbach 2011

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

// PathScale EKOPath C++ Compiler

#ifndef QUARK_COMPILER
#  define QUARK_COMPILER "PathScale EKOPath C++ Compiler version " __PATHSCALE__
#endif

#if __PATHCC__ >= 4
#  define QUARK_MSVC6_MEMBER_TEMPLATES
#  define QUARK_HAS_UNISTD_H
#  define QUARK_HAS_STDINT_H
#  define QUARK_HAS_SIGACTION
#  define QUARK_HAS_SCHED_YIELD
#  define QUARK_HAS_THREADS
#  define QUARK_HAS_PTHREADS
#  define QUARK_HAS_PTHREAD_YIELD
#  define QUARK_HAS_PTHREAD_MUTEXATTR_SETTYPE
#  define QUARK_HAS_PARTIAL_STD_ALLOCATOR
#  define QUARK_HAS_NRVO
#  define QUARK_HAS_NL_TYPES_H
#  define QUARK_HAS_NANOSLEEP
#  define QUARK_HAS_LONG_LONG
#  define QUARK_HAS_LOG1P
#  define QUARK_HAS_GETTIMEOFDAY
#  define QUARK_HAS_EXPM1
#  define QUARK_HAS_DIRENT_H
#  define QUARK_HAS_CLOCK_GETTIME
#  define QUARK_NO_CXX11_VARIADIC_TEMPLATES
#  define QUARK_NO_CXX11_UNICODE_LITERALS
#  define QUARK_NO_CXX11_TEMPLATE_ALIASES
#  define QUARK_NO_CXX11_STATIC_ASSERT
#  define QUARK_NO_SFINAE_EXPR
#  define QUARK_NO_CXX11_SCOPED_ENUMS
#  define QUARK_NO_CXX11_RVALUE_REFERENCES
#  define QUARK_NO_CXX11_RANGE_BASED_FOR
#  define QUARK_NO_CXX11_RAW_LITERALS
#  define QUARK_NO_CXX11_NULLPTR
#  define QUARK_NO_CXX11_NUMERIC_LIMITS
#  define QUARK_NO_CXX11_NOEXCEPT
#  define QUARK_NO_CXX11_LAMBDAS
#  define QUARK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#  define QUARK_NO_MS_INT64_NUMERIC_LIMITS
#  define QUARK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#  define QUARK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#  define QUARK_NO_CXX11_DELETED_FUNCTIONS
#  define QUARK_NO_CXX11_DEFAULTED_FUNCTIONS
#  define QUARK_NO_CXX11_DECLTYPE
#  define QUARK_NO_CXX11_DECLTYPE_N3276
#  define QUARK_NO_CXX11_CONSTEXPR
#  define QUARK_NO_COMPLETE_VALUE_INITIALIZATION
#  define QUARK_NO_CXX11_CHAR32_T
#  define QUARK_NO_CXX11_CHAR16_T
#  define QUARK_NO_CXX11_AUTO_MULTIDECLARATIONS
#  define QUARK_NO_CXX11_AUTO_DECLARATIONS
#  define QUARK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#  define QUARK_NO_CXX11_HDR_UNORDERED_SET
#  define QUARK_NO_CXX11_HDR_UNORDERED_MAP
#  define QUARK_NO_CXX11_HDR_TYPEINDEX
#  define QUARK_NO_CXX11_HDR_TUPLE
#  define QUARK_NO_CXX11_HDR_THREAD
#  define QUARK_NO_CXX11_HDR_SYSTEM_ERROR
#  define QUARK_NO_CXX11_HDR_REGEX
#  define QUARK_NO_CXX11_HDR_RATIO
#  define QUARK_NO_CXX11_HDR_RANDOM
#  define QUARK_NO_CXX11_HDR_MUTEX
#  define QUARK_NO_CXX11_HDR_INITIALIZER_LIST
#  define QUARK_NO_CXX11_HDR_FUTURE
#  define QUARK_NO_CXX11_HDR_FORWARD_LIST
#  define QUARK_NO_CXX11_HDR_CONDITION_VARIABLE
#  define QUARK_NO_CXX11_HDR_CODECVT
#  define QUARK_NO_CXX11_HDR_CHRONO
#  define QUARK_NO_CXX11_USER_DEFINED_LITERALS
#  define QUARK_NO_CXX11_ALIGNAS
#  define QUARK_NO_CXX11_TRAILING_RESULT_TYPES
#  define QUARK_NO_CXX11_INLINE_NAMESPACES
#  define QUARK_NO_CXX11_REF_QUALIFIERS
#  define QUARK_NO_CXX11_FINAL

// C++ 14:
#if !defined(__cpp_aggregate_nsdmi) || (__cpp_aggregate_nsdmi < 201304)
#  define QUARK_NO_CXX14_AGGREGATE_NSDMI
#endif
#if !defined(__cpp_binary_literals) || (__cpp_binary_literals < 201304)
#  define QUARK_NO_CXX14_BINARY_LITERALS
#endif
#if !defined(__cpp_constexpr) || (__cpp_constexpr < 201304)
#  define QUARK_NO_CXX14_CONSTEXPR
#endif
#if !defined(__cpp_decltype_auto) || (__cpp_decltype_auto < 201304)
#  define QUARK_NO_CXX14_DECLTYPE_AUTO
#endif
#if (__cplusplus < 201304) // There's no SD6 check for this....
#  define QUARK_NO_CXX14_DIGIT_SEPARATORS
#endif
#if !defined(__cpp_generic_lambdas) || (__cpp_generic_lambdas < 201304)
#  define QUARK_NO_CXX14_GENERIC_LAMBDAS
#endif
#if !defined(__cpp_init_captures) || (__cpp_init_captures < 201304)
#  define QUARK_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#endif
#if !defined(__cpp_return_type_deduction) || (__cpp_return_type_deduction < 201304)
#  define QUARK_NO_CXX14_RETURN_TYPE_DEDUCTION
#endif
#if !defined(__cpp_variable_templates) || (__cpp_variable_templates < 201304)
#  define QUARK_NO_CXX14_VARIABLE_TEMPLATES
#endif
#endif
