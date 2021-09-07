#ifndef _ASSERT_H
#define _ASSERT_H

#include <kernel/panic.h>

#define ASSERT(a) ((a) ? (void)0 : panic_assert(__FILE__, __LINE__, #a))

#endif //_ASSERT_H
