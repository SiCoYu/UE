template <class T>
LockQueue<T>::LockQueue(std::string name)
{
	m_list = new LockList<T>("name");
}

template <class T>
void LockQueue<T>::push(T item)


template <class T>
T LockQueue<T>::pop()
{
	return m_list.RemoveAt(0);
}