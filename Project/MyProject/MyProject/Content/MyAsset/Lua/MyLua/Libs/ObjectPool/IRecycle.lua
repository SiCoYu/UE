MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "IRecycle";
GlobalNS[M.clsName] = M;

function M:putInPool()       -- 放入缓冲
	
end

function M:getFromPool()     -- 从缓冲池取出来
	
end

function M:dispose()         -- 释放资源
	
end

function M:setIsUsePool(bool value)
	
end

function M:isUsePool()
	
end

return M;