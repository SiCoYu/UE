#pragma once

#include <string.h>
#include "Engine/StreamableManager.h"	 // FStreamableManager
#include "MyStreamableManager.generated.h"

USTRUCT()
struct FMyStreamableManager
{
	GENERATED_USTRUCT_BODY();

	FStreamableManager mStreamableManager;

	FMyStreamableManager();
	~FMyStreamableManager();

	/**
	* Synchronously load the referred asset and return the loaded object, or NULL if it can't be found.
	* A hard reference is made to the object (use Unload to release it), and this can be very slow.
	*/
	UObject* SynchronousLoad(std::string path);

	template< typename T >
	T* SynchronousLoadType(FStringAssetReference const& Target)
	{
		return Cast< T >(SynchronousLoad(Target));
	}
};