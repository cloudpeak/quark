/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.quark.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/atomic_flag.hpp
 *
 * This header contains definition of \c atomic_flag.
 */

#ifndef QUARK_ATOMIC_ATOMIC_FLAG_HPP_INCLUDED_
#define QUARK_ATOMIC_ATOMIC_FLAG_HPP_INCLUDED_

#include <quark/atomic/capabilities.hpp>
#include <quark/atomic/detail/operations.hpp>
#include <quark/atomic/detail/atomic_flag.hpp>

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace quark {

using atomics::atomic_flag;

} // namespace quark

#endif // QUARK_ATOMIC_ATOMIC_FLAG_HPP_INCLUDED_
