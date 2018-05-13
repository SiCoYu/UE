// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

namespace MyNS
{
	/**
	 * Defines a value metafunction of the given Value.
	 */
	template <typename T, T Val>
	struct TIntegralConstant
	{
		static const T Value = Val;
	};
}