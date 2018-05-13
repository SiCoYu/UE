#pragma once

#include <cassert>
#include "MySmDelegateInstanceInterface.h"

using namespace MyNS;

namespace MyNS
{
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

		MySmBaseRawMethodDelegateInstance(UserClass* InUserObject, FMethodPtr InMethodPtr, VarTypes... Vars)
			: UserObject(InUserObject)
			, MethodPtr(InMethodPtr)
		{
			assert(InUserObject != nullptr && MethodPtr != nullptr);
		}

		// Deprecated
		virtual bool hasSameObject(const void* InUserObject) const override final
		{
			return UserObject == InUserObject;
		}

		virtual bool isValid() const override final
		{
			return true;
		}

	public:
		// 创建拷贝，全部都是拷贝，不是直接引用
		virtual void CreateCopy(MySmDelegateBase& Base) override final
		{
			//new (Base) UnwrappedThisType(*(UnwrappedThisType*)this);
			UnwrappedThisType* instance = new UnwrappedThisType(*(UnwrappedThisType*)this);
			Base.setDelegateInstance(instance);
		}

		virtual RetValType Execute(ParamTypes... Params) const override final
		{
			typedef typename TRemoveConst<UserClass>::Type MutableUserClass;

			// 通常会直接传入 UserObject 是 this， 这个是 const T ，如果不去掉 const ，直接调用，编译器会报错
			MutableUserClass* MutableUserObject = const_cast<MutableUserClass*>(UserObject);

			assert(MethodPtr != nullptr);

			return (MutableUserObject->*MethodPtr)(Params...);
		}

	public:
		FORCEINLINE static void Create(MySmDelegateBase& Base, UserClass* InUserObject, FMethodPtr InFunc, VarTypes... Vars)
		{
			//new (Base) UnwrappedThisType(InUserObject, InFunc, Vars...);
			UnwrappedThisType* instance = new UnwrappedThisType(InUserObject, InFunc, Vars...);
			Base.setDelegateInstance(instance);
		}

	protected:
		UserClass* UserObject;
		FMethodPtr MethodPtr;
	};

	template <bool bConst, class UserClass, typename... ParamTypes, typename... VarTypes>
	class MySmBaseRawMethodDelegateInstance<bConst, UserClass, void(ParamTypes...), VarTypes...> : public MySmBaseRawMethodDelegateInstance<bConst, UserClass, TTypeWrapper<void>(ParamTypes...), VarTypes...>
	{
		typedef MySmBaseRawMethodDelegateInstance<bConst, UserClass, TTypeWrapper<void>(ParamTypes...), VarTypes...> Super;

	public:
		MySmBaseRawMethodDelegateInstance(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, VarTypes... Vars)
			: Super(InUserObject, InMethodPtr, Vars...)
		{
		}

		virtual bool ExecuteIfSafe(ParamTypes... Params) const override final
		{
			Super::Execute(Params...);

			return true;
		}
	};

	template <typename FuncType, typename... VarTypes>
	class MySmBaseStaticDelegateInstance;

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
			assert(StaticFuncPtr != nullptr);
		}

		virtual bool hasSameObject(const void* UserObject) const override final
		{
			return false;
		}

		virtual bool isValid() const override final
		{
			return true;
		}

	public:
		virtual void CreateCopy(MySmDelegateBase& Base) override final
		{
			//new (Base) UnwrappedThisType(*(UnwrappedThisType*)this);
			UnwrappedThisType pInstance = new UnwrappedThisType(*(UnwrappedThisType*)this);
			Base.setDelegateInstance(pInstance);
		}

		virtual RetValType Execute(ParamTypes... Params) const override final
		{
			assert(StaticFuncPtr != nullptr);

			return StaticFuncPtr(Params...);
		}

	public:

		FORCEINLINE static void Create(MySmDelegateBase& Base, FFuncPtr InFunc, VarTypes... Vars)
		{
			//new (Base) UnwrappedThisType(InFunc, Vars...);
			UnwrappedThisType pInstance = new UnwrappedThisType(InFunc, Vars...);
			Base.setDelegateInstance(pInstance);
		}

	private:
		FFuncPtr StaticFuncPtr;
	};

	template <typename... ParamTypes, typename... VarTypes>
	class MySmBaseStaticDelegateInstance<void(ParamTypes...), VarTypes...> : public MySmBaseStaticDelegateInstance<TTypeWrapper<void>(ParamTypes...), VarTypes...>
	{
		typedef MySmBaseStaticDelegateInstance<TTypeWrapper<void>(ParamTypes...), VarTypes...> Super;

	public:
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