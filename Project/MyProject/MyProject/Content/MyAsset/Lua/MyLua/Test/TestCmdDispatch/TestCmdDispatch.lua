MLoader("MyLua.Libs.Network.CmdDispatch.NetModuleDispatchHandle");
MLoader("MyLua.Module.Game.GameNetHandle.GameTestCmdHandle");

MLoader("MyLua.Test.TestCmdDispatch.TestNetHandleCB");

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "TestCmdDispatch";
GlobalNS[M.clsName] = M;

function M:ctor()
    self:init();
end

function M:dtor()

end

function M:init()
	local testNetHandleCB = GlobalNS.new(GlobalNS.TestNetHandleCB);
    Ctx.mNetCmdNotify:addOneDispatch(testNetHandleCB);    -- 设置网络模块处理
end

function M:run()
	
end

return M;