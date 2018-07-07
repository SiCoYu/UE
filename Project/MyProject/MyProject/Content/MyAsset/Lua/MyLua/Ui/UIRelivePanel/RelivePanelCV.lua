MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");

MLoader("MyLua.Ui.UiRelivePanel.RelivePanelNS");

local M = GlobalNS.StaticClass();
local this = M;
M.clsName = "RelivePanelPath";
GlobalNS.RelivePanelNS[M.clsName] = M;

function M.init()
	M.BtnRelive = "Relive_BtnTouch";
    M.BtnBackRoom = "BackRoom_BtnTouch";
end

M.init();

return M;