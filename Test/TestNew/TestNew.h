#include <malloc.h>  
#include <iostream>  

using namespace std;

void * operator new(size_t size)
{
	cout << "内存分配";
	return malloc(size);
}

#ifdef _DEBUG  

void * operator new(size_t size, const char *file, int line)
{
	cout << "new size:" << size << endl;
	cout << file << " " << line << endl;

	// 下面两种方法可以达到同样的效果，但下面一种比较好  
	// 因为用下面一种可以保持原有的申请方式一样  
	//void * p = malloc(size);  
	void * p = operator new(size);

	return p;
}

void operator delete(void * p)
{
	//cout << "delete " << (int)p << endl;
	free(p);
}

void operator delete [](void * p)
{
	//cout << "delete [] " << (int)p << endl;
	free(p);
}

void operator delete(void * p, const char *file, int line)
{
	cout << "delete file line" << endl;
	free(p);
}

void operator delete [](void * p, const char *file, int line)
{
	cout << "delete [] file line" << endl;
	free(p);
}

#define new new(__FILE__, __LINE__)  
#endif  