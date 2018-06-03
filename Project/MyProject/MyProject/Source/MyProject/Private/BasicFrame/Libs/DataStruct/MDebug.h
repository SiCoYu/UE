#ifndef __Error_H
#define __Error_H

#include <assert.h>

#ifdef _DEBUG
#  define TOOL_ASSERT assert;
#else
#  define TOOL_ASSERT assert
#endif

#endif