// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "Templates/MyAlignOf.h"

namespace MyNS
{
	/**
	 * Used to declare an untyped array of data with compile-time alignment.
	 * It needs to use template specialization as the MS_ALIGN and GCC_ALIGN macros require literal parameters.
	 */
	template<int32 Size, uint32 Alignment>
	struct TAlignedBytes; // this intentionally won't compile, we don't support the requested alignment

	/** Unaligned storage. */
	template<int32 Size>
	struct TAlignedBytes<Size, 1>
	{
		uint8 Pad[Size];
	};

	/** An untyped array of data with compile-time alignment and size derived from another type. */
	template<typename ElementType>
	struct TTypeCompatibleBytes :
		public TAlignedBytes<
		sizeof(ElementType),
		ALIGNOF(ElementType)
		>
	{};
}