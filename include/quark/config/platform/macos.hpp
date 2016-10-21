//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Darin Adler 2001 - 2002. 
//  (C) Copyright Bill Kempf 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

//  Mac OS specific config options:

#define QUARK_PLATFORM "Mac OS"

#if __MACH__ && !defined(_MSL_USING_MSL_C)

// Using the Mac OS X system BSD-style C library.

#  ifndef QUARK_HAS_UNISTD_H
#    define QUARK_HAS_UNISTD_H
#  endif
//
// Begin by including our boilerplate code for POSIX
// feature detection, this is safe even when using
// the MSL as Metrowerks supply their own <unistd.h>
// to replace the platform-native BSD one. G++ users
// should also always be able to do this on MaxOS X.
//
#  include <quark/config/posix_features.hpp>
#  ifndef QUARK_HAS_STDINT_H
#     define QUARK_HAS_STDINT_H
#  endif

//
// BSD runtime has pthreads, sigaction, sched_yield and gettimeofday,
// of these only pthreads are advertised in <unistd.h>, so set the 
// other options explicitly:
//
#  define QUARK_HAS_SCHED_YIELD
#  define QUARK_HAS_GETTIMEOFDAY
#  define QUARK_HAS_SIGACTION

#  if (__GNUC__ < 3) && !defined( __APPLE_CC__)

// GCC strange "ignore std" mode works better if you pretend everything
// is in the std namespace, for the most part.

#    define QUARK_NO_STDC_NAMESPACE
#  endif

#  if (__GNUC__ == 4)

// Both gcc and intel require these.  
#    define QUARK_HAS_PTHREAD_MUTEXATTR_SETTYPE
#    define QUARK_HAS_NANOSLEEP

#  endif

#else

// Using the MSL C library.

// We will eventually support threads in non-Carbon builds, but we do
// not support this yet.
#  if ( defined(TARGET_API_MAC_CARBON) && TARGET_API_MAC_CARBON ) || ( defined(TARGET_CARBON) && TARGET_CARBON )

#  if !defined(QUARK_HAS_PTHREADS)
// MPTasks support is deprecated/removed from Boost:
//#    define QUARK_HAS_MPTASKS
#  elif ( __dest_os == __mac_os_x )
// We are doing a Carbon/Mach-O/MSL build which has pthreads, but only the
// gettimeofday and no posix.
#  define QUARK_HAS_GETTIMEOFDAY
#  endif

#ifdef QUARK_HAS_PTHREADS
#  define QUARK_HAS_THREADS
#endif

// The remote call manager depends on this.
#    define QUARK_BIND_ENABLE_PASCAL

#  endif

#endif



