#include "TestNew.h"
#include "ClassNew.h"

void main()
{
	int * p = new int[5];
	delete[] p;
	// delete p;
	ClassNew* aaa = new ClassNew();

}