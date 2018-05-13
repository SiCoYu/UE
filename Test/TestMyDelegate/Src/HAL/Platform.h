// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

//~ Unsigned base types.
/// An 8-bit unsigned integer.
typedef unsigned char		uint8;
/// A 16-bit unsigned integer.
typedef unsigned short		uint16;
/// A 32-bit unsigned integer.
typedef unsigned int		uint32;
/// A 64-bit unsigned integer.
typedef unsigned __int64		uint64;

//~ Signed base types.
/// An 8-bit signed integer.
typedef	char		int8;
/// A 16-bit signed integer.
typedef short		int16;
/// A 32-bit signed integer.
typedef int		int32;
/// A 64-bit signed integer.
typedef __int64		int64;

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