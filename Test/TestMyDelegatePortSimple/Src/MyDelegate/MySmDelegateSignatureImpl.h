#pragma once

#include "Templates/MyTypeWrapper.h"
#include "Templates/MyRemoveReference.h"
#include "Templates/MyBaseTemplate.h"
#include "MySmDelegateBase.h"
#include "MySmDelegateInstancesImpl.h"

class MySmDelegateBase;
class IMySmDelegateInstance;
template <typename FuncType> struct IMySmBaseDelegateInstance;

namespace MyNS
{
	/**
	* @brief 使用 DECLARE_DELEGATE 宏创建, 
	*/
	template <typename WrappedRetValType, typename... ParamTypes>
	class MySmBaseDelegate : public MySmDelegateBase
	{
	public:
		/** 定义返回类型 */
		typedef typename MyTUnwrapType<WrappedRetValType>::Type RetValType;
		typedef RetValType TFuncType(ParamTypes...);

		/** 定义 Instance 类型 */
		typedef IMySmBaseDelegateInstance<TFuncType> MySmDelegateInstanceInterface;

		/** Declare the user's C++ pointer-based delegate instance types. */
		template <typename UserClass                                                                            > struct MySmRawMethodDelegate : MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType                                        > { typedef MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType                                        > Super; MySmRawMethodDelegate(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr) : Super(InUserObject, InMethodPtr) {} };
		template <typename UserClass                                                                            > struct MySmRawMethodDelegate_Const : MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType                                        > { typedef MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType                                        > Super; MySmRawMethodDelegate_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr) : Super(InUserObject, InMethodPtr) {} };
		template <typename UserClass, typename Var1Type                                                         > struct MySmRawMethodDelegate_OneVar : MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type                              > { typedef MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type                              > Super; MySmRawMethodDelegate_OneVar(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1) : Super(InUserObject, InMethodPtr, Var1) {} };
		template <typename UserClass, typename Var1Type                                                         > struct MySmRawMethodDelegate_OneVar_Const : MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type                              > { typedef MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type                              > Super; MySmRawMethodDelegate_OneVar_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1) : Super(InUserObject, InMethodPtr, Var1) {} };
		template <typename UserClass, typename Var1Type, typename Var2Type                                      > struct MySmRawMethodDelegate_TwoVars : MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type                    > { typedef MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type                    > Super; MySmRawMethodDelegate_TwoVars(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2) : Super(InUserObject, InMethodPtr, Var1, Var2) {} };
		template <typename UserClass, typename Var1Type, typename Var2Type                                      > struct MySmRawMethodDelegate_TwoVars_Const : MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type                    > { typedef MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type                    > Super; MySmRawMethodDelegate_TwoVars_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2) : Super(InUserObject, InMethodPtr, Var1, Var2) {} };
		template <typename UserClass, typename Var1Type, typename Var2Type, typename Var3Type                   > struct MySmRawMethodDelegate_ThreeVars : MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type, Var3Type          > { typedef MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type, Var3Type          > Super; MySmRawMethodDelegate_ThreeVars(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3) : Super(InUserObject, InMethodPtr, Var1, Var2, Var3) {} };
		template <typename UserClass, typename Var1Type, typename Var2Type, typename Var3Type                   > struct MySmRawMethodDelegate_ThreeVars_Const : MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type, Var3Type          > { typedef MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type, Var3Type          > Super; MySmRawMethodDelegate_ThreeVars_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3) : Super(InUserObject, InMethodPtr, Var1, Var2, Var3) {} };
		template <typename UserClass, typename Var1Type, typename Var2Type, typename Var3Type, typename Var4Type> struct MySmRawMethodDelegate_FourVars : MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> { typedef MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> Super; MySmRawMethodDelegate_FourVars(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3, Var4Type Var4) : Super(InUserObject, InMethodPtr, Var1, Var2, Var3, Var4) {} };
		template <typename UserClass, typename Var1Type, typename Var2Type, typename Var3Type, typename Var4Type> struct MySmRawMethodDelegate_FourVars_Const : MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> { typedef MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> Super; MySmRawMethodDelegate_FourVars_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3, Var4Type Var4) : Super(InUserObject, InMethodPtr, Var1, Var2, Var3, Var4) {} };

		///** Declare the user's static function pointer delegate instance types. */
		struct MySmStaticDelegate : MySmBaseStaticDelegateInstance<TFuncType                                        > { typedef MySmBaseStaticDelegateInstance<TFuncType                                        > Super; MySmStaticDelegate(typename Super::FFuncPtr InFuncPtr) : Super(InFuncPtr) {} };
		template <typename Var1Type                                                         > struct MySmStaticDelegate_OneVar : MySmBaseStaticDelegateInstance<TFuncType, Var1Type                              > { typedef MySmBaseStaticDelegateInstance<TFuncType, Var1Type                              > Super; MySmStaticDelegate_OneVar(typename Super::FFuncPtr InFuncPtr, Var1Type Var1) : Super(InFuncPtr, Var1) {} };
		template <typename Var1Type, typename Var2Type                                      > struct MySmStaticDelegate_TwoVars : MySmBaseStaticDelegateInstance<TFuncType, Var1Type, Var2Type                    > { typedef MySmBaseStaticDelegateInstance<TFuncType, Var1Type, Var2Type                    > Super; MySmStaticDelegate_TwoVars(typename Super::FFuncPtr InFuncPtr, Var1Type Var1, Var2Type Var2) : Super(InFuncPtr, Var1, Var2) {} };
		template <typename Var1Type, typename Var2Type, typename Var3Type                   > struct MySmStaticDelegate_ThreeVars : MySmBaseStaticDelegateInstance<TFuncType, Var1Type, Var2Type, Var3Type          > { typedef MySmBaseStaticDelegateInstance<TFuncType, Var1Type, Var2Type, Var3Type          > Super; MySmStaticDelegate_ThreeVars(typename Super::FFuncPtr InFuncPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3) : Super(InFuncPtr, Var1, Var2, Var3) {} };
		template <typename Var1Type, typename Var2Type, typename Var3Type, typename Var4Type> struct MySmStaticDelegate_FourVars : MySmBaseStaticDelegateInstance<TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> { typedef MySmBaseStaticDelegateInstance<TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> Super; MySmStaticDelegate_FourVars(typename Super::FFuncPtr InFuncPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3, Var4Type Var4) : Super(InFuncPtr, Var1, Var2, Var3, Var4) {} };

	public:
		template <typename... VarTypes>
		inline static MySmBaseDelegate<RetValType, ParamTypes...> CreateStatic(typename MyTIdentity<RetValType(*)(ParamTypes..., VarTypes...)>::Type InFunc, VarTypes... Vars)
		{
			MySmBaseDelegate<RetValType, ParamTypes...> Result;
			MySmBaseStaticDelegateInstance<TFuncType, VarTypes...>::Create(Result, InFunc, Vars...);
			return Result;
		}

		template <typename UserClass, typename... VarTypes>
		inline static MySmBaseDelegate<RetValType, ParamTypes...> CreateRaw(UserClass* InUserObject, typename MyTMemFunPtrType<false, UserClass, RetValType(ParamTypes..., VarTypes...)>::Type InFunc, VarTypes... Vars)
		{
			MySmBaseDelegate<RetValType, ParamTypes...> Result;
			MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, VarTypes...>::Create(Result, InUserObject, InFunc, Vars...);
			return Result;
		}

		template <typename UserClass, typename... VarTypes>
		inline static MySmBaseDelegate<RetValType, ParamTypes...> CreateRaw(UserClass* InUserObject, typename MyTMemFunPtrType<true, UserClass, RetValType(ParamTypes..., VarTypes...)>::Type InFunc, VarTypes... Vars)
		{
			MySmBaseDelegate<RetValType, ParamTypes...> Result;
			MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, VarTypes...>::Create(Result, InUserObject, InFunc, Vars...);
			return Result;
		}

	public:
		inline MySmBaseDelegate()
		{
		}

		/**
		* 'Null' 构造
		*/
		//inline MySmBaseDelegate(TYPE_OF_NULLPTR)
		//{
		//}

		template <typename T>
		inline MySmBaseDelegate(T param)
		{
		}

		//template <typename... VarTypes>
		//inline MySmBaseDelegate(int flag, typename MySmBaseStaticDelegateInstance<TFuncType, VarTypes...>::FFuncPtr InFunc, VarTypes... Vars)
		//{
		//	this->BindStatic(InFunc, Vars...);
		//}

		//template <typename UserClass, typename... VarTypes>
		//inline MySmBaseDelegate(UserClass* InUserObject, typename MyTMemFunPtrType<false, UserClass, RetValType(ParamTypes..., VarTypes...)>::Type InFunc, VarTypes... Vars)
		//{
		//	this->BindRaw(InUserObject, InFunc, Vars...);
		//}

		//template <typename UserClass, typename... VarTypes>
		//inline MySmBaseDelegate(UserClass* InUserObject, typename MyTMemFunPtrType<true, UserClass, RetValType(ParamTypes..., VarTypes...)>::Type InFunc, VarTypes... Vars)
		//{
		//	this->BindRaw(InUserObject, InFunc, Vars...);
		//}

		inline ~MySmBaseDelegate()
		{
			this->unbind();
		}

		inline MySmBaseDelegate(const MySmBaseDelegate& Other)
		{
			*this = Other;
		}

		inline MySmBaseDelegate& operator=(const MySmBaseDelegate& Other)
		{
			if (&Other != this)
			{
				MySmDelegateInstanceInterface* OtherInstance = Other.GetDelegateInstanceProtected();

				if (OtherInstance != nullptr)
				{
					OtherInstance->CreateCopy(*this);
				}
				else
				{
					this->unbind();
				}
			}

			return *this;
		}

		//inline bool operator!()
		//{
		//	return false;
		//}

		// warning C4717: 'MyNS::MySmBaseDelegate<void,int,int,bool>::MySmBaseDelegate<void,int,int,bool>': recursive on all control paths, function will cause runtime stack overflow
		//friend inline bool operator != (MySmBaseDelegate rhl, std::nullptr_t)
		//{
		//	return false;
		//}

		//friend inline bool operator != (std::nullptr_t, MySmBaseDelegate rhl)
		//{
		//	return false;
		//}

	public:
		template <typename... VarTypes>
		inline void BindStatic(typename MySmBaseStaticDelegateInstance<TFuncType, VarTypes...>::FFuncPtr InFunc, VarTypes... Vars)
		{
			*this = this->CreateStatic(InFunc, Vars...);
		}

		template <typename UserClass, typename... VarTypes>
		inline void BindRaw(UserClass* InUserObject, typename MyTMemFunPtrType<false, UserClass, RetValType(ParamTypes..., VarTypes...)>::Type InFunc, VarTypes... Vars)
		{
			*this = this->CreateRaw(InUserObject, InFunc, Vars...);
		}

		template <typename UserClass, typename... VarTypes>
		inline void BindRaw(UserClass* InUserObject, typename MyTMemFunPtrType<true, UserClass, RetValType(ParamTypes..., VarTypes...)>::Type InFunc, VarTypes... Vars)
		{
			*this = this->CreateRaw(InUserObject, InFunc, Vars...);
		}

	public:
		FORCEINLINE RetValType Execute(ParamTypes... Params) const
		{
			MySmDelegateInstanceInterface* LocalDelegateInstance = GetDelegateInstanceProtected();

			assert(LocalDelegateInstance != nullptr);

			return LocalDelegateInstance->Execute(Params...);
		}

		FORCEINLINE MySmDelegateInstanceInterface* GetDelegateInstanceProtected() const
		{
			return (MySmDelegateInstanceInterface*)mDelegateInstance;
		}
	};

	template <typename... ParamTypes>
	class MySmBaseDelegate<void, ParamTypes...> : public MySmBaseDelegate<MyTTypeWrapper<void>, ParamTypes...>
	{
		typedef MySmBaseDelegate<MyTTypeWrapper<void>, ParamTypes...> Super;

	public:
		typedef typename Super::MySmDelegateInstanceInterface MySmDelegateInstanceInterface;

		MySmBaseDelegate()
		{
		}

		/**
		* 'Null' 构造
		*/
		FORCEINLINE MySmBaseDelegate(TYPE_OF_NULLPTR)
			: Super(nullptr)
		{
		}

		FORCEINLINE MySmBaseDelegate(const MySmBaseDelegate& Other)
			: Super(Other)
		{
		}

		//template <typename T>
		//inline MySmBaseDelegate(T param)
		//	: Super(param)
		//{
		//	
		//}

		// 直接 MySmBaseDelegate<void, int, int, bool>::MySmBaseDelegate(this, &Class::handle) 这样写会编译报错,因为第一个参数都是指针，编译器会错误把 this 对象指针当做函数指针去处理，导致编译错误，直接匹配静态函数
		//template <typename... VarTypes>
		//inline MySmBaseDelegate(int flag, typename MySmBaseStaticDelegateInstance<TFuncType, VarTypes...>::FFuncPtr InFunc, VarTypes... Vars)
		//	: Super(flag, InFunc, Vars...)
		//{

		//}

		//template <typename UserClass, typename... VarTypes>
		//inline MySmBaseDelegate(UserClass* InUserObject, typename MyTMemFunPtrType<false, UserClass, RetValType(ParamTypes..., VarTypes...)>::Type InFunc, VarTypes... Vars)
		//	: Super(InUserObject, InFunc, Vars...)
		//{
		//	
		//}

		//template <typename UserClass, typename... VarTypes>
		//inline MySmBaseDelegate(UserClass* InUserObject, typename MyTMemFunPtrType<true, UserClass, RetValType(ParamTypes..., VarTypes...)>::Type InFunc, VarTypes... Vars)
		//	: Super(InUserObject, InFunc, Vars...)
		//{
		//	
		//}

		inline MySmBaseDelegate& operator=(const MySmBaseDelegate& Other)
		{
			(Super&)*this = (Super&)Other;
			return *this;
		}

		inline bool ExecuteIfBound(ParamTypes... Params) const
		{
			if (Super::isValid())
			{
				return Super::GetDelegateInstanceProtected()->ExecuteIfSafe(Params...);
			}

			return false;
		}
	};
}