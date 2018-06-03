#include "MyProject.h"
#include "PriorityList.h"
#include "MacroDef.h"
#include "Ctx.h"
#include "LogSys.h"
#include "LogTypeId.h"
#include "PrioritySort.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "PriorityProcessObject.h"

MY_BEGIN_NAMESPACE(MyNS)

PriorityList::PriorityList()
{
	//this->mPriorityProcessObjectList = new MList<PriorityProcessObject>();
	this->mPrioritySort = PrioritySort::ePS_Great;
	this->mIsSpeedUpFind = false;
	this->mIsOpKeepSort = false;
}

void PriorityList::init()
{

}

void PriorityList::dispose()
{
	//if(nullptr != this->mPriorityProcessObjectList)
	//{
		this->mPriorityProcessObjectList.dispose();
		//this->mPriorityProcessObjectList = nullptr;
	//}
	//if(nullptr != this->mDic)
	//{
		this->mDic.dispose();
		//this->mDic = nullptr;
	//}
}

void PriorityList::setIsSpeedUpFind(bool value)
{
	this->mIsSpeedUpFind = value;

	//if (this->mIsSpeedUpFind)
	//{
	//	this->mDic = new MDictionary<INoOrPriorityObject, int>();
	//}
}

void PriorityList::setIsOpKeepSort(bool value)
{
	this->mIsOpKeepSort = value;
}

void PriorityList::clear()
{
	int index = 0;
	int listLen = this->count();

	while(index < listLen)
	{
		//NumIdBufferObjectFactory.deleteObject(this->mPriorityProcessObjectList.get(index));
		MY_DELETE this->mPriorityProcessObjectList.get(index);
		this->mPriorityProcessObjectList.set(index, nullptr);
		index += 1;
	}

	this->mPriorityProcessObjectList.clear();

	if(this->mIsSpeedUpFind)
	{
		this->mDic.clear();
	}
}

int PriorityList::count()
{
	return this->mPriorityProcessObjectList.count();
}

INoOrPriorityObject* PriorityList::get(int index)
{
	INoOrPriorityObject* ret = nullptr;

	if(index < this->count())
	{
		ret = this->mPriorityProcessObjectList.get(index)->mPriorityObject;
	}

	return ret;
}

float PriorityList::getPriority(int index)
{
	float ret = 0;

	if (index < this->count())
	{
		ret = this->mPriorityProcessObjectList.get(index)->mPriority;
	}

	return ret;
}

bool PriorityList::contains(INoOrPriorityObject* item)
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
			int listLen = this->mPriorityProcessObjectList.count();

			while (index < listLen)
			{
				if (item == this->mPriorityProcessObjectList.get(index)->mPriorityObject)
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
			GLogSys->log("PriorityList::Contains, failed", LogTypeId::eLogPriorityListCheck);
		}
	}

	return ret;
}

void PriorityList::removeAt(int index)
{
	PriorityProcessObject* priorityProcessObject = nullptr;
	priorityProcessObject = this->mPriorityProcessObjectList.get(index);

	if (this->mIsSpeedUpFind)
	{
		this->_effectiveRemove(this->mPriorityProcessObjectList.get(index)->mPriorityObject);
	}
	else
	{
		this->mPriorityProcessObjectList.removeAt(index);
	}

	if (nullptr != priorityProcessObject)
	{
		//NumIdBufferObjectFactory.deleteObject(priorityProcessObject);
		MY_DELETE priorityProcessObject;
		priorityProcessObject = nullptr;
	}
}

int PriorityList::getIndexByPriority(float priority)
{
	int retIndex = -1;

	int index = 0;
	int listLen = this->mPriorityProcessObjectList.count();

	while (index < listLen)
	{
		if (PrioritySort::ePS_Less == this->mPrioritySort)
		{
			if (this->mPriorityProcessObjectList.get(index)->mPriority >= priority)
			{
				retIndex = index;
				break;
			}
		}
		else if (PrioritySort::ePS_Great == this->mPrioritySort)
		{
			if (this->mPriorityProcessObjectList.get(index)->mPriority <= priority)
			{
				retIndex = index;
				break;
			}
		}

		++index;
	}

	return retIndex;
}

int PriorityList::getIndexByPriorityObject(INoOrPriorityObject* priorityObject)
{
	int retIndex = -1;

	int index = 0;
	int listLen = this->mPriorityProcessObjectList.count();

	while (index < listLen)
	{
		if (this->mPriorityProcessObjectList.get(index)->mPriorityObject == priorityObject)
		{
			retIndex = index;
			break;
		}

		++index;
	}

	return retIndex;
}

int PriorityList::getIndexByNoOrPriorityObject(INoOrPriorityObject* priorityObject)
{
	return this->getIndexByPriorityObject(priorityObject);
}

void PriorityList::addPriorityObject(INoOrPriorityObject* priorityObject, float priority)
{
	if (nullptr != priorityObject)
	{
		if (!this->contains(priorityObject))
		{
			PriorityProcessObject* priorityProcessObject = nullptr;
			priorityProcessObject = MY_NEW PriorityProcessObject();
			//priorityProcessObject = NumIdBufferObjectFactory.newObject<PriorityProcessObject>(BufferType.eBT_PriorityProcessObject, true);

			priorityProcessObject->mPriorityObject = priorityObject;
			priorityProcessObject->mPriority = priority;

			if (!this->mIsOpKeepSort)
			{
				this->mPriorityProcessObjectList.add(priorityProcessObject);

				if (this->mIsSpeedUpFind)
				{
					this->mDic.add(priorityObject, this->mPriorityProcessObjectList.count() - 1);
				}
			}
			else
			{
				int index = this->getIndexByPriority(priority);

				if (-1 == index)
				{
					this->mPriorityProcessObjectList.add(priorityProcessObject);

					if (this->mIsSpeedUpFind)
					{
						this->mDic.add(priorityObject, this->mPriorityProcessObjectList.count() - 1);
					}
				}
				else
				{
					this->mPriorityProcessObjectList.insert(index, priorityProcessObject);

					if (this->mIsSpeedUpFind)
					{
						this->mDic.add(priorityObject, index);
						this->_updateIndex(index + 1);
					}
				}
			}
		}
	}
	else
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log("PriorityList::addPriorityObject, failed", LogTypeId::eLogPriorityListCheck);
		}
	}
}

void PriorityList::removePriorityObject(INoOrPriorityObject* priorityObject)
{
	if (this->contains(priorityObject))
	{
		if (this->mIsSpeedUpFind)
		{
			this->_effectiveRemove(priorityObject);
		}
		else
		{
			int index = this->getIndexByPriorityObject(priorityObject);

			if(-1 != index)
			{
				this->mPriorityProcessObjectList.removeAt(index);
			}
		}
	}
}

void PriorityList::addNoOrPriorityObject(INoOrPriorityObject* noPriorityObject, float priority = 0.0f)
{
	this->addPriorityObject(noPriorityObject, priority);
}

void PriorityList::removeNoOrPriorityObject(INoOrPriorityObject* noPriorityObject)
{
	this->removePriorityObject(noPriorityObject);
}

// 快速移除元素
bool PriorityList::_effectiveRemove(INoOrPriorityObject* item)
{
	bool ret = false;

	if (this->mDic.containsKey(item))
	{
		ret = true;

		int index = this->mDic.value(item);
		this->mDic.remove(item);

		if (index == this->mPriorityProcessObjectList.count() - 1)    // 如果是最后一个元素，直接移除
		{
			this->mPriorityProcessObjectList.removeAt(index);
		}
		else
		{
			// 这样移除会使优先级顺序改变
			if (!this->mIsOpKeepSort)
			{
				this->mPriorityProcessObjectList.set(index, this->mPriorityProcessObjectList.get(this->mPriorityProcessObjectList.count() - 1));
				this->mPriorityProcessObjectList.removeAt(this->mPriorityProcessObjectList.count() - 1);
				this->mDic.add(this->mPriorityProcessObjectList.get(index)->mPriorityObject, index);
			}
			else
			{
				this->mPriorityProcessObjectList.removeAt(index);
				this->_updateIndex(index);
			}
		}
	}

	return ret;
}

void PriorityList::_updateIndex(int index)
{
	int listLen = this->mPriorityProcessObjectList.count();

	while (index < listLen)
	{
		this->mDic.add(this->mPriorityProcessObjectList.get(index)->mPriorityObject, index);

		++index;
	}
}

MY_END_NAMESPACE