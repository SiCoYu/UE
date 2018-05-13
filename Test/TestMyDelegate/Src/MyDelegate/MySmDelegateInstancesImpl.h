#pragma once

#include <cassert>
#include "MySmDelegateInstanceInterface.h"

namespace MyNS
{
	/**
	* Implements a delegate binding for C++ member functions.
	*/
	template <bool bConst, class UserClass, typename FuncType, typename... VarTypes>
	class MySmBaseRawMethodDelegateInstance;

	template <bool bConst, class UserClass, typename WrappedRetValType, typename... ParamTypes, typename... VarTypes>
	class MySmBaseRawMethodDelegateInstance<bConst, UserClass, WrappedRetValType(ParamTypes...), VarTypes...> : public IMySmBaseDelegateInstance<typename TUnwrapType<WrappedRetValType>::Type(ParamTypes...)>
	{
	public:
		typedef typename TUnwrapType<WrappedRetValType>::Type RetValType;

	private:
		typedef IMySmBaseDelegateInstance<RetValType(ParamTypes...)>                                          Super;
		typedef MySmBaseRawMethodDelegateInstance<bConst, UserClass, RetValType(ParamTypes...), VarTypes...> UnwrappedThisType;

	public:
		typedef typename TMemFunPtrType<bConst, UserClass, RetValType(ParamTypes..., VarTypes...)>::Type FMethodPtr;

		/**
		* Creates and initializes a new instance.
		*
		* @param InUserObject An arbitrary object (templated) that hosts the member function.
		* @param InMethodPtr C++ member function pointer for the method to bind.
		*/
		MySmBaseRawMethodDelegateInstance(UserClass* InUserObject, FMethodPtr InMethodPtr, VarTypes... Vars)
			: UserObject(InUserObject)
			, MethodPtr(InMethodPtr)
		{
			// Non-expirable delegates must always have a non-null object pointer on creation (otherwise they could never execute.)
			assert(InUserObject != nullptr && MethodPtr != nullptr);
		}

		// Deprecated
		virtual bool HasSameObject(const void* InUserObject) const override final
		{
			return UserObject == InUserObject;
		}

		virtual bool IsSafeToExecute() const override final
		{
			// We never know whether or not it is safe to deference a C++ pointer, but we have to
			// trust the user in this case.  Prefer using a shared-pointer based delegate type instead!
			return true;
		}

	public:

		// IBaseDelegateInstance interface

		virtual void CreateCopy(MySmDelegateBase& Base) override final
		{
			new (Base) UnwrappedThisType(*(UnwrappedThisType*)this);
		}

		virtual RetValType Execute(ParamTypes... Params) const override final
		{
			typedef typename TRemoveConst<UserClass>::Type MutableUserClass;

			// Safely remove const to work around a compiler issue with instantiating template permutations for 
			// overloaded functions that take a function pointer typedef as a member of a templated class.  In
			// all cases where this code is actually invoked, the UserClass will already be a const pointer.
			MutableUserClass* MutableUserObject = const_cast<MutableUserClass*>(UserObject);

			// Call the member function on the user's object.  And yes, this is the correct C++ syntax for calling a
			// pointer-to-member function.
			assert(MethodPtr != nullptr);

			return (UserObject.*MethodPtr)(args...);
		}

	public:

		/**
		* Creates a new raw method delegate binding for the given user object and function pointer.
		*
		* @param InUserObject User's object that contains the class method.
		* @param InFunc Member function pointer to your class method.
		* @return The new delegate.
		*/
		FORCEINLINE static void Create(MySmDelegateBase& Base, UserClass* InUserObject, FMethodPtr InFunc, VarTypes... Vars)
		{
			new (Base) UnwrappedThisType(InUserObject, InFunc, Vars...);
		}

	protected:

		// Pointer to the user's class which contains a method we would like to call.
		UserClass* UserObject;

		// C++ member function pointer.
		FMethodPtr MethodPtr;
	};

	template <bool bConst, class UserClass, typename... ParamTypes, typename... VarTypes>
	class MySmBaseRawMethodDelegateInstance<bConst, UserClass, void(ParamTypes...), VarTypes...> : public MySmBaseRawMethodDelegateInstance<bConst, UserClass, TTypeWrapper<void>(ParamTypes...), VarTypes...>
	{
		typedef MySmBaseRawMethodDelegateInstance<bConst, UserClass, TTypeWrapper<void>(ParamTypes...), VarTypes...> Super;

	public:
		/**
		* Creates and initializes a new instance.
		*
		* @param InUserObject An arbitrary object (templated) that hosts the member function.
		* @param InMethodPtr C++ member function pointer for the method to bind.
		*/
		MySmBaseRawMethodDelegateInstance(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, VarTypes... Vars)
			: Super(InUserObject, InMethodPtr, Vars...)
		{
		}

		virtual bool ExecuteIfSafe(ParamTypes... Params) const override final
		{
			// We never know whether or not it is safe to deference a C++ pointer, but we have to
			// trust the user in this case.  Prefer using a shared-pointer based delegate type instead!
			Super::Execute(Params...);

			return true;
		}
	};

	/**
	* Implements a delegate binding for regular C++ functions.
	*/
	template <typename FuncType, typename... VarTypes>
	class TMySmBaseStaticDelegateInstance;

	template <typename WrappedRetValType, typename... ParamTypes, typename... VarTypes>
	class MySmBaseStaticDelegateInstance<WrappedRetValType(ParamTypes...), VarTypes...> : public IMySmBaseDelegateInstance<typename TUnwrapType<WrappedRetValType>::Type(ParamTypes...)>
	{
	public:
		typedef typename TUnwrapType<WrappedRetValType>::Type RetValType;

		typedef IMySmBaseDelegateInstance<RetValType(ParamTypes...)>                    Super;
		typedef MySmBaseStaticDelegateInstance<RetValType(ParamTypes...), VarTypes...> UnwrappedThisType;

	public:
		typedef RetValType(*FFuncPtr)(ParamTypes..., VarTypes...);

		MySmBaseStaticDelegateInstance(FFuncPtr InStaticFuncPtr, VarTypes... Vars)
			: StaticFuncPtr(InStaticFuncPtr)
			, Payload(Vars...)
			, Handle(FDelegateHandle::GenerateNewHandle)
		{
			check(StaticFuncPtr != nullptr);
		}

		// Deprecated
		virtual bool HasSameObject(const void* UserObject) const override final
		{
			// Raw Delegates aren't bound to an object so they can never match
			return false;
		}

		virtual bool IsSafeToExecute() const override final
		{
			// Static functions are always safe to execute!
			return true;
		}

	public:

		// IBaseDelegateInstance interface

		virtual void CreateCopy(FDelegateBase& Base) override final
		{
			new (Base) UnwrappedThisType(*(UnwrappedThisType*)this);
		}

		virtual RetValType Execute(ParamTypes... Params) const override final
		{
			// Call the static function
			checkSlow(StaticFuncPtr != nullptr);

			return Payload.ApplyAfter(StaticFuncPtr, Params...);
		}

	public:

		/**
		* Creates a new static function delegate binding for the given function pointer.
		*
		* @param InFunc Static function pointer.
		* @return The new delegate.
		*/
		FORCEINLINE static void Create(FDelegateBase& Base, FFuncPtr InFunc, VarTypes... Vars)
		{
			new (Base) UnwrappedThisType(InFunc, Vars...);
		}

	private:

		// C++ function pointer.
		FFuncPtr StaticFuncPtr;
	};

	template <typename... ParamTypes, typename... VarTypes>
	class MySmBaseStaticDelegateInstance<void(ParamTypes...), VarTypes...> : public MySmBaseStaticDelegateInstance<TTypeWrapper<void>(ParamTypes...), VarTypes...>
	{
		typedef BaseStaticDelegateInstance<TTypeWrapper<void>(ParamTypes...), VarTypes...> Super;

	public:
		/**
		* Creates and initializes a new instance.
		*
		* @param InStaticFuncPtr C++ function pointer.
		*/
		MySmBaseStaticDelegateInstance(typename Super::FFuncPtr InStaticFuncPtr, VarTypes... Vars)
			: Super(InStaticFuncPtr, Vars...)
		{
		}

		virtual bool ExecuteIfSafe(ParamTypes... Params) const override final
		{
			Super::Execute(Params...);

			return true;
		}
	};
}