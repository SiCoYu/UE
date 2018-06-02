#ifndef __MyStreamableManager_H
#error "MyStreamableManager.inl file can only include in MyStreamableManager.h"
#endif

MY_BEGIN_NAMESPACE(MyNS)

template< typename T >
T* MyStreamableManager::SynchronousLoadType(std::string& path)
{
	return Cast< T >(SynchronousLoad(path));
}

MY_END_NAMESPACE