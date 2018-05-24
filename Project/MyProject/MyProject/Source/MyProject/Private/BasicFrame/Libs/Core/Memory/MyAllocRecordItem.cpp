#include "MyProject.h"
#include "MyAllocRecordItem.h"

MyAllocRecordItem::MyAllocRecordItem()
	:mBytes(0),
	 mLine(0)
{

}

MyAllocRecordItem::MyAllocRecordItem(
	size_t sz, 
	const char* file, 
	size_t ln, 
	const char* func
)
	:mBytes(sz), mLine(ln)
{
	if (file)
		mFileName = file;
	if (func)
		mFunction = func;
}