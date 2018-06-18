#pragma once

namespace MyNS
{
	template <bool Const, typename Class, typename FuncType>
	struct MySimpleMemFunPtrType;

	template <typename Class, typename RetType, typename... ArgTypes>
	struct MySimpleMemFunPtrType<false, Class, RetType(ArgTypes...)>
	{
		typedef RetType(Class::* Type)(ArgTypes...);
	};

	template <typename Class, typename RetType, typename... ArgTypes>
	struct MySimpleMemFunPtrType<true, Class, RetType(ArgTypes...)>
	{
		typedef RetType(Class::* Type)(ArgTypes...) const;
	};
}