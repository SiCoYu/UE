MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

--[[
 * @brief 缓存需要的数据，更容易控制需要缓存多少个，以及各种统计信息，但是申请一个 Item 需要一次 RemoveAt 和 Add，而比仅仅使用一个列表多了一次 add
]]

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "IndexData";
GlobalNS[M.clsName] = M;

function M:ctor()
	self.mTotalNum = 32;
	self.mInitNum = 32;

	self.mItemArray = new IndexItemBase[this.mInitNum];

	self.mFreeIndexList = new MList<int>();
	self.mFreeIndexList.setIsSpeedUpFind(true);
	self.mFreeIndexList.setIsOpKeepSort(false);

	self.mActiveIndexList = new MList<int>();
	self.mActiveIndexList.setIsSpeedUpFind(true);
	self.mActiveIndexList.setIsOpKeepSort(true);

	local index = 0;
	local listLen = self.mInitNum;

	while(index < listLen) do
		self.mFreeIndexList.add(index);

		index += 1;
	end
end

function M:init()
	
end

function M:dispose()
{
	if (null != this.mFreeIndexList)
	{
		this.mFreeIndexList.dispose();
		this.mFreeIndexList = null;
	}
	if (null != this.mActiveIndexList)
	{
		this.mActiveIndexList.dispose();
		this.mActiveIndexList = null;
	}
	if (null != this.mActiveIndexList)
	{
		this.mActiveIndexList.dispose();
		this.mActiveIndexList = null;
	}

	if (null != this.mItemArray)
	{
		int index = 0;
		int listLen = this.mItemArray.Length;

		while(index < listLen)
		{
			if (null != this.mItemArray[index])
			{
				this.mItemArray[index].dispose();
				this.mItemArray[index] = null;
			}

			index += 1;
		}

		this.mItemArray = null;
	}
}

-- 只支持初始化的时候设置
function M:setTotalNum(int value)
{
	this.mTotalNum = value;
}

function M:newItem()
{
	return null;
}

function M:newFreeItem()
{
	int freeIndex = -1;

	// 如果没有 free 数据
	if(this.mFreeIndexList.count() == 0)
	{
		int expandNum = 0;

		// 大于 0 说明有限制
		if (this.mTotalNum > 0)
		{
			// 如果还没有增大到最大限制
			if (this.mInitNum < this.mTotalNum)
			{
				if (2 * this.mInitNum <= this.mTotalNum)
				{
					expandNum = 2 * this.mInitNum;
				}
				else
				{
					expandNum = this.mTotalNum;
				}
			}
			else
			{
				throw new System.Exception("aaa");
			}
		}
		else
		{
			expandNum = 2 * this.mInitNum;
		}

		// 重新生成扩大的数组
		IndexItemBase[] tmpItemArray = this.mItemArray;
		this.mItemArray = new IndexItemBase[expandNum];

		// 将原始数据拷贝到扩大的数组中
		int index = 0;
		int listLen = tmpItemArray.Length;

		while(index < listLen)
		{
			this.mItemArray[index] = tmpItemArray[index];
			index += 1;
		}

		// free 添加新元素
		index = tmpItemArray.Length;
		listLen = this.mItemArray.Length;

		while (index < listLen)
		{
			this.mFreeIndexList.add(index);
			index += 1;
		}

		this.mInitNum = expandNum;
	}

	// 获取 free 元素索引
	freeIndex = this.mFreeIndexList.get(0);
	this.mFreeIndexList.RemoveAt(0);        // 申请需要一次 RemoveAt
	this.mActiveIndexList.add(freeIndex);   // 申请需要一次 add

	// 创建 free 元素
	if (null == this.mItemArray[freeIndex])
	{
		this.mItemArray[freeIndex] = this.newItem();
		this.mItemArray[freeIndex].setIndex(freeIndex);
	}

	return this.mItemArray[freeIndex];
}

public void deleteFreeItem(IndexItemBase item)
{
	if(-1 != item.getIndex())
	{
		this.mFreeIndexList.add(item.getIndex());
	}
}

return M;