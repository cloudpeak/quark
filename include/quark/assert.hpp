//
//  quark/assert.hpp - QUARK_ASSERT(expr)
//                     QUARK_ASSERT_MSG(expr, msg)
//                     QUARK_VERIFY(expr)
//                     QUARK_VERIFY_MSG(expr, msg)
//
//  Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2007, 2014 Peter Dimov
//  Copyright (c) Beman Dawes 2011
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.quark.org/LICENSE_1_0.txt
//
//  Note: There are no include guards. This is intentional.
//
//  See http://www.quark.org/libs/assert/assert.html for documentation.
//

//
// Stop inspect complaining about use of 'assert':
//
// quarkinspect:naassert_macro
//

//
// QUARK_ASSERT, QUARK_ASSERT_MSG
//

#undef QUARK_ASSERT
#undef QUARK_ASSERT_MSG

#if defined(QUARK_DISABLE_ASSERTS) || ( defined(QUARK_ENABLE_ASSERT_DEBUG_HANDLER) && defined(NDEBUG) )

# define QUARK_ASSERT(expr) ((void)0)
# define QUARK_ASSERT_MSG(expr, msg) ((void)0)

#elif defined(QUARK_ENABLE_ASSERT_HANDLER) || ( defined(QUARK_ENABLE_ASSERT_DEBUG_HANDLER) && !defined(NDEBUG) )

#include <quark/config.hpp> // for QUARK_LIKELY
#include <quark/current_function.hpp>

namespace quark
{
    void assertion_failed(char const * expr, char const * function, char const * file, long line); // user defined
    void assertion_failed_msg(char const * expr, char const * msg, char const * function, char const * file, long line); // user defined
} // namespace quark

#define QUARK_ASSERT(expr) (QUARK_LIKELY(!!(expr))? ((void)0): ::quark::assertion_failed(#expr, QUARK_CURRENT_FUNCTION, __FILE__, __LINE__))
#define QUARK_ASSERT_MSG(expr, msg) (QUARK_LIKELY(!!(expr))? ((void)0): ::quark::assertion_failed_msg(#expr, msg, QUARK_CURRENT_FUNCTION, __FILE__, __LINE__))

#else

# include <assert.h> // .h to support old libraries w/o <cassert> - effect is the same

# define QUARK_ASSERT(expr) assert(expr)
# define QUARK_ASSERT_MSG(expr, msg) assert((expr)&&(msg))

#endif

//
// QUARK_VERIFY, QUARK_VERIFY_MSG
//

#undef QUARK_VERIFY
#undef QUARK_VERIFY_MSG

#if defined(QUARK_DISABLE_ASSERTS) || ( !defined(QUARK_ENABLE_ASSERT_HANDLER) && defined(NDEBUG) )

# define QUARK_VERIFY(expr) ((void)(expr))
# define QUARK_VERIFY_MSG(expr, msg) ((void)(expr))

#else

# define QUARK_VERIFY(expr) QUARK_ASSERT(expr)
# define QUARK_VERIFY_MSG(expr, msg) QUARK_ASSERT_MSG(expr,msg)

#endif
