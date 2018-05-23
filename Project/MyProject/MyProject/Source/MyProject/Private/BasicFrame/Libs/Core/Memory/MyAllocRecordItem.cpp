#include "MyProject.h"
#include "MyAllocRecordItem.h"

MyAllocRecordItem::MyAllocRecordItem()
	:bytes(0), 
	line(0)
{

}

MyAllocRecordItem::MyAllocRecordItem(
	size_t sz, 
	unsigned int p, 
	const char* file, 
	size_t ln, 
	const char* func
)
	:bytes(sz), pool(p), line(ln)
{
	if (file)
		filename = file;
	if (func)
		function = func;
}