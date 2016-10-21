//  Boost config.hpp configuration header file  ------------------------------//

//  (C) Copyright John Maddock 2002.
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org/libs/config for most recent version.

//  Boost config.hpp policy and rationale documentation has been moved to
//  http://www.quark.org/libs/config
//
//  CAUTION: This file is intended to be completely stable -
//           DO NOT MODIFY THIS FILE!
//

#ifndef QUARK_CONFIG_HPP
#define QUARK_CONFIG_HPP

// if we don't have a user config, then use the default location:
#if !defined(QUARK_USER_CONFIG) && !defined(QUARK_NO_USER_CONFIG)
#  define QUARK_USER_CONFIG <quark/config/user.hpp>
#if 0
// For dependency trackers:
#  include <quark/config/user.hpp>
#endif
#endif
// include it first:
#ifdef QUARK_USER_CONFIG
#  include QUARK_USER_CONFIG
#endif

// if we don't have a compiler config set, try and find one:
#if !defined(QUARK_COMPILER_CONFIG) && !defined(QUARK_NO_COMPILER_CONFIG) && !defined(QUARK_NO_CONFIG)
#  include <quark/config/select_compiler_config.hpp>
#endif
// if we have a compiler config, include it now:
#ifdef QUARK_COMPILER_CONFIG
#  include QUARK_COMPILER_CONFIG
#endif

// if we don't have a std library config set, try and find one:
#if !defined(QUARK_STDLIB_CONFIG) && !defined(QUARK_NO_STDLIB_CONFIG) && !defined(QUARK_NO_CONFIG) && defined(__cplusplus)
#  include <quark/config/select_stdlib_config.hpp>
#endif
// if we have a std library config, include it now:
#ifdef QUARK_STDLIB_CONFIG
#  include QUARK_STDLIB_CONFIG
#endif

// if we don't have a platform config set, try and find one:
#if !defined(QUARK_PLATFORM_CONFIG) && !defined(QUARK_NO_PLATFORM_CONFIG) && !defined(QUARK_NO_CONFIG)
#  include <quark/config/select_platform_config.hpp>
#endif
// if we have a platform config, include it now:
#ifdef QUARK_PLATFORM_CONFIG
#  include QUARK_PLATFORM_CONFIG
#endif

// get config suffix code:
#include <quark/config/suffix.hpp>

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif  // QUARK_CONFIG_HPP
