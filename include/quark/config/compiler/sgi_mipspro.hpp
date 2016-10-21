//  (C) Copyright John Maddock 2001 - 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

//  SGI C++ compiler setup:

#define QUARK_COMPILER "SGI Irix compiler version " QUARK_STRINGIZE(_COMPILER_VERSION)

#include "quark/config/compiler/common_edg.hpp"

//
// Threading support:
// Turn this on unconditionally here, it will get turned off again later
// if no threading API is detected.
//
#define QUARK_HAS_THREADS
#define QUARK_NO_TWO_PHASE_NAME_LOOKUP

#undef QUARK_NO_SWPRINTF
#undef QUARK_DEDUCED_TYPENAME

//
// version check:
// probably nothing to do here?


