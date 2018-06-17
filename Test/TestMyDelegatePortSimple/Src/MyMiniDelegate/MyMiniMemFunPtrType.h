#pragma once

namespace MyNS
{
	template <bool Const, typename Class, typename FuncType>
	struct MyMiniMemFunPtrType;

	template <typename Class, typename RetType, typename... ArgTypes>
	struct MyMiniMemFunPtrType<false, Class, RetType(ArgTypes...)>
	{
		typedef RetType(Class::* Type)(ArgTypes...);
	};

	template <typename Class, typename RetType, typename... ArgTypes>
	struct MyMiniMemFunPtrType<true, Class, RetType(ArgTypes...)>
	{
		typedef RetType(Class::* Type)(ArgTypes...) const;
	};
}