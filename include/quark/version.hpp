//  Boost version.hpp configuration header file  ------------------------------//

//  (C) Copyright John maddock 1999. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org/libs/config for documentation

#ifndef QUARK_VERSION_HPP
#define QUARK_VERSION_HPP

//
//  Caution: this is the only Boost header that is guaranteed
//  to change with every Boost release. Including this header
//  will cause a recompile every time a new Boost version is
//  used.
//
//  QUARK_VERSION % 100 is the patch level
//  QUARK_VERSION / 100 % 1000 is the minor version
//  QUARK_VERSION / 100000 is the major version

#define QUARK_VERSION 105900

//
//  QUARK_LIB_VERSION must be defined to be the same as QUARK_VERSION
//  but as a *string* in the form "x_y[_z]" where x is the major version
//  number, y is the minor version number, and z is the patch level if not 0.
//  This is used by <config/auto_link.hpp> to select which library version to link to.

#define QUARK_LIB_VERSION "1_59"

#endif
