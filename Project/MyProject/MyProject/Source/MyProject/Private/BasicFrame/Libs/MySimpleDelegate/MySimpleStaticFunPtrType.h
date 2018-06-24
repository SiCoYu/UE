#pragma once

namespace MyNS
{
	template <typename FuncType>
	struct MySimpleStaticFunPtrType;

	template <typename RetType, typename... ArgTypes>
	struct MySimpleStaticFunPtrType<RetType(ArgTypes...)>
	{
		typedef RetType(* Type)(ArgTypes...);
	};
}