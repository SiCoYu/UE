MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");

local M = GlobalNS.StaticClass();
local this = M;
M.clsName = "UiFormId";
GlobalNS[M.clsName] = M;

function M.ctor()
	
end

function M.init()
    --10000
	this.eUiTest = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    --10001
	this.eUiStartGame = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    --10002 依次类推... ...
    this.eUiRankListPanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiRelivePanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiPlayerDataPanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiOptionPanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiTopXRankPanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiConsoleDlg = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
	this.eUiShop_SkinPanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
	this.eUiPack = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiSettingsPanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiMessagePanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiSignPanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiDayAwardPanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiOtherAwardPanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiAccountPanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiAccountAvatarPanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiBugReportPanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiEmoticonPanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiShareSelfPanel = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
    --[[替换占位符(勿删)--]]
	this.eUiCount = GCtx.mUiMgr.mUniqueNumIdGen:genNewId();
end

--静态表直接构造就行了，不会使用 new 操作符
M.ctor();

return M;