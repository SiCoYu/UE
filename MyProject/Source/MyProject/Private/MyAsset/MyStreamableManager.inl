

template< typename T >
T* FMyStreamableManager::SynchronousLoadType(std::string& path)
{
	return Cast< T >(SynchronousLoad(path));
}