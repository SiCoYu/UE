MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

MLoader("MyLua.Libs.DataStruct.MList");
MLoader("MyLua.Libs.DataStruct.MDictionary");

-- 优先级队列
local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "NoPriorityList";
GlobalNS[M.clsName] = M;

function M:ctor()
	self.mNoPriorityProcessObjectList = GlobalNS.new(GlobalNS.MList);
	self.mIsSpeedUpFind = false;
end

function M:dtor()

end

function M:setIsSpeedUpFind(value)
	self.mIsSpeedUpFind = value;

	if (self.mIsSpeedUpFind) then
		self.mDic = GlobalNS.new(GlobalNS.MDictionary);
	end
end

function M:setIsOpKeepSort(value)

end

function M:clear()
	self.mNoPriorityProcessObjectList:clear();

	if(self.mIsSpeedUpFind) then
		self.mDic:clear();
	end
end

function M:count()
	return self.mNoPriorityProcessObjectList:count();
end

function M:get(index)
	local ret = nil;

	if(index < self:count()) then
		ret = self.mNoPriorityProcessObjectList:get(index);
	end

	return ret;
end

function M:contains(item)
	local ret = false;

	if (nil ~= item) then
		if (self.mIsSpeedUpFind) then
			ret = self.mDic:containsKey(item);
		else
			local index = 0;
			local listLen = self.mNoPriorityProcessObjectList:count();

			while (index < listLen) do
				if (item == self.mNoPriorityProcessObjectList:get(index)) then
					ret = true;
					break;
				end

				index = index + 1;
			end
		end
	else
		if (MacroDef.ENABLE_LOG) then
			Ctx.mLogSys:log("NoPriorityList::Contains, failed", GlobalNS.LogTypeId.eLogNoPriorityListCheck);
		end
	end

	return ret;
end

function M:removeAt(index)
	if (self.mIsSpeedUpFind) then
		self:effectiveRemove(self.mNoPriorityProcessObjectList:at(index));
	else
		self.mNoPriorityProcessObjectList:removeAt(index);
	end
end

function M:getIndexByNoPriorityObject(priorityObject)
	local retIndex = -1;

	local index = 0;
	local listLen = self.mNoPriorityProcessObjectList:count();

	while (index < listLen) do
		if (self.mNoPriorityProcessObjectList:get(index) == priorityObject) then
			retIndex = index;
			break;
		end

		index = index + 1;
	end

	return retIndex;
end

function M:getIndexByNoOrPriorityObject(priorityObject)
	return self:getIndexByNoPriorityObject(priorityObject);
end

function M:addNoPriorityObject(noPriorityObject)
	if (nil ~= noPriorityObject) then
		if (not self:contains(noPriorityObject)) then
			self.mNoPriorityProcessObjectList:add(noPriorityObject);

			if (self.mIsSpeedUpFind) then
				self.mDic:add(noPriorityObject, self.mNoPriorityProcessObjectList:count() - 1);
			end
		end
	else
		if (MacroDef.ENABLE_LOG) then
			Ctx.mLogSys:log("NoPriorityList::addNoPriorityObject, failed", GlobalNS.LogTypeId.eLogNoPriorityListCheck);
		end
	end
end

function M:removeNoPriorityObject(noPriorityObject)
	if (nil ~= noPriorityObject) then
		if (self:contains(noPriorityObject)) then
			if (self.mIsSpeedUpFind) then
				self:effectiveRemove(noPriorityObject);
			else
				local index = self:getIndexByNoPriorityObject(noPriorityObject);

				if (-1 ~= index) then
					self.mNoPriorityProcessObjectList:removeAt(index);
				end
			end
		end
	else
		if (MacroDef.ENABLE_LOG) then
			Ctx.mLogSys:log("NoPriorityList::addNoPriorityObject, failed", GlobalNS.LogTypeId.eLogNoPriorityListCheck);
		end
	end
end

function M:addNoOrPriorityObject(noPriorityObject, priority)
	self:addNoPriorityObject(noPriorityObject);
end

function M:removeNoOrPriorityObject(noPriorityObject)
	self:removeNoPriorityObject(noPriorityObject);
end

-- 快速移除元素
function M:effectiveRemove(item)
	local ret = false;

	if (self.mDic:containsKey(item)) then
		ret = true;

		local idx = self.mDic:value(item);
		self.mDic:remove(item);

		if (idx == self.mNoPriorityProcessObjectList:count() - 1) then   -- 如果是最后一个元素，直接移除
			self.mNoPriorityProcessObjectList:removeAt(idx);
		else
			self.mNoPriorityProcessObjectList:set(idx, self.mNoPriorityProcessObjectList:get(self.mNoPriorityProcessObjectList:count() - 1));
			self.mNoPriorityProcessObjectList:removeAt(self.mNoPriorityProcessObjectList:count() - 1);
			self.mDic:add(self.mNoPriorityProcessObjectList:get(idx), idx);
		end
	end

	return ret;
end

function M:updateIndex(idx)
	local listLen = self.mNoPriorityProcessObjectList:count();

	while (idx < listLen) do
		self.mDic:add(self.mNoPriorityProcessObjectList:get(idx), idx);

		idx = idx + 1;
	end
end

return M;