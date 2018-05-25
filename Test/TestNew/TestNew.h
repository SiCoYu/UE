#include <malloc.h>  
#include <iostream>  

using namespace std;

void * operator new(size_t size)
{
	cout << "�ڴ����";
	return malloc(size);
}

#ifdef _DEBUG  

void * operator new(size_t size, const char *file, int line)
{
	cout << "new size:" << size << endl;
	cout << file << " " << line << endl;

	// �������ַ������Դﵽͬ����Ч����������һ�ֱȽϺ�  
	// ��Ϊ������һ�ֿ��Ա���ԭ�е����뷽ʽһ��  
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