MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

--[[
	@brief 基本缓冲对象
]]

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "BufferObjectBase";
GlobalNS[M.clsName] = M;

function M:ctor()
	self.mIsUsePool = false;
	self:onGetFromPool();
end

function M:init()
	self:onInit();
end

function M:onInit()

end

function M:onGetFromPool()

end

function M:onPutInPool()

end

function M:dispose()
	self:onPutInPool();
	self:onDestroy();
end

function M:destroy()
	self:onDestroy();
end

function M:onDestroy()

end

function M:isUsePool()
	return self.mIsUsePool;
end

function M:setIsUsePool(value)
	self.mIsUsePool = value;
end

function M:putInPool()
	self:onPutInPool();
end

function M:getFromPool()
	self:onGetFromPool();
end

return M;