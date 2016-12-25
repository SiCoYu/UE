

template< typename T >
T* FMyStreamableManager::SynchronousLoadType(const std::string& path)
{
	return Cast< T >(SynchronousLoad(path));
}