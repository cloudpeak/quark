//  (C) Copyright Artyom Beilis 2010.  
//  Use, modification and distribution are subject to the  
//  Boost Software License, Version 1.0. (See accompanying file  
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt) 

#ifndef QUARK_CONFIG_PLATFORM_VMS_HPP 
#define QUARK_CONFIG_PLATFORM_VMS_HPP 

#define QUARK_PLATFORM "OpenVMS" 

#undef  QUARK_HAS_STDINT_H 
#define QUARK_HAS_UNISTD_H 
#define QUARK_HAS_NL_TYPES_H 
#define QUARK_HAS_GETTIMEOFDAY 
#define QUARK_HAS_DIRENT_H 
#define QUARK_HAS_PTHREADS 
#define QUARK_HAS_NANOSLEEP 
#define QUARK_HAS_CLOCK_GETTIME 
#define QUARK_HAS_PTHREAD_MUTEXATTR_SETTYPE 
#define QUARK_HAS_LOG1P 
#define QUARK_HAS_EXPM1 
#define QUARK_HAS_THREADS 
#undef  QUARK_HAS_SCHED_YIELD 

#endif 
