#include "MyProject.h"
#include "AddOnceEventDispatch.h"

AddOnceEventDispatch::AddOnceEventDispatch(int eventId_)
	: EventDispatch(eventId_)
{

}

void AddOnceEventDispatch::addEventHandle(EventDispatchDelegate handle)
{
	// 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
	if (!this->isExistEventHandle(handle))
	{
		Super::addEventHandle(handle);
	}
}