MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");

-- 功能模块 NS
local M = GlobalNS.StaticClass();
local this = M;
M.clsName = "EmoticonPanelNS";
GlobalNS[M.clsName] = M;

return M;