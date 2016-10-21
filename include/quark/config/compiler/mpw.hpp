//  (C) Copyright John Maddock 2001 - 2002.
//  (C) Copyright Aleksey Gurtovoy 2002.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

//  MPW C++ compilers setup:

#   if    defined(__SC__)
#     define QUARK_COMPILER "MPW SCpp version " QUARK_STRINGIZE(__SC__)
#   elif defined(__MRC__)
#     define QUARK_COMPILER "MPW MrCpp version " QUARK_STRINGIZE(__MRC__)
#   else
#     error "Using MPW compiler configuration by mistake.  Please update."
#   endif

//
// MPW 8.90:
//
#if (MPW_CPLUS <= 0x890) || !defined(QUARK_STRICT_CONFIG)
#  define QUARK_NO_CV_SPECIALIZATIONS
#  define QUARK_NO_DEPENDENT_NESTED_DERIVATIONS
#  define QUARK_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
#  define QUARK_NO_INCLASS_MEMBER_INITIALIZATION
#  define QUARK_NO_INTRINSIC_WCHAR_T
#  define QUARK_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#  define QUARK_NO_USING_TEMPLATE

#  define QUARK_NO_CWCHAR
#  define QUARK_NO_LIMITS_COMPILE_TIME_CONSTANTS

#  define QUARK_NO_STD_ALLOCATOR /* actually a bug with const reference overloading */

#endif

//
// C++0x features
//
//   See quark\config\suffix.hpp for QUARK_NO_LONG_LONG
//
#define QUARK_NO_CXX11_AUTO_DECLARATIONS
#define QUARK_NO_CXX11_AUTO_MULTIDECLARATIONS
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
#define QUARK_NO_CXX11_HDR_INITIALIZER_LIST
#define QUARK_NO_CXX11_LAMBDAS
#define QUARK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define QUARK_NO_CXX11_NOEXCEPT
#define QUARK_NO_CXX11_NULLPTR
#define QUARK_NO_CXX11_RANGE_BASED_FOR
#define QUARK_NO_CXX11_RAW_LITERALS
#define QUARK_NO_CXX11_RVALUE_REFERENCES
#define QUARK_NO_CXX11_SCOPED_ENUMS
#define QUARK_NO_SFINAE_EXPR
#define QUARK_NO_CXX11_STATIC_ASSERT
#define QUARK_NO_CXX11_TEMPLATE_ALIASES
#define QUARK_NO_CXX11_UNICODE_LITERALS
#define QUARK_NO_CXX11_VARIADIC_TEMPLATES
#define QUARK_NO_CXX11_VARIADIC_MACROS
#define QUARK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
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
// versions check:
// we don't support MPW prior to version 8.9:
#if MPW_CPLUS < 0x890
#  error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version is 0x890:
#if (MPW_CPLUS > 0x890)
#  if defined(QUARK_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif


