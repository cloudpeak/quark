//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <functional> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if quark/tr1/tr1/functional is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef QUARK_CONFIG_FUNCTIONAL
#  define QUARK_CONFIG_FUNCTIONAL

#  ifndef QUARK_TR1_NO_RECURSION
#     define QUARK_TR1_NO_RECURSION
#     define QUARK_CONFIG_NO_FUNCTIONAL_RECURSION
#  endif

#  include <functional>

#  ifdef QUARK_CONFIG_NO_FUNCTIONAL_RECURSION
#     undef QUARK_TR1_NO_RECURSION
#     undef QUARK_CONFIG_NO_FUNCTIONAL_RECURSION
#  endif

#endif
