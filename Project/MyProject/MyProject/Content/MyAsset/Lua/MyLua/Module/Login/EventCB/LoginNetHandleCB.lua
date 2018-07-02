MLoader("MyLua.Libs.Network.CmdDispatch.NetModuleDispatchHandle");
MLoader("MyLua.Module.Login.LoginNetHandle.LoginCmdHandle");

local M = GlobalNS.Class(GlobalNS.NetModuleDispatchHandle);
M.clsName = "LoginNetHandleCB";
GlobalNS[M.clsName] = M;

function M:ctor()
    local cmdHandle = GlobalNS.new(GlobalNS.LoginCmdHandle);
    self:addCmdHandle(LoginResponse, cmdHandle, cmdHandle.handleMsg);
end

function M:dtor()

end

return M;