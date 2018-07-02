MLoader("MyLua.Libs.Network.CmdDispatch.NetCmdDispatchHandle");

local M = GlobalNS.Class(GlobalNS.NetCmdDispatchHandle);
M.clsName = "TestCmdHandle";
GlobalNS[M.clsName] = M;

function M:ctor()
    self:addParamHandle(MSG_ReqTest, self, self.handleTest);
end

function M:dtor()
    
end

function M:handleTest(cmd)
    GlobalNS.CSSystemTest.onTestProtoBuf(cmd);
end

return M;