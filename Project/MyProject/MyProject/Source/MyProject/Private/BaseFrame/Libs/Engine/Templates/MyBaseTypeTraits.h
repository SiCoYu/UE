// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	MyBaseTypeTraits.h: Unreal type traits definitions.
	Note: Boost does a much better job of limiting instantiations.
	We require VC8 so a lot of potential version checks are omitted.
=============================================================================*/

#pragma once

namespace MyNS
{
	template< class T >
	struct MyTRemoveConst
	{
		typedef T Type;
	};
	template< class T >
	struct MyTRemoveConst<const T>
	{
		typedef T Type;
	};
}