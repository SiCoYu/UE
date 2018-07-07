MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");

local M = GlobalNS.StaticClass();
M.clsName = "UiLayerId";
GlobalNS[M.clsName] = M;

function M.ctor()
	M.eUIBtmLayer = 0;
	M.eUIFirstLayer = 1;
	M.eUISecondLayer = 2;
	M.eUIThirdLayer = 3;
	M.eUIForthLayer = 4;
	M.eUITopLayer = 5;
end

M.ctor();

return M;