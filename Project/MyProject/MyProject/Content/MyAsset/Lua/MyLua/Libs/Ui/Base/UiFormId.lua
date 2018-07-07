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
	this.eUiTest = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    --10001
	this.eUiStartGame = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    --10002 依次类推... ...
    this.eUiRankListPanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiRelivePanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiPlayerDataPanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiOptionPanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiTopXRankPanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiConsoleDlg = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
	this.eUiShop_SkinPanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
	this.eUiPack = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiSettingsPanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiMessagePanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiSignPanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiDayAwardPanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiOtherAwardPanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiAccountPanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiAccountAvatarPanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiBugReportPanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiEmoticonPanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    this.eUiShareSelfPanel = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
    --[[替换占位符(勿删)--]]
	this.eUiCount = Ctx.mUiMgr.mUniqueNumIdGen:genNewId();
end

--静态表直接构造就行了，不会使用 new 操作符
M.ctor();

return M;