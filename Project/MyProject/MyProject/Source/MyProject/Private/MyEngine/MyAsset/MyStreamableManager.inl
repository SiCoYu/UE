#ifndef __MyStreamableManager_H
#error "MyStreamableManager.inl file can only include in MyStreamableManager.h"
#endif

template< typename T >
T* FMyStreamableManager::SynchronousLoadType(std::string& path)
{
	return Cast< T >(SynchronousLoad(path));
}