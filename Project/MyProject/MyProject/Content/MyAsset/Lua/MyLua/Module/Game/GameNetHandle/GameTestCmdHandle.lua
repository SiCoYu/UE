﻿MLoader("MyLua.Libs.Network.CmdDisp.NetCmdDispHandle");

local M = GlobalNS.Class(GlobalNS.NetCmdDispHandle);
M.clsName = "GameTestCmdHandle";
GlobalNS[M.clsName] = M;

function M:ctor()
    self:addParamHandle(MSG_ReqTest, self, self.handleTest);
	self:addParamHandle(LoginResponse, self, self.LoginResponse);
end

function M:dtor()
    
end

function M:handleTest(cmd)
    --GlobalNS.CSSystem.onTestProtoBuf(cmd);
end

function M:handleLoginResponse(cmd)
	GCtx.mLogSys:log(cmd.result, GlobalNS.LogTypeId.eLogCommon);
end

return M;