MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

MLoader("MyLua.Libs.ObjectPool.IRecycle");

local M = GlobalNS.Class(GlobalNS.IRecycle);
M.clsName = "IStrIdRecycle";
GlobalNS[M.clsName] = M;

function M:getBufferUniqueId()

end

return M: