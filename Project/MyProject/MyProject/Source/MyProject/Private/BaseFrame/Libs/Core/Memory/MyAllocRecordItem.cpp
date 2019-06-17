#include "MyProject.h"
#include "MyAllocRecordItem.h"

MY_BEGIN_NAMESPACE(MyNS)

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
	:mBytes(sz), 
	 mLine(ln)
{
	if (file)
	{
		this->mFileName = file;
	}
	if (func)
	{
		this->mFunction = func;
	}
}

MY_END_NAMESPACE