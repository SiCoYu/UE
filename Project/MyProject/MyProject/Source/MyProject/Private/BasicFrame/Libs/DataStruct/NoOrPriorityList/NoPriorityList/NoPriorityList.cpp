#include "MyProject.h"
#include "NoPriorityList.h"
#include "MacroDef.h"
#include "Ctx.h"
#include "LogSys.h"
#include "LogTypeId.h"

MY_BEGIN_NAMESPACE(MyNS)

NoPriorityList::NoPriorityList()
{
	//this->mNoPriorityProcessObjectList = new MList<INoOrPriorityObject>();
	this->mIsSpeedUpFind = false;
}

void NoPriorityList::init()
{

}

void NoPriorityList::dispose()
{
	//if(nullptr != this->mNoPriorityProcessObjectList)
	//{
		this->mNoPriorityProcessObjectList.dispose();
		//this->mNoPriorityProcessObjectList = nullptr;
	//}
	//if (nullptr != this->mDic)
	//{
		this->mDic.dispose();
		//this->mDic = nullptr;
	//}

	this->clear();
}

void NoPriorityList::setIsSpeedUpFind(bool value)
{
	this->mIsSpeedUpFind = value;

	//if (this->mIsSpeedUpFind)
	//{
	//	this->mDic = new MDictionary<INoOrPriorityObject, int>();
	//}
}

void NoPriorityList::setIsOpKeepSort(bool value)
{

}

void NoPriorityList::clear()
{
	this->mNoPriorityProcessObjectList.clear();

	if(this->mIsSpeedUpFind)
	{
		this->mDic.clear();
	}
}

int NoPriorityList::count()
{
	return this->mNoPriorityProcessObjectList.count();
}

INoOrPriorityObject* NoPriorityList::get(int index)
{
	INoOrPriorityObject* ret = nullptr;

	if(index < this->count())
	{
		ret = this->mNoPriorityProcessObjectList.get(index);
	}

	return ret;
}

bool NoPriorityList::contains(INoOrPriorityObject* item)
{
	bool ret = false;

	if (nullptr != item)
	{
		if (this->mIsSpeedUpFind)
		{
			ret = this->mDic.containsKey(item);
		}
		else
		{
			int index = 0;
			int listLen = this->mNoPriorityProcessObjectList.count();

			while (index < listLen)
			{
				if (item == this->mNoPriorityProcessObjectList.get(index))
				{
					ret = true;
					break;
				}

				++index;
			}
		}
	}
	else
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log("NoPriorityList::Contains, failed", LogTypeId::eLogNoPriorityListCheck);
		}
	}

	return ret;
}

void NoPriorityList::removeAt(int index)
{
	if (this->mIsSpeedUpFind)
	{
		this->_effectiveRemove(this->mNoPriorityProcessObjectList[index]);
	}
	else
	{
		this->mNoPriorityProcessObjectList.removeAt(index);
	}
}

int NoPriorityList::getIndexByNoPriorityObject(INoOrPriorityObject* priorityObject)
{
	int retIndex = -1;

	int index = 0;
	int listLen = this->mNoPriorityProcessObjectList.count();

	while (index < listLen)
	{
		if (this->mNoPriorityProcessObjectList.get(index) == priorityObject)
		{
			retIndex = index;
			break;
		}

		++index;
	}

	return retIndex;
}

int NoPriorityList::getIndexByNoOrPriorityObject(INoOrPriorityObject* priorityObject)
{
	return this->getIndexByNoPriorityObject(priorityObject);
}

void NoPriorityList::addNoPriorityObject(INoOrPriorityObject* noPriorityObject)
{
	if (nullptr != noPriorityObject)
	{
		if (!this->contains(noPriorityObject))
		{
			this->mNoPriorityProcessObjectList.add(noPriorityObject);

			if (this->mIsSpeedUpFind)
			{
				this->mDic.add(noPriorityObject, this->mNoPriorityProcessObjectList.count() - 1);
			}
		}
	}
	else
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log("NoPriorityList::addNoPriorityObject, failed", LogTypeId::eLogNoPriorityListCheck);
		}
	}
}

void NoPriorityList::removeNoPriorityObject(INoOrPriorityObject* noPriorityObject)
{
	if (nullptr != noPriorityObject)
	{
		if (this->contains(noPriorityObject))
		{
			if (this->mIsSpeedUpFind)
			{
				this->_effectiveRemove(noPriorityObject);
			}
			else
			{
				int index = this->getIndexByNoPriorityObject(noPriorityObject);

				if (-1 != index)
				{
					this->mNoPriorityProcessObjectList.removeAt(index);
				}
			}
		}
	}
	else
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log("NoPriorityList::addNoPriorityObject, failed", LogTypeId::eLogNoPriorityListCheck);
		}
	}
}

void NoPriorityList::addNoOrPriorityObject(INoOrPriorityObject* noPriorityObject, float priority)
{
	this->addNoPriorityObject(noPriorityObject);
}

void NoPriorityList::removeNoOrPriorityObject(INoOrPriorityObject* noPriorityObject)
{
	this->removeNoPriorityObject(noPriorityObject);
}

// 快速移除元素
bool NoPriorityList::_effectiveRemove(INoOrPriorityObject* item)
{
	bool ret = false;

	if (this->mDic.containsKey(item))
	{
		ret = true;

		int index = this->mDic[item];
		this->mDic.remove(item);

		if (index == this->mNoPriorityProcessObjectList.count() - 1)    // 如果是最后一个元素，直接移除
		{
			this->mNoPriorityProcessObjectList.removeAt(index);
		}
		else
		{
			this->mNoPriorityProcessObjectList.set(index, this->mNoPriorityProcessObjectList.get(this->mNoPriorityProcessObjectList.count() - 1));
			this->mNoPriorityProcessObjectList.removeAt(this->mNoPriorityProcessObjectList.count() - 1);
			this->mDic.add(this->mNoPriorityProcessObjectList.get(index), index);
		}
	}

	return ret;
}

void NoPriorityList::_updateIndex(int index)
{
	int listLen = this->mNoPriorityProcessObjectList.count();

	while (index < listLen)
	{
		this->mDic.add(this->mNoPriorityProcessObjectList.get(index), index);

		++index;
	}
}

MY_END_NAMESPACE