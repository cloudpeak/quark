//  Boost compiler configuration selection header file

//  (C) Copyright John Maddock 2001 - 2002. 
//  (C) Copyright Jens Maurer 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

// locate which platform we are on and define QUARK_PLATFORM_CONFIG as needed.
// Note that we define the headers to include using "header_name" not
// <header_name> in order to prevent macro expansion within the header
// name (for example "linux" is a macro on linux systems).

#if (defined(linux) || defined(__linux) || defined(__linux__) || defined(__GNU__) || defined(__GLIBC__)) && !defined(_CRAYC)
// linux, also other platforms (Hurd etc) that use GLIBC, should these really have their own config headers though?
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/linux.hpp"

#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
// BSD:
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/bsd.hpp"

#elif defined(sun) || defined(__sun)
// solaris:
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/solaris.hpp"

#elif defined(__sgi)
// SGI Irix:
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/irix.hpp"

#elif defined(__hpux)
// hp unix:
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/hpux.hpp"

#elif defined(__CYGWIN__)
// cygwin is not win32:
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/cygwin.hpp"

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
// win32:
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/win32.hpp"

#elif defined(__HAIKU__)
// Haiku
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/haiku.hpp"

#elif defined(__BEOS__)
// BeOS
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/beos.hpp"

#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
// MacOS
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/macos.hpp"

#elif defined(__IBMCPP__) || defined(_AIX)
// IBM
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/aix.hpp"

#elif defined(__amigaos__)
// AmigaOS
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/amigaos.hpp"

#elif defined(__QNXNTO__)
// QNX:
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/qnxnto.hpp"

#elif defined(__VXWORKS__)
// vxWorks:
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/vxworks.hpp"

#elif defined(__SYMBIAN32__) 
// Symbian: 
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/symbian.hpp" 

#elif defined(_CRAYC)
// Cray:
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/cray.hpp" 

#elif defined(__VMS) 
// VMS:
#  define QUARK_PLATFORM_CONFIG "quark/config/platform/vms.hpp" 
#else

#  if defined(unix) \
      || defined(__unix) \
      || defined(_XOPEN_SOURCE) \
      || defined(_POSIX_SOURCE)

   // generic unix platform:

#  ifndef QUARK_HAS_UNISTD_H
#     define QUARK_HAS_UNISTD_H
#  endif

#  include <quark/config/posix_features.hpp>

#  endif

#  if defined (QUARK_ASSERT_CONFIG)
      // this must come last - generate an error if we don't
      // recognise the platform:
#     error "Unknown platform - please configure and report the results to quark.org"
#  endif

#endif

#if 0
//
// This section allows dependency scanners to find all the files we *might* include:
//
#  include "quark/config/platform/linux.hpp"
#  include "quark/config/platform/bsd.hpp"
#  include "quark/config/platform/solaris.hpp"
#  include "quark/config/platform/irix.hpp"
#  include "quark/config/platform/hpux.hpp"
#  include "quark/config/platform/cygwin.hpp"
#  include "quark/config/platform/win32.hpp"
#  include "quark/config/platform/beos.hpp"
#  include "quark/config/platform/macos.hpp"
#  include "quark/config/platform/aix.hpp"
#  include "quark/config/platform/amigaos.hpp"
#  include "quark/config/platform/qnxnto.hpp"
#  include "quark/config/platform/vxworks.hpp"
#  include "quark/config/platform/symbian.hpp" 
#  include "quark/config/platform/cray.hpp" 
#  include "quark/config/platform/vms.hpp" 
#  include <quark/config/posix_features.hpp>



#endif

