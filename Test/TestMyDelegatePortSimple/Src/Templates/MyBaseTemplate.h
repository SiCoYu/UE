// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MPlatform.h"
#include "Templates/MyRemoveReference.h"

namespace MyNS
{
	/**
	 * Returns the same type passed to it.  This is useful in a few cases, but mainly for inhibiting template argument deduction in function arguments, e.g.:
	 *
	 * template <typename T>
	 * void Func1(T Val); // Can be called like Func(123) or Func<int>(123);
	 *
	 * template <typename T>
	 * void Func2(typename MyTIdentity<T>::Type Val); // Must be called like Func<int>(123)
	 */
	template <typename T>
	struct MyTIdentity
	{
		typedef T Type;
	};

	/**
	 * Metafunction which returns the specified boolean value.
	 */
	template <bool bValue>
	struct MyTBoolConstant
	{
		enum { Value = bValue };
	};

	/**
	 * Equivalent to std::declval.
	 *
	 * Note that this function is unimplemented, and is only intended to be used in unevaluated contexts, like sizeof and trait expressions.
	 */
	template <typename T>
	T&& DeclVal();
}