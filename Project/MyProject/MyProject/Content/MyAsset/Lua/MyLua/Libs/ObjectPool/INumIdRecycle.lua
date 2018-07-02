MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

MLoader("MyLua.Libs.ObjectPool.IRecycle");

local M = GlobalNS.Class(GlobalNS.IRecycle);
M.clsName = "INumIdRecycle";
GlobalNS[M.clsName] = M;

function M:getBufferType()
	
end

return M;