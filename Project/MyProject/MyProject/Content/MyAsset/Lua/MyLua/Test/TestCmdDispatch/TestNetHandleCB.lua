MLoader("MyLua.Libs.Network.CmdDispatch.NetModuleDispatchHandle");
MLoader("MyLua.Test.TestCmdDispatch.TestCmdHandle");

local M = GlobalNS.Class(GlobalNS.NetModuleDispatchHandle);
M.clsName = "TestNetHandleCB";
GlobalNS[M.clsName] = M;

function M:ctor()
    local cmdHandle = GlobalNS.new(GlobalNS.TestCmdHandle);
    self:addCmdHandle(MSG_ReqTest, cmdHandle, cmdHandle.call);
end

function M:dtor()

end

return M;