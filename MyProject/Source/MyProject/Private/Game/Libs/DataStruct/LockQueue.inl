template <class T>
LockQueue<T>::LockQueue(string name)
{
	m_list = new LockList<T>("name");
}

template <class T>
void LockQueue<T>::push(T item)
{
	m_list.Add(item);
}

template <class T>
T LockQueue<T>::pop()
{
	return m_list.RemoveAt(0);
}