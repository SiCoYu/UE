// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#define USING_UE4_API 0

#if USING_UE4_API
#include "HAL/Platform.h"
#else
// Backwater of the spec. All compilers support this except microsoft, and they will soon
#ifndef TYPENAME_OUTSIDE_TEMPLATE
#define TYPENAME_OUTSIDE_TEMPLATE	typename
#endif

// Method modifiers
#ifndef ABSTRACT
#define ABSTRACT
#endif
#ifndef CONSTEXPR
#define CONSTEXPR constexpr
#endif

// String constants
#ifndef LINE_TERMINATOR
#define LINE_TERMINATOR TEXT("\n")
#endif
#ifndef LINE_TERMINATOR_ANSI
#define LINE_TERMINATOR_ANSI "\n"
#endif

template<typename T32BITS, typename T64BITS, int PointerSize>
struct SelectIntPointerType
{
	// nothing here are is it an error if the partial specializations fail
};

template<typename T32BITS, typename T64BITS>
struct SelectIntPointerType<T32BITS, T64BITS, 8>
{
	typedef T64BITS TIntPointer; // select the 64 bit type
};

template<typename T32BITS, typename T64BITS>
struct SelectIntPointerType<T32BITS, T64BITS, 4>
{
	typedef T32BITS TIntPointer; // select the 32 bit type
};

//~ Unsigned base types.
/// An 8-bit unsigned integer.
typedef unsigned char		uint8;
/// A 16-bit unsigned integer.
typedef unsigned short		uint16;
/// A 32-bit unsigned integer.
typedef unsigned int		uint32;
/// A 64-bit unsigned integer.
typedef unsigned long long		uint64;

//~ Signed base types.
/// An 8-bit signed integer.
typedef	signed char		int8;
/// A 16-bit signed integer.
typedef signed short		int16;
/// A 32-bit signed integer.
typedef signed int		int32;
/// A 64-bit signed integer.
typedef signed long long		int64;

typedef char	ANSICHAR;
typedef wchar_t	WIDECHAR;
typedef wchar_t TCHAR;

typedef int32					TYPE_OF_NULL;
typedef decltype(nullptr)		TYPE_OF_NULLPTR;

typedef SelectIntPointerType<uint32, uint64, sizeof(void*)>::TIntPointer UPTRINT;	// unsigned int the same size as a pointer
typedef SelectIntPointerType<int32, int64, sizeof(void*)>::TIntPointer PTRINT;		// signed int the same size as a pointer

#define FORCEINLINE __forceinline

//------------------------------------------------------------------
// Test the global types
//------------------------------------------------------------------
namespace TypeTests
{
	template <typename A, typename B>
	struct TAreTypesEqual
	{
		enum { Value = false };
	};

	template <typename T>
	struct TAreTypesEqual<T, T>
	{
		enum { Value = true };
	};

	static_assert(sizeof(uint8) == 1, "BYTE type size test failed.");
	static_assert(int32(uint8(-1)) == 0xFF, "BYTE type sign test failed.");

	static_assert(sizeof(uint16) == 2, "WORD type size test failed.");
	static_assert(int32(uint16(-1)) == 0xFFFF, "WORD type sign test failed.");

	static_assert(sizeof(uint32) == 4, "DWORD type size test failed.");
	static_assert(int64(uint32(-1)) == int64(0xFFFFFFFF), "DWORD type sign test failed.");

	static_assert(sizeof(uint64) == 8, "QWORD type size test failed.");
	static_assert(uint64(-1) > uint64(0), "QWORD type sign test failed.");


	static_assert(sizeof(int8) == 1, "SBYTE type size test failed.");
	static_assert(int32(int8(-1)) == -1, "SBYTE type sign test failed.");

	static_assert(sizeof(int16) == 2, "SWORD type size test failed.");
	static_assert(int32(int16(-1)) == -1, "SWORD type sign test failed.");

	static_assert(sizeof(int32) == 4, "INT type size test failed.");
	static_assert(int64(int32(-1)) == int64(-1), "INT type sign test failed.");

	static_assert(sizeof(int64) == 8, "SQWORD type size test failed.");
	static_assert(int64(-1) < int64(0), "SQWORD type sign test failed.");
}

#if !defined(TEXT)
#define TEXT_PASTE(x) L ## x
#define TEXT(x) TEXT_PASTE(x)
#endif
#endif