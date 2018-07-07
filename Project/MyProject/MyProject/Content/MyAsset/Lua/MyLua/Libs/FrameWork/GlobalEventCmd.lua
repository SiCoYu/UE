MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");

MLoader("MyLua.Test.TestMain");

if(MacroDef.UNIT_TEST) then
	MLoader("MyLua.Test.TestMain");
end

--[[
    处理 CS 到 Lua 的全局事件
]]
local M = GlobalNS.StaticClass();
local this = M;
M.clsName = "GlobalEventCmd";
GlobalNS[M.clsName] = M;

-- 接收消息
function M.onReceiveToLua(id, buffer)
    --Ctx.mLogSys:log("GlobalEventCmd::onReceiveToLua", GlobalNS.LogTypeId.eLogCommon);
    Ctx.mNetMgr:receiveCmd(id, buffer);
end

function M.onReceiveToLuaRpc(buffer, length)
    --Ctx.mLogSys:log("GlobalEventCmd::onReceiveToLuaRpc", GlobalNS.LogTypeId.eLogCommon);
    Ctx.mNetMgr:receiveCmdRpc(buffer, length);
end

-- 接收消息, KBE
function M.onReceiveToLua_KBE(msgName, param)
    --Ctx.mLogSys:log("GlobalEventCmd::onReceiveToLua_KBE", GlobalNS.LogTypeId.eLogCommon);
	Ctx.mNetCmdNotify_KBE:handleMsg(msgName, param);
end

-- 场景加载完成
function M.onSceneLoaded()
	this.onUnitTest();
end

function M.onUnitTest()
	if(MacroDef.UNIT_TEST) then
		pTestMain = GlobalNS.new(GlobalNS.TestMain);
		pTestMain:run();
	end
end

-- 主角加载完成
function M.onPlayerMainLoaded()
    --加载场景上的UI组件，主角加载完成后再加载UI，否则UI拿不到主角数据
    Ctx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiRankListPanel);
    Ctx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiRelivePanel);
    Ctx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiShop_SkinPanel);
    Ctx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiSettingsPanel);
    Ctx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiMessagePanel);
    Ctx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiSignPanel);
    Ctx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiDayAwardPanel);
    Ctx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiOtherAwardPanel);
    Ctx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiAccountPanel);
    Ctx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiAccountAvatarPanel);

    Ctx.mUiMgr:loadAndShow(GlobalNS.UiFormId.eUiPlayerDataPanel);
    Ctx.mUiMgr:loadAndShow(GlobalNS.UiFormId.eUiOptionPanel);
    Ctx.mUiMgr:loadAndShow(GlobalNS.UiFormId.eUiTopXRankPanel);
end

-- 帧循环
function M.onAdvance(delta, tickMode)
	--测试 tick
	--[[
	if(nil == M.mTickItemBase) then
		M.mTickItemBase = GlobalNS.new(GlobalNS.TickItemBase);
		M.mTickItemBase:addSelfTick(0);
	end
	]]
	
	Ctx.mProcessSys:advance(delta, tickMode);
end

function M.openForm(formId)
	Ctx.mUiMgr:loadAndShow(formId);
end

function M.exitForm(formId)
	Ctx.mUiMgr:exitForm(formId);
end

function M.requireFile(filePath)
	return MLoader(filePath);
end

--场景加载进度, progress: [0, 1]
function M.onSceneLoadProgress(progress)
	local form = Ctx.mUiMgr:getForm(GlobalNS.UiFormId.eUiStartGame);
	if(nil ~= form) then
		form:setProgress(progress);
	end
end

return M;