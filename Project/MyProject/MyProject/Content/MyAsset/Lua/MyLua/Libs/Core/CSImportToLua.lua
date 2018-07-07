MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");

-- 使用 CS 反射绑定 CS 到 lua
local M = GlobalNS.StaticClass();
M.clsName = "CSImportToLua";
GlobalNS[M.clsName] = M;

function M:ctor()

end

M.UtilEngineWrap = luanet.import_type("SDK.Lib.UtilEngineWrap");        -- 参数一定不能空

M.ctor();

return M;