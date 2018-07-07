MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

MLoader("MyLua.Libs.DataStruct.MDictionary");
MLoader("MyLua.Libs.DataStruct.MList");

--[[
 * @brief 有 Id 的缓存池
]]

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "IdPoolSys";
GlobalNS[M.clsName] = M;

function M:ctor()
	self.mId2PoolDic = GlobalNS.new(GlobalNS.MDictionary);
	self.mTmpList = nil;
end

function M:init()

end

function M:dispose()
	self.releaseAllObject();
end

function M:getObject(id)
	local ret = nil;

	if (self.mId2PoolDic:containsKey(id)) then
		self.mTmpList = self.mId2PoolDic:value(id);

		if (self.mTmpList:count() > 0) then
			ret = self.mTmpList:get(0);
			self.mTmpList.RemoveAt(0);
			self.mTmpList = nil;
		end
	end

	return ret;
end

function M:returnObject(id, obj)
	if(not self.mId2PoolDic:containsKey(id)) then
		self.mId2PoolDic:set(id, GlobalNS.new(GlobalNS.MList));
		self.mId2PoolDic:get(id):setIsSpeedUpFind(true);
		self.mId2PoolDic:get(id):setIsOpKeepSort(false);
	end

	self.mTmpList = self.mId2PoolDic:get(id);

	if (not self.mTmpList.Contains(obj)) then
		self.mTmpList:add(obj);
	end

	self.mTmpList = nil;
end

function M:releaseAllObject()
	local resUniqueIdList = GlobalNS.new(GlobalNS.MList);

	for key_, value_ in pairs(self.mId2PoolDic) do
		resUniqueIdList:add(key_);
	end

	local index = 0;
	local listLen = resUniqueIdList:length();

	while (index < listLen) do
		self:releaseAllObjectById(resUniqueIdList:get(idx));
		index = index + 1;
	end

	resUniqueIdList:clear();
	resUniqueIdList = nil;

	self.mId2PoolDic:clear();
end

function M:releaseAllObjectById(id)
	if (self.mId2PoolDic:containsKey(id)) then
		local list = self.mId2PoolDic:value(id);
		local item = nil;

		local index = 0;
		local listLen = list:count();

		while(index < listLen) do
			item = list:get(index);
			item:dispose();

			index = index + 1;
		end

		self.mId2PoolDic:remove(id);
	end
end

return M;