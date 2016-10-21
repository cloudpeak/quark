/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.quark.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/operations_lockfree.hpp
 *
 * This header defines lockfree atomic operations.
 */

#ifndef QUARK_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_
#define QUARK_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_

#include <quark/atomic/detail/config.hpp>
#include <quark/atomic/detail/platform.hpp>

#if !defined(QUARK_ATOMIC_EMULATED)
#include QUARK_ATOMIC_DETAIL_HEADER(quark/atomic/detail/ops_)
#else
#include <quark/atomic/detail/operations_fwd.hpp>
#endif

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // QUARK_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_
