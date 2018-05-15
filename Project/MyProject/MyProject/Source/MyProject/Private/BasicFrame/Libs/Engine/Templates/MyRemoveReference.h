// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

namespace MyNS
{
	/**
	 * MyTRemoveReference<type> will remove any references from a type.
	 */
	template <typename T> struct MyTRemoveReference { typedef T Type; };
	template <typename T> struct MyTRemoveReference<T& > { typedef T Type; };
	template <typename T> struct MyTRemoveReference<T&&> { typedef T Type; };
}