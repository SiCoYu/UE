#ifndef __MDebug_H
#define __MDebug_H

#include <assert.h>

#ifdef _DEBUG
#  define TOOL_ASSERT assert;
#else
#  define TOOL_ASSERT assert
#endif

#endif