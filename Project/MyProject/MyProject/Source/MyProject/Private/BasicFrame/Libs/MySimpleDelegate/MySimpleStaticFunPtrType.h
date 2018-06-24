#pragma once

namespace MyNS
{
	template <typename FuncType>
	struct MySimpleStaticFunPtrType;

	template <typename RetType, typename... ArgTypes>
	struct MySimpleMemFunPtrType<RetType(ArgTypes...)>
	{
		typedef RetType(Class::* Type)(ArgTypes...);
	};
}