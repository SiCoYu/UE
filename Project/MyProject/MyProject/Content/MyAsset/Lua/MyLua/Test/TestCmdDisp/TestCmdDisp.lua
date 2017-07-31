MLoader("MyLua.Libs.Network.CmdDisp.NetModuleDispHandle");
MLoader("MyLua.Module.Game.GameNetHandle.GameTestCmdHandle");

MLoader("MyLua.Test.TestCmdDisp.TestNetHandleCB");

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "TestCmdDisp";
GlobalNS[M.clsName] = M;

function M:ctor()
    self:init();
end

function M:dtor()

end

function M:init()
	local testNetHandleCB = GlobalNS.new(GlobalNS.TestNetHandleCB);
    GCtx.mNetCmdNotify:addOneDisp(testNetHandleCB);    -- 设置网络模块处理
end

function M:run()
	
end

return M;