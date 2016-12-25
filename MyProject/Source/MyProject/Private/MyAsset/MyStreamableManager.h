#pragma once

#include <string>
#include "Engine/StreamableManager.h"	 // FStreamableManager

class FMyStreamableManager
{
public:
	FStreamableManager mStreamableManager;

	FMyStreamableManager();
	~FMyStreamableManager();

	void init();
	void dispose();

	UObject* SynchronousLoad(const std::string& path);

	template< typename T >
	T* SynchronousLoadType(const std::string& path);
};

#include "MyStreamableManager.inl"