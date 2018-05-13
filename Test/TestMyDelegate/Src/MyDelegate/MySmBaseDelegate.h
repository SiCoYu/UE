#pragma once

#include "Templates/TypeWrapper.h"
#include "Templates/RemoveReference.h"
#include "Templates/UnrealTemplate.h"
#include "MySmDelegateBase.h"
#include "MySmDelegateInstancesImpl.h"

class MySmDelegateBase;
class IMySmDelegateInstance;
template <typename FuncType> struct IMySmBaseDelegateInstance;

namespace MyNS
{
	/**
	* Unicast delegate base object.
	*
	* Use the various DECLARE_DELEGATE macros to create the actual delegate type, templated to
	* the function signature the delegate is compatible with. Then, you can create an instance
	* of that class when you want to bind a function to the delegate.
	*/
	template <typename WrappedRetValType, typename... ParamTypes>
	class MySmBaseDelegate : public MySmDelegateBase
	{
	public:
		/** Type definition for return value type. */
		typedef typename TUnwrapType<WrappedRetValType>::Type RetValType;
		typedef RetValType TFuncType(ParamTypes...);

		/** Type definition for the shared interface of delegate instance types compatible with this delegate class. */
		typedef IMySmBaseDelegateInstance<TFuncType> MySmDelegateInstanceInterface;

		/** Declare the user's C++ pointer-based delegate instance types. */
		template <typename UserClass                                                                            > struct MySmRawMethodDelegate : MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType                                        > { typedef MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType                                        > Super; MySmRawMethodDelegate(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr) : Super(InUserObject, InMethodPtr) {} };
		template <typename UserClass                                                                            > struct MySmRawMethodDelegate_Const : MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType                                        > { typedef MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType                                        > Super; MySmRawMethodDelegate_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr) : Super(InUserObject, InMethodPtr) {} };
		template <typename UserClass, typename Var1Type                                                         > struct MySmRawMethodDelegate_OneVar : MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type                              > { typedef MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type                              > Super; MySmRawMethodDelegate_OneVar(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1) : Super(InUserObject, InMethodPtr, Var1) {} };
		template <typename UserClass, typename Var1Type                                                         > struct MySmRawMethodDelegate_OneVar_Const : MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type                              > { typedef MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type                              > Super; MySmRawMethodDelegate_OneVar_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1) : Super(InUserObject, InMethodPtr, Var1) {} };
		template <typename UserClass, typename Var1Type, typename Var2Type                                      > struct TRawMethodDelegate_TwoVars : MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type                    > { typedef MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type                    > Super; MySmRawMethodDelegate_TwoVars(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2) : Super(InUserObject, InMethodPtr, Var1, Var2) {} };
		template <typename UserClass, typename Var1Type, typename Var2Type                                      > struct TRawMethodDelegate_TwoVars_Const : MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type                    > { typedef MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type                    > Super; MySmRawMethodDelegate_TwoVars_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2) : Super(InUserObject, InMethodPtr, Var1, Var2) {} };
		template <typename UserClass, typename Var1Type, typename Var2Type, typename Var3Type                   > struct MySmRawMethodDelegate_ThreeVars : MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type, Var3Type          > { typedef MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type, Var3Type          > Super; MySmRawMethodDelegate_ThreeVars(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3) : Super(InUserObject, InMethodPtr, Var1, Var2, Var3) {} };
		template <typename UserClass, typename Var1Type, typename Var2Type, typename Var3Type                   > struct MySmRawMethodDelegate_ThreeVars_Const : MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type, Var3Type          > { typedef TBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type, Var3Type          > Super; TRawMethodDelegate_ThreeVars_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3) : Super(InUserObject, InMethodPtr, Var1, Var2, Var3) {} };
		template <typename UserClass, typename Var1Type, typename Var2Type, typename Var3Type, typename Var4Type> struct MySmRawMethodDelegate_FourVars : MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> { typedef MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> Super; MySmRawMethodDelegate_FourVars(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3, Var4Type Var4) : Super(InUserObject, InMethodPtr, Var1, Var2, Var3, Var4) {} };
		template <typename UserClass, typename Var1Type, typename Var2Type, typename Var3Type, typename Var4Type> struct MySmRawMethodDelegate_FourVars_Const : MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> { typedef MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> Super; MySmRawMethodDelegate_FourVars_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3, Var4Type Var4) : Super(InUserObject, InMethodPtr, Var1, Var2, Var3, Var4) {} };

		/** Declare the user's static function pointer delegate instance types. */
		struct MySmStaticDelegate : MySmBaseStaticDelegateInstance<TFuncType                                        > { typedef MySmBaseStaticDelegateInstance<TFuncType                                        > Super; MySmStaticDelegate(typename Super::FFuncPtr InFuncPtr) : Super(InFuncPtr) {} };
		template <typename Var1Type                                                         > struct TStaticDelegate_OneVar : MySmBaseStaticDelegateInstance<TFuncType, Var1Type                              > { typedef MySmBaseStaticDelegateInstance<TFuncType, Var1Type                              > Super; MySmStaticDelegate_OneVar(typename Super::FFuncPtr InFuncPtr, Var1Type Var1) : Super(InFuncPtr, Var1) {} };
		template <typename Var1Type, typename Var2Type                                      > struct TStaticDelegate_TwoVars : MySmBaseStaticDelegateInstance<TFuncType, Var1Type, Var2Type                    > { typedef MySmBaseStaticDelegateInstance<TFuncType, Var1Type, Var2Type                    > Super; MySmStaticDelegate_TwoVars(typename Super::FFuncPtr InFuncPtr, Var1Type Var1, Var2Type Var2) : Super(InFuncPtr, Var1, Var2) {} };
		template <typename Var1Type, typename Var2Type, typename Var3Type                   > struct TStaticDelegate_ThreeVars : MySmBaseStaticDelegateInstance<TFuncType, Var1Type, Var2Type, Var3Type          > { typedef MySmBaseStaticDelegateInstance<TFuncType, Var1Type, Var2Type, Var3Type          > Super; MySmStaticDelegate_ThreeVars(typename Super::FFuncPtr InFuncPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3) : Super(InFuncPtr, Var1, Var2, Var3) {} };
		template <typename Var1Type, typename Var2Type, typename Var3Type, typename Var4Type> struct TStaticDelegate_FourVars : MySmBaseStaticDelegateInstance<TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> { typedef MySmBaseStaticDelegateInstance<TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> Super; MySmStaticDelegate_FourVars(typename Super::FFuncPtr InFuncPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3, Var4Type Var4) : Super(InFuncPtr, Var1, Var2, Var3, Var4) {} };

	public:

		/**
		* Static: Creates a raw C++ pointer global function delegate
		*/
		template <typename... VarTypes>
		inline static MySmBaseDelegate<RetValType, ParamTypes...> CreateStatic(typename TIdentity<RetValType(*)(ParamTypes..., VarTypes...)>::Type InFunc, VarTypes... Vars)
		{
			TBaseDelegate<RetValType, ParamTypes...> Result;
			TBaseStaticDelegateInstance<TFuncType, VarTypes...>::Create(Result, InFunc, Vars...);
			return Result;
		}

		/**
		* Static: Creates a raw C++ pointer member function delegate.
		*
		* Raw pointer doesn't use any sort of reference, so may be unsafe to call if the object was
		* deleted out from underneath your delegate. Be careful when calling Execute()!
		*/
		template <typename UserClass, typename... VarTypes>
		inline static MySmBaseDelegate<RetValType, ParamTypes...> CreateRaw(UserClass* InUserObject, typename TMemFunPtrType<false, UserClass, RetValType(ParamTypes..., VarTypes...)>::Type InFunc, VarTypes... Vars)
		{
			MySmBaseDelegate<RetValType, ParamTypes...> Result;
			MySmBaseRawMethodDelegateInstance<false, UserClass, TFuncType, VarTypes...>::Create(Result, InUserObject, InFunc, Vars...);
			return Result;
		}
		template <typename UserClass, typename... VarTypes>
		inline static TBaseDelegate<RetValType, ParamTypes...> CreateRaw(UserClass* InUserObject, typename TMemFunPtrType<true, UserClass, RetValType(ParamTypes..., VarTypes...)>::Type InFunc, VarTypes... Vars)
		{
			MySmBaseDelegate<RetValType, ParamTypes...> Result;
			MySmBaseRawMethodDelegateInstance<true, UserClass, TFuncType, VarTypes...>::Create(Result, InUserObject, InFunc, Vars...);
			return Result;
		}

	public:

		/**
		* Default constructor
		*/
		inline MySmBaseDelegate()
		{
		}

		/**
		* 'Null' constructor
		*/
		inline MySmBaseDelegate(TYPE_OF_NULLPTR)
		{
		}

		/**
		* Destructor.
		*/
		inline ~MySmBaseDelegate()
		{
			Unbind();
		}

		/**
		* Creates and initializes a new instance from an existing delegate object.
		*
		* @param Other The delegate object to copy from.
		*/
		inline MySmBaseDelegate(const MySmBaseDelegate& Other)
		{
			*this = Other;
		}

		/**
		* Assignment operator.
		*
		* @param	OtherDelegate	Delegate object to copy from
		*/
		inline MySmBaseDelegate& operator=(const MySmBaseDelegate& Other)
		{
			if (&Other != this)
			{
				// this down-cast is OK! allows for managing invocation list in the base class without requiring virtual functions
				TDelegateInstanceInterface* OtherInstance = Other.GetDelegateInstanceProtected();

				if (OtherInstance != nullptr)
				{
					OtherInstance->CreateCopy(*this);
				}
				else
				{
					Unbind();
				}
			}

			return *this;
		}

	public:

		/**
		* Binds a raw C++ pointer global function delegate
		*/
		template <typename... VarTypes>
		inline void BindStatic(typename TBaseStaticDelegateInstance<TFuncType, VarTypes...>::FFuncPtr InFunc, VarTypes... Vars)
		{
			*this = CreateStatic(InFunc, Vars...);
		}

		/**
		* Binds a raw C++ pointer delegate.
		*
		* Raw pointer doesn't use any sort of reference, so may be unsafe to call if the object was
		* deleted out from underneath your delegate. Be careful when calling Execute()!
		*/
		template <typename UserClass, typename... VarTypes>
		inline void BindRaw(UserClass* InUserObject, typename TMemFunPtrType<false, UserClass, RetValType(ParamTypes..., VarTypes...)>::Type InFunc, VarTypes... Vars)
		{
			*this = CreateRaw(InUserObject, InFunc, Vars...);
		}
		template <typename UserClass, typename... VarTypes>
		inline void BindRaw(UserClass* InUserObject, typename TMemFunPtrType<true, UserClass, RetValType(ParamTypes..., VarTypes...)>::Type InFunc, VarTypes... Vars)
		{
			*this = CreateRaw(InUserObject, InFunc, Vars...);
		}

	public:
		/**
		* Execute the delegate.
		*
		* If the function pointer is not valid, an error will occur. Check IsBound() before
		* calling this method or use ExecuteIfBound() instead.
		*
		* @see ExecuteIfBound
		*/
		FORCEINLINE RetValType Execute(ParamTypes... Params) const
		{
			MySmDelegateInstanceInterface* LocalDelegateInstance = GetDelegateInstanceProtected();

			// If this assert goes off, Execute() was called before a function was bound to the delegate.
			// Consider using ExecuteIfSafe() instead.
			assert(LocalDelegateInstance != nullptr);

			return LocalDelegateInstance->Execute(Params...);
		}

		/**
		* Returns a pointer to the correctly-typed delegate instance.
		*/
		FORCEINLINE MySmDelegateInstanceInterface* GetDelegateInstanceProtected() const
		{
			return (MySmDelegateInstanceInterface*)mDelegateInstance;
		}
	};

	template <typename... ParamTypes>
	class MySmBaseDelegate<void, ParamTypes...> : public MySmBaseDelegate<TTypeWrapper<void>, ParamTypes...>
	{
		typedef MySmBaseDelegate<TTypeWrapper<void>, ParamTypes...> Super;

	public:
		typedef typename Super::MySmDelegateInstanceInterface MySmDelegateInstanceInterface;

		/**
		* Default constructor
		*/
		MySmBaseDelegate()
		{
		}

		/**
		* 'Null' constructor
		*/
		FORCEINLINE MySmBaseDelegate(TYPE_OF_NULLPTR)
			: Super(nullptr)
		{
		}

		/**
		* Creates and initializes a new instance from an existing delegate object.
		*
		* @param Other The delegate object to copy from.
		*/
		FORCEINLINE MySmBaseDelegate(const MySmBaseDelegate& Other)
			: Super(Other)
		{
		}

		/**
		* Assignment operator.
		*
		* @param	OtherDelegate	Delegate object to copy from
		*/
		inline MySmBaseDelegate& operator=(const MySmBaseDelegate& Other)
		{
			(Super&)*this = (Super&)Other;
			return *this;
		}

		/**
		* Execute the delegate, but only if the function pointer is still valid
		*
		* @return  Returns true if the function was executed
		*/
		// NOTE: Currently only delegates with no return value support ExecuteIfBound() 
		inline bool ExecuteIfBound(ParamTypes... Params) const
		{
			if (Super::IsBound())
			{
				return Super::GetDelegateInstanceProtected()->ExecuteIfSafe(Params...);
			}

			return false;
		}
	};
}