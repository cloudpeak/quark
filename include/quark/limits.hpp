
//  (C) Copyright John maddock 1999. 
//  (C) David Abrahams 2002.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)
//
// use this header as a workaround for missing <limits>

//  See http://www.quark.org/libs/compatibility/index.html for documentation.

#ifndef QUARK_LIMITS
#define QUARK_LIMITS

#include <quark/config.hpp>

#ifdef QUARK_NO_LIMITS
#  error "There is no std::numeric_limits suppport available."
#else
# include <limits>
#endif

#if (defined(QUARK_HAS_LONG_LONG) && defined(QUARK_NO_LONG_LONG_NUMERIC_LIMITS)) \
      || (defined(QUARK_HAS_MS_INT64) && defined(QUARK_NO_MS_INT64_NUMERIC_LIMITS))
// Add missing specializations for numeric_limits:
#ifdef QUARK_HAS_MS_INT64
#  define QUARK_LLT __int64
#  define QUARK_ULLT unsigned __int64
#else
#  define QUARK_LLT  ::quark::long_long_type
#  define QUARK_ULLT  ::quark::ulong_long_type
#endif

#include <climits>  // for CHAR_BIT

namespace std
{
  template<>
  class numeric_limits<QUARK_LLT> 
  {
   public:

      QUARK_STATIC_CONSTANT(bool, is_specialized = true);
#ifdef QUARK_HAS_MS_INT64
      static QUARK_LLT min QUARK_PREVENT_MACRO_SUBSTITUTION (){ return 0x8000000000000000i64; }
      static QUARK_LLT max QUARK_PREVENT_MACRO_SUBSTITUTION (){ return 0x7FFFFFFFFFFFFFFFi64; }
#elif defined(LLONG_MAX)
      static QUARK_LLT min QUARK_PREVENT_MACRO_SUBSTITUTION (){ return LLONG_MIN; }
      static QUARK_LLT max QUARK_PREVENT_MACRO_SUBSTITUTION (){ return LLONG_MAX; }
#elif defined(LONGLONG_MAX)
      static QUARK_LLT min QUARK_PREVENT_MACRO_SUBSTITUTION (){ return LONGLONG_MIN; }
      static QUARK_LLT max QUARK_PREVENT_MACRO_SUBSTITUTION (){ return LONGLONG_MAX; }
#else
      static QUARK_LLT min QUARK_PREVENT_MACRO_SUBSTITUTION (){ return 1LL << (sizeof(QUARK_LLT) * CHAR_BIT - 1); }
      static QUARK_LLT max QUARK_PREVENT_MACRO_SUBSTITUTION (){ return ~(min)(); }
#endif
      QUARK_STATIC_CONSTANT(int, digits = sizeof(QUARK_LLT) * CHAR_BIT -1);
      QUARK_STATIC_CONSTANT(int, digits10 = (CHAR_BIT * sizeof (QUARK_LLT) - 1) * 301L / 1000);
      QUARK_STATIC_CONSTANT(bool, is_signed = true);
      QUARK_STATIC_CONSTANT(bool, is_integer = true);
      QUARK_STATIC_CONSTANT(bool, is_exact = true);
      QUARK_STATIC_CONSTANT(int, radix = 2);
      static QUARK_LLT epsilon() throw() { return 0; };
      static QUARK_LLT round_error() throw() { return 0; };

      QUARK_STATIC_CONSTANT(int, min_exponent = 0);
      QUARK_STATIC_CONSTANT(int, min_exponent10 = 0);
      QUARK_STATIC_CONSTANT(int, max_exponent = 0);
      QUARK_STATIC_CONSTANT(int, max_exponent10 = 0);

      QUARK_STATIC_CONSTANT(bool, has_infinity = false);
      QUARK_STATIC_CONSTANT(bool, has_quiet_NaN = false);
      QUARK_STATIC_CONSTANT(bool, has_signaling_NaN = false);
      QUARK_STATIC_CONSTANT(bool, has_denorm = false);
      QUARK_STATIC_CONSTANT(bool, has_denorm_loss = false);
      static QUARK_LLT infinity() throw() { return 0; };
      static QUARK_LLT quiet_NaN() throw() { return 0; };
      static QUARK_LLT signaling_NaN() throw() { return 0; };
      static QUARK_LLT denorm_min() throw() { return 0; };

      QUARK_STATIC_CONSTANT(bool, is_iec559 = false);
      QUARK_STATIC_CONSTANT(bool, is_bounded = true);
      QUARK_STATIC_CONSTANT(bool, is_modulo = true);

      QUARK_STATIC_CONSTANT(bool, traps = false);
      QUARK_STATIC_CONSTANT(bool, tinyness_before = false);
      QUARK_STATIC_CONSTANT(float_round_style, round_style = round_toward_zero);
      
  };

  template<>
  class numeric_limits<QUARK_ULLT> 
  {
   public:

      QUARK_STATIC_CONSTANT(bool, is_specialized = true);
#ifdef QUARK_HAS_MS_INT64
      static QUARK_ULLT min QUARK_PREVENT_MACRO_SUBSTITUTION (){ return 0ui64; }
      static QUARK_ULLT max QUARK_PREVENT_MACRO_SUBSTITUTION (){ return 0xFFFFFFFFFFFFFFFFui64; }
#elif defined(ULLONG_MAX) && defined(ULLONG_MIN)
      static QUARK_ULLT min QUARK_PREVENT_MACRO_SUBSTITUTION (){ return ULLONG_MIN; }
      static QUARK_ULLT max QUARK_PREVENT_MACRO_SUBSTITUTION (){ return ULLONG_MAX; }
#elif defined(ULONGLONG_MAX) && defined(ULONGLONG_MIN)
      static QUARK_ULLT min QUARK_PREVENT_MACRO_SUBSTITUTION (){ return ULONGLONG_MIN; }
      static QUARK_ULLT max QUARK_PREVENT_MACRO_SUBSTITUTION (){ return ULONGLONG_MAX; }
#else
      static QUARK_ULLT min QUARK_PREVENT_MACRO_SUBSTITUTION (){ return 0uLL; }
      static QUARK_ULLT max QUARK_PREVENT_MACRO_SUBSTITUTION (){ return ~0uLL; }
#endif
      QUARK_STATIC_CONSTANT(int, digits = sizeof(QUARK_LLT) * CHAR_BIT);
      QUARK_STATIC_CONSTANT(int, digits10 = (CHAR_BIT * sizeof (QUARK_LLT)) * 301L / 1000);
      QUARK_STATIC_CONSTANT(bool, is_signed = false);
      QUARK_STATIC_CONSTANT(bool, is_integer = true);
      QUARK_STATIC_CONSTANT(bool, is_exact = true);
      QUARK_STATIC_CONSTANT(int, radix = 2);
      static QUARK_ULLT epsilon() throw() { return 0; };
      static QUARK_ULLT round_error() throw() { return 0; };

      QUARK_STATIC_CONSTANT(int, min_exponent = 0);
      QUARK_STATIC_CONSTANT(int, min_exponent10 = 0);
      QUARK_STATIC_CONSTANT(int, max_exponent = 0);
      QUARK_STATIC_CONSTANT(int, max_exponent10 = 0);

      QUARK_STATIC_CONSTANT(bool, has_infinity = false);
      QUARK_STATIC_CONSTANT(bool, has_quiet_NaN = false);
      QUARK_STATIC_CONSTANT(bool, has_signaling_NaN = false);
      QUARK_STATIC_CONSTANT(bool, has_denorm = false);
      QUARK_STATIC_CONSTANT(bool, has_denorm_loss = false);
      static QUARK_ULLT infinity() throw() { return 0; };
      static QUARK_ULLT quiet_NaN() throw() { return 0; };
      static QUARK_ULLT signaling_NaN() throw() { return 0; };
      static QUARK_ULLT denorm_min() throw() { return 0; };

      QUARK_STATIC_CONSTANT(bool, is_iec559 = false);
      QUARK_STATIC_CONSTANT(bool, is_bounded = true);
      QUARK_STATIC_CONSTANT(bool, is_modulo = true);

      QUARK_STATIC_CONSTANT(bool, traps = false);
      QUARK_STATIC_CONSTANT(bool, tinyness_before = false);
      QUARK_STATIC_CONSTANT(float_round_style, round_style = round_toward_zero);
      
  };
}
#endif 

#endif

