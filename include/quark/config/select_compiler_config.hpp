//  Boost compiler configuration selection header file

//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Martin Wille 2003.
//  (C) Copyright Guillaume Melquiond 2003.
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//   http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org/ for most recent version.

// locate which compiler we are using and define
// QUARK_COMPILER_CONFIG as needed: 

#if defined __CUDACC__
//  NVIDIA CUDA C++ compiler for GPU
#   include "quark/config/compiler/nvcc.hpp"

#endif

#if defined(__GCCXML__)
// GCC-XML emulates other compilers, it has to appear first here!
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/gcc_xml.hpp"

#elif defined(_CRAYC)
// EDG based Cray compiler:
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/cray.hpp"

#elif defined __COMO__
//  Comeau C++
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/comeau.hpp"

#elif defined(__PATHSCALE__) && (__PATHCC__ >= 4)
// PathScale EKOPath compiler (has to come before clang and gcc)
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/pathscale.hpp"

#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
//  Intel
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/intel.hpp"

#elif defined __clang__ && !defined(__CUDACC__) && !defined(__ibmxl__)
// when using clang and cuda at same time, you want to appear as gcc
//  Clang C++ emulates GCC, so it has to appear early.
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/clang.hpp"

#elif defined __DMC__
//  Digital Mars C++
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/digitalmars.hpp"

# elif defined(__GNUC__) && !defined(__ibmxl__)
//  GNU C++:
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/gcc.hpp"

#elif defined __KCC
//  Kai C++
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/kai.hpp"

#elif defined __sgi
//  SGI MIPSpro C++
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/sgi_mipspro.hpp"

#elif defined __DECCXX
//  Compaq Tru64 Unix cxx
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/compaq_cxx.hpp"

#elif defined __ghs
//  Greenhills C++
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/greenhills.hpp"

#elif defined __CODEGEARC__
//  CodeGear - must be checked for before Borland
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/codegear.hpp"

#elif defined __BORLANDC__
//  Borland
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/borland.hpp"

#elif defined  __MWERKS__
//  Metrowerks CodeWarrior
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/metrowerks.hpp"

#elif defined  __SUNPRO_CC
//  Sun Workshop Compiler C++
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/sunpro_cc.hpp"

#elif defined __HP_aCC
//  HP aCC
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/hp_acc.hpp"

#elif defined(__MRC__) || defined(__SC__)
//  MPW MrCpp or SCpp
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/mpw.hpp"

#elif defined(__ibmxl__)
// IBM XL C/C++ for Linux (Little Endian)
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/xlcpp.hpp"

#elif defined(__IBMCPP__)
//  IBM Visual Age or IBM XL C/C++ for Linux (Big Endian)
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/vacpp.hpp"

#elif defined(__PGI)
//  Portland Group Inc.
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/pgi.hpp"

#elif defined _MSC_VER
//  Microsoft Visual C++
//
//  Must remain the last #elif since some other vendors (Metrowerks, for
//  example) also #define _MSC_VER
#   define QUARK_COMPILER_CONFIG "quark/config/compiler/visualc.hpp"

#elif defined (QUARK_ASSERT_CONFIG)
// this must come last - generate an error if we don't
// recognise the compiler:
#  error "Unknown compiler - please configure (http://www.quark.org/libs/config/config.htm#configuring) and report the results to the main quark mailing list (http://www.quark.org/more/mailing_lists.htm#main)"

#endif

#if 0
//
// This section allows dependency scanners to find all the headers we *might* include:
//
#include "quark/config/compiler/gcc_xml.hpp"
#include "quark/config/compiler/cray.hpp"
#include "quark/config/compiler/comeau.hpp"
#include "quark/config/compiler/pathscale.hpp"
#include "quark/config/compiler/intel.hpp"
#include "quark/config/compiler/clang.hpp"
#include "quark/config/compiler/digitalmars.hpp"
#include "quark/config/compiler/gcc.hpp"
#include "quark/config/compiler/kai.hpp"
#include "quark/config/compiler/sgi_mipspro.hpp"
#include "quark/config/compiler/compaq_cxx.hpp"
#include "quark/config/compiler/greenhills.hpp"
#include "quark/config/compiler/codegear.hpp"
#include "quark/config/compiler/borland.hpp"
#include "quark/config/compiler/metrowerks.hpp"
#include "quark/config/compiler/sunpro_cc.hpp"
#include "quark/config/compiler/hp_acc.hpp"
#include "quark/config/compiler/mpw.hpp"
#include "quark/config/compiler/vacpp.hpp"
#include "quark/config/compiler/pgi.hpp"
#include "quark/config/compiler/visualc.hpp"

#endif

