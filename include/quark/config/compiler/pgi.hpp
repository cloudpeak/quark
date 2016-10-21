//  (C) Copyright Noel Belcourt 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

//  PGI C++ compiler setup:

#define QUARK_COMPILER_VERSION __PGIC__##__PGIC_MINOR__
#define QUARK_COMPILER "PGI compiler version " QUARK_STRINGIZE(QUARK_COMPILER_VERSION)

//
// Threading support:
// Turn this on unconditionally here, it will get turned off again later
// if no threading API is detected.
//

#if __PGIC__ >= 11

// options requested by configure --enable-test
#define QUARK_HAS_PTHREADS
#define QUARK_HAS_THREADS
#define QUARK_HAS_PTHREAD_YIELD
#define QUARK_HAS_NRVO
#define QUARK_HAS_LONG_LONG

// options --enable-test wants undefined
#undef QUARK_NO_STDC_NAMESPACE
#undef QUARK_NO_EXCEPTION_STD_NAMESPACE
#undef QUARK_DEDUCED_TYPENAME

#define QUARK_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#define QUARK_NO_TWO_PHASE_NAME_LOOKUP
#define QUARK_NO_CXX11_AUTO_MULTIDECLARATIONS
#define QUARK_NO_CXX11_AUTO_DECLARATIONS

#elif __PGIC__ >= 10

// options requested by configure --enable-test
#define QUARK_HAS_THREADS
#define QUARK_HAS_NRVO
#define QUARK_HAS_LONG_LONG
#if defined(linux) || defined(__linux) || defined(__linux__)
#  define QUARK_HAS_STDINT_H
#endif

// options --enable-test wants undefined
#undef QUARK_NO_STDC_NAMESPACE
#undef QUARK_NO_EXCEPTION_STD_NAMESPACE
#undef QUARK_DEDUCED_TYPENAME

#elif __PGIC__ >= 7

#define QUARK_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#define QUARK_NO_TWO_PHASE_NAME_LOOKUP
#define QUARK_NO_SWPRINTF
#define QUARK_NO_CXX11_AUTO_MULTIDECLARATIONS
#define QUARK_NO_CXX11_AUTO_DECLARATIONS

#else

#  error "Pgi compiler not configured - please reconfigure"

#endif
//
// C++0x features
//
//   See quark\config\suffix.hpp for QUARK_NO_LONG_LONG
//
#define QUARK_NO_CXX11_CHAR16_T
#define QUARK_NO_CXX11_CHAR32_T
#define QUARK_NO_CXX11_CONSTEXPR
#define QUARK_NO_CXX11_DECLTYPE
#define QUARK_NO_CXX11_DECLTYPE_N3276
#define QUARK_NO_CXX11_DEFAULTED_FUNCTIONS
#define QUARK_NO_CXX11_DELETED_FUNCTIONS
#define QUARK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#define QUARK_NO_CXX11_EXTERN_TEMPLATE
#define QUARK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define QUARK_NO_CXX11_LAMBDAS
#define QUARK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define QUARK_NO_CXX11_NOEXCEPT
#define QUARK_NO_CXX11_NULLPTR
#define QUARK_NO_CXX11_NUMERIC_LIMITS
#define QUARK_NO_CXX11_RANGE_BASED_FOR
#define QUARK_NO_CXX11_RAW_LITERALS
#define QUARK_NO_CXX11_RVALUE_REFERENCES
#define QUARK_NO_CXX11_SCOPED_ENUMS
#define QUARK_NO_SFINAE_EXPR
#define QUARK_NO_CXX11_STATIC_ASSERT
#define QUARK_NO_SWPRINTF
#define QUARK_NO_CXX11_TEMPLATE_ALIASES
#define QUARK_NO_CXX11_UNICODE_LITERALS
#define QUARK_NO_CXX11_VARIADIC_TEMPLATES
#define QUARK_NO_CXX11_VARIADIC_MACROS
#define QUARK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX

#define QUARK_NO_CXX11_HDR_UNORDERED_SET
#define QUARK_NO_CXX11_HDR_UNORDERED_MAP
#define QUARK_NO_CXX11_HDR_TYPEINDEX
#define QUARK_NO_CXX11_HDR_TYPE_TRAITS
#define QUARK_NO_CXX11_HDR_TUPLE
#define QUARK_NO_CXX11_HDR_THREAD
#define QUARK_NO_CXX11_HDR_SYSTEM_ERROR
#define QUARK_NO_CXX11_HDR_REGEX
#define QUARK_NO_CXX11_HDR_RATIO
#define QUARK_NO_CXX11_HDR_RANDOM
#define QUARK_NO_CXX11_HDR_MUTEX
#define QUARK_NO_CXX11_HDR_INITIALIZER_LIST
#define QUARK_NO_CXX11_HDR_FUTURE
#define QUARK_NO_CXX11_HDR_FORWARD_LIST
#define QUARK_NO_CXX11_HDR_CONDITION_VARIABLE
#define QUARK_NO_CXX11_HDR_CODECVT
#define QUARK_NO_CXX11_HDR_CHRONO
#define QUARK_NO_CXX11_HDR_ARRAY
#define QUARK_NO_CXX11_USER_DEFINED_LITERALS
#define QUARK_NO_CXX11_ALIGNAS
#define QUARK_NO_CXX11_TRAILING_RESULT_TYPES
#define QUARK_NO_CXX11_INLINE_NAMESPACES
#define QUARK_NO_CXX11_REF_QUALIFIERS
#define QUARK_NO_CXX11_FINAL

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
//
// version check:
// probably nothing to do here?

