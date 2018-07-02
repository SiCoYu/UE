MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

MLoader("MyLua.Libs.ObjectPool.IdPoolSys");

local M = GlobalNS.Class(GlobalNS.IdPoolSys);
M.clsName = "StrIdPoolSys";
GlobalNS[M.clsName] = M;

function M:ctor()
	
end

function M:dtor()
	
end

return M;