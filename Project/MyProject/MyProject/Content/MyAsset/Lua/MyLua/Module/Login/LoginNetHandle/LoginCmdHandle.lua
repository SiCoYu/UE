MLoader("MyLua.Libs.Network.CmdDispatch.NetCmdDispatchHandle");

local M = GlobalNS.Class(GlobalNS.NetCmdDispatchHandle);
M.clsName = "LoginCmdHandle";
GlobalNS[M.clsName] = M;

function M:ctor()
	self:addParamHandle(LoginResponse, self, self.handleLoginResponse);
end

function M:dtor()
    
end

function M:handleLoginResponse(cmd)
	Ctx.mLogSys:log(cmd.result, GlobalNS.LogTypeId.eLogCommon);
end

return M;