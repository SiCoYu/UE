#ifndef __MDebug_H
#define __MDebug_H

//#include <assert.h>
#include <cassert>

#ifdef _DEBUG
#  define MY_ASSERT assert;
#else
#  define MY_ASSERT assert
#endif

#endif