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

	UObject* SynchronousLoad(std::string& path);

	template< typename T >
	T* SynchronousLoadType(std::string& path);
};

#include "MyStreamableManager.inl"