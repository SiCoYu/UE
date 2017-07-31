MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");

--[[
    处理 CS 到 Lua 的全局事件
]]
local M = GlobalNS.StaticClass();
local this = M;
M.clsName = "GlobalEventCmdTest";
GlobalNS[M.clsName] = M;

-- 测试发送消息
function M.testSendMsg()
	local form = GCtx.mUiMgr:getForm(GlobalNS.UIFormId.eUITest);
	if(form ~= nil) then
		form:testSendMsg();
	end
end

return M;