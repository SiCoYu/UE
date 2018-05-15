// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MPlatform.h"
#include "Templates/MyRemoveReference.h"

namespace MyNS
{
	/**
	 * utility template for a class that should not be copyable.
	 * Derive from this class to make your class non-copyable
	 */
	class FNoncopyable
	{
	protected:
		// ensure the class cannot be constructed directly
		FNoncopyable() {}
		// the class should not be used polymorphically
		~FNoncopyable() {}
	private:
		FNoncopyable(const FNoncopyable&);
		FNoncopyable& operator=(const FNoncopyable&);
	};


	/**
	 * exception-safe guard around saving/restoring a value.
	 * Commonly used to make sure a value is restored
	 * even if the code early outs in the future.
	 * Usage:
	 *  	TGuardValue<bool> GuardSomeBool(bSomeBool, false); // Sets bSomeBool to false, and restores it in dtor.
	 */
	template <typename Type>
	struct TGuardValue : private FNoncopyable
	{
		TGuardValue(Type& ReferenceValue, const Type& NewValue)
			: RefValue(ReferenceValue), OldValue(ReferenceValue)
		{
			RefValue = NewValue;
		}
		~TGuardValue()
		{
			RefValue = OldValue;
		}

		/**
		 * Overloaded dereference operator.
		 * Provides read-only access to the original value of the data being tracked by this struct
		 *
		 * @return	a const reference to the original data value
		 */
		FORCEINLINE const Type& operator*() const
		{
			return OldValue;
		}

	private:
		Type& RefValue;
		Type OldValue;
	};

	/**
	 * Helper class to make it easy to use key/value pairs with a container.
	 */
	template <typename KeyType, typename ValueType>
	struct TKeyValuePair
	{
		TKeyValuePair(const KeyType& InKey, const ValueType& InValue)
			: Key(InKey), Value(InValue)
		{
		}
		TKeyValuePair(const KeyType& InKey)
			: Key(InKey)
		{
		}
		TKeyValuePair()
		{
		}
		bool operator==(const TKeyValuePair& Other) const
		{
			return Key == Other.Key;
		}
		bool operator!=(const TKeyValuePair& Other) const
		{
			return Key != Other.Key;
		}
		bool operator<(const TKeyValuePair& Other) const
		{
			return Key < Other.Key;
		}
		FORCEINLINE bool operator()(const TKeyValuePair& A, const TKeyValuePair& B) const
		{
			return A.Key < B.Key;
		}
		KeyType		Key;
		ValueType	Value;
	};

	//
	// Macros that can be used to specify multiple template parameters in a macro parameter.
	// This is necessary to prevent the macro parsing from interpreting the template parameter
	// delimiting comma as a macro parameter delimiter.
	// 

#define TEMPLATE_PARAMETERS2(X,Y) X,Y


/**
 * Removes one level of pointer from a type, e.g.:
 *
 * TRemovePointer<      int32  >::Type == int32
 * TRemovePointer<      int32* >::Type == int32
 * TRemovePointer<      int32**>::Type == int32*
 * TRemovePointer<const int32* >::Type == const int32
 */
	template <typename T> struct TRemovePointer { typedef T Type; };
	template <typename T> struct TRemovePointer<T*> { typedef T Type; };

	/**
	 * CopyTemp will enforce the creation of an rvalue which can bind to rvalue reference parameters.
	 * Unlike MoveTemp, the source object will never be modifed. (i.e. a copy will be made)
	 * There is no std:: equivalent.
	 */
	template <typename T>
	FORCEINLINE T CopyTemp(T& Val)
	{
		return const_cast<const T&>(Val);
	}

	template <typename T>
	FORCEINLINE T CopyTemp(const T& Val)
	{
		return Val;
	}

	template <typename T>
	FORCEINLINE T&& CopyTemp(T&& Val)
	{
		// If we already have an rvalue, just return it unchanged, rather than needlessly creating yet another rvalue from it.
		return MoveTemp(Val);
	}

	/**
	 * Forward will cast a reference to an rvalue reference.
	 * This is UE's equivalent of std::forward.
	 */
	template <typename T>
	FORCEINLINE T&& Forward(typename TRemoveReference<T>::Type& Obj)
	{
		return (T&&)Obj;
	}

	template <typename T>
	FORCEINLINE T&& Forward(typename TRemoveReference<T>::Type&& Obj)
	{
		return (T&&)Obj;
	}

	/**
	 * A traits class which specifies whether a Swap of a given type should swap the bits or use a traditional value-based swap.
	 */
	template <typename T>
	struct TUseBitwiseSwap
	{
		// We don't use bitwise swapping for 'register' types because this will force them into memory and be slower.
		enum { Value = !TOrValue<__is_enum(T), TIsPointer<T>, TIsArithmetic<T>>::Value };
	};

	/**
	 * This exists to avoid a Visual Studio bug where using a cast to forward an rvalue reference array argument
	 * to a pointer parameter will cause bad code generation.  Wrapping the cast in a function causes the correct
	 * code to be generated.
	 */
	template <typename T, typename ArgType>
	FORCEINLINE T StaticCast(ArgType&& Arg)
	{
		return static_cast<T>(Arg);
	}

	/**
	 * TRValueToLValueReference converts any rvalue reference type into the equivalent lvalue reference, otherwise returns the same type.
	 */
	template <typename T> struct TRValueToLValueReference { typedef T  Type; };
	template <typename T> struct TRValueToLValueReference<T&&> { typedef T& Type; };

	/** Template for initializing a singleton at the boot. */
	template< class T >
	struct TForceInitAtBoot
	{
		TForceInitAtBoot()
		{
			T::Get();
		}
	};

	/** Used to avoid cluttering code with ifdefs. */
	struct FNoopStruct
	{
		FNoopStruct()
		{}

		~FNoopStruct()
		{}
	};

	/**
	 * Copies the cv-qualifiers from one type to another, e.g.:
	 *
	 * TCopyQualifiersFromTo<const    T1,       T2>::Type == const T2
	 * TCopyQualifiersFromTo<volatile T1, const T2>::Type == const volatile T2
	 */
	template <typename From, typename To> struct TCopyQualifiersFromTo { typedef                To Type; };
	template <typename From, typename To> struct TCopyQualifiersFromTo<const          From, To> { typedef const          To Type; };
	template <typename From, typename To> struct TCopyQualifiersFromTo<      volatile From, To> { typedef       volatile To Type; };
	template <typename From, typename To> struct TCopyQualifiersFromTo<const volatile From, To> { typedef const volatile To Type; };

	/**
	 * Tests if qualifiers are lost between one type and another, e.g.:
	 *
	 * TCopyQualifiersFromTo<const    T1,                T2>::Value == true
	 * TCopyQualifiersFromTo<volatile T1, const volatile T2>::Value == false
	 */
	template <typename From, typename To>
	struct TLosesQualifiersFromTo
	{
		enum { Value = !TAreTypesEqual<typename TCopyQualifiersFromTo<From, To>::Type, To>::Value };
	};

	/**
	 * Returns the same type passed to it.  This is useful in a few cases, but mainly for inhibiting template argument deduction in function arguments, e.g.:
	 *
	 * template <typename T>
	 * void Func1(T Val); // Can be called like Func(123) or Func<int>(123);
	 *
	 * template <typename T>
	 * void Func2(typename TIdentity<T>::Type Val); // Must be called like Func<int>(123)
	 */
	template <typename T>
	struct TIdentity
	{
		typedef T Type;
	};

	/**
	 * Metafunction which returns the specified boolean value.
	 */
	template <bool bValue>
	struct TBoolConstant
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