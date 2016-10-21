/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.quark.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2012 - 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_msvc_arm.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef QUARK_ATOMIC_DETAIL_CAPS_MSVC_ARM_HPP_INCLUDED_
#define QUARK_ATOMIC_DETAIL_CAPS_MSVC_ARM_HPP_INCLUDED_

#include <quark/atomic/detail/config.hpp>

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

#define QUARK_ATOMIC_INT8_LOCK_FREE 2
#define QUARK_ATOMIC_INT16_LOCK_FREE 2
#define QUARK_ATOMIC_INT32_LOCK_FREE 2
#define QUARK_ATOMIC_INT64_LOCK_FREE 2
#define QUARK_ATOMIC_POINTER_LOCK_FREE 2

#define QUARK_ATOMIC_THREAD_FENCE 2
#define QUARK_ATOMIC_SIGNAL_FENCE 2

#endif // QUARK_ATOMIC_DETAIL_CAPS_MSVC_ARM_HPP_INCLUDED_
