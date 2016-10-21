//  quark/config/user.hpp  ---------------------------------------------------//

//  (C) Copyright John Maddock 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  Do not check in modified versions of this file,
//  This file may be customized by the end user, but not by quark.

//
//  Use this file to define a site and compiler specific
//  configuration policy:
//

// define this to locate a compiler config file:
// #define QUARK_COMPILER_CONFIG <myheader>

// define this to locate a stdlib config file:
// #define QUARK_STDLIB_CONFIG   <myheader>

// define this to locate a platform config file:
// #define QUARK_PLATFORM_CONFIG <myheader>

// define this to disable compiler config,
// use if your compiler config has nothing to set:
// #define QUARK_NO_COMPILER_CONFIG

// define this to disable stdlib config,
// use if your stdlib config has nothing to set:
// #define QUARK_NO_STDLIB_CONFIG

// define this to disable platform config,
// use if your platform config has nothing to set:
// #define QUARK_NO_PLATFORM_CONFIG

// define this to disable all config options,
// excluding the user config.  Use if your
// setup is fully ISO compliant, and has no
// useful extensions, or for autoconf generated
// setups:
// #define QUARK_NO_CONFIG

// define this to make the config "optimistic"
// about unknown compiler versions.  Normally
// unknown compiler versions are assumed to have
// all the defects of the last known version, however
// setting this flag, causes the config to assume
// that unknown compiler versions are fully conformant
// with the standard:
// #define QUARK_STRICT_CONFIG

// define this to cause the config to halt compilation
// with an #error if it encounters anything unknown --
// either an unknown compiler version or an unknown
// compiler/platform/library:
// #define QUARK_ASSERT_CONFIG


// define if you want to disable threading support, even
// when available:
// #define QUARK_DISABLE_THREADS

// define when you want to disable Win32 specific features
// even when available:
// #define QUARK_DISABLE_WIN32

// QUARK_DISABLE_ABI_HEADERS: Stops quark headers from including any 
// prefix/suffix headers that normally control things like struct 
// packing and alignment. 
// #define QUARK_DISABLE_ABI_HEADERS

// QUARK_ABI_PREFIX: A prefix header to include in place of whatever
// quark.config would normally select, any replacement should set up 
// struct packing and alignment options as required. 
// #define QUARK_ABI_PREFIX my-header-name

// QUARK_ABI_SUFFIX: A suffix header to include in place of whatever 
// quark.config would normally select, any replacement should undo 
// the effects of the prefix header. 
// #define QUARK_ABI_SUFFIX my-header-name

// QUARK_ALL_DYN_LINK: Forces all libraries that have separate source, 
// to be linked as dll's rather than static libraries on Microsoft Windows 
// (this macro is used to turn on __declspec(dllimport) modifiers, so that 
// the compiler knows which symbols to look for in a dll rather than in a 
// static library).  Note that there may be some libraries that can only 
// be linked in one way (statically or dynamically), in these cases this 
// macro has no effect.
// #define QUARK_ALL_DYN_LINK
 
// QUARK_WHATEVER_DYN_LINK: Forces library "whatever" to be linked as a dll 
// rather than a static library on Microsoft Windows: replace the WHATEVER 
// part of the macro name with the name of the library that you want to 
// dynamically link to, for example use QUARK_DATE_TIME_DYN_LINK or 
// QUARK_REGEX_DYN_LINK etc (this macro is used to turn on __declspec(dllimport) 
// modifiers, so that the compiler knows which symbols to look for in a dll 
// rather than in a static library).  
// Note that there may be some libraries that can only 
// be linked in one way (statically or dynamically), 
// in these cases this macro is unsupported.
// #define QUARK_WHATEVER_DYN_LINK
 
// QUARK_ALL_NO_LIB: Tells the config system not to automatically select 
// which libraries to link against.  
// Normally if a compiler supports #pragma lib, then the correct library 
// build variant will be automatically selected and linked against, 
// simply by the act of including one of that library's headers.  
// This macro turns that feature off.
// #define QUARK_ALL_NO_LIB
 
// QUARK_WHATEVER_NO_LIB: Tells the config system not to automatically 
// select which library to link against for library "whatever", 
// replace WHATEVER in the macro name with the name of the library; 
// for example QUARK_DATE_TIME_NO_LIB or QUARK_REGEX_NO_LIB.  
// Normally if a compiler supports #pragma lib, then the correct library 
// build variant will be automatically selected and linked against, simply 
// by the act of including one of that library's headers.  This macro turns 
// that feature off.
// #define QUARK_WHATEVER_NO_LIB
 
// QUARK_LIB_BUILDID: Set to the same value as the value passed to Boost.Build's
// --buildid command line option.  For example if you built using:
//
// bjam address-model=64 --buildid=amd64
//
// then compile your code with:
//
// -DQUARK_LIB_BUILDID = amd64
//
// to ensure the correct libraries are selected at link time.
// #define QUARK_LIB_BUILDID amd64

