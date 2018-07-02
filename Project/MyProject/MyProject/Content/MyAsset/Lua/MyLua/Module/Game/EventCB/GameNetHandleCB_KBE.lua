MLoader("MyLua.Libs.Network.CmdDispatch.NetModuleDispatchHandle");
MLoader("MyLua.Module.Game.GameNetHandle.GameTestCmdHandle");

local M = GlobalNS.Class(GlobalNS.NetModuleDispatchHandle);
M.clsName = "GameNetHandleCB_KBE";
GlobalNS[M.clsName] = M;

function M:ctor()
	self.mGameEventHandle = GlobalNS.new(GlobalNS.GameEventHandle);
end

function M:dtor()

end

function M:init()
	self.mGameEventHandle:init();
end

return M;