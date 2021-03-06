#pragma once

#include "IMySmDelegateInstance.h"

namespace MyNS
{
	class IMySmDelegateInstance;
	class MySmDelegateBase;

	template <typename FuncType>
	struct IMySmBaseDelegateInstance;

	template <typename FuncType>
	struct IMySmBaseDelegateInstanceCommon;

	template <typename RetType, typename... ArgTypes>
	struct IMySmBaseDelegateInstanceCommon<RetType(ArgTypes...)> : public IMySmDelegateInstance
	{
		/**
		* ��ȿ���
		*/
		virtual void CreateCopy(MySmDelegateBase& Base) = 0;

		/**
		* ִ��
		*/
		virtual RetType Execute(ArgTypes...) const = 0;
	};

	template <typename FuncType>
	struct IMySmBaseDelegateInstance : public IMySmBaseDelegateInstanceCommon<FuncType>
	{
	};

	template <typename... ArgTypes>
	struct IMySmBaseDelegateInstance<void(ArgTypes...)> : public IMySmBaseDelegateInstanceCommon<void(ArgTypes...)>
	{
		/**
		* Execute the delegate, but only if the function pointer is still valid
		*
		* @return  Returns true if the function was executed
		*/
		// NOTE: Currently only delegates with no return value support ExecuteIfSafe()
		virtual bool ExecuteIfSafe(ArgTypes...) const = 0;
	};

	template <bool Const, typename Class, typename FuncType>
	struct MyTMemFunPtrType;

	template <typename Class, typename RetType, typename... ArgTypes>
	struct MyTMemFunPtrType<false, Class, RetType(ArgTypes...)>
	{
		typedef RetType(Class::* Type)(ArgTypes...);
	};

	template <typename Class, typename RetType, typename... ArgTypes>
	struct MyTMemFunPtrType<true, Class, RetType(ArgTypes...)>
	{
		typedef RetType(Class::* Type)(ArgTypes...) const;
	};
}