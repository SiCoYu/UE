MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");

local M = GlobalNS.StaticClass();
M.clsName = "UiCanvasId";
GlobalNS[M.clsName] = M;

function M.ctor()
	M.eUIFirstCanvas = 0;
	M.eUISecondCanvas = 1;
end

M.ctor();

return M;