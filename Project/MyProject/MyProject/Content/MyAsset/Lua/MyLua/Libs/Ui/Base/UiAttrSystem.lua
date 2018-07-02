MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");

--[[
local M = GlobalNS.StaticClass();
M.clsName = "PreFormModeWhenOpen";
GlobalNS[M.clsName] = M;

function M.ctor()
	M.eNONE = 0;
	M.eHIDE = 1;
	M.eCLOSE = 2;
end

M.ctor();

-------------------------------------
M = GlobalNS.StaticClass();
M.clsName = "PreFormModeWhenClose";
GlobalNS[M.clsName] = M;

function M.ctor()
	M.eNONE = 0;
	M.eSHOW = 1;
end

M.ctor();
]]

-------------------------------------
local M = GlobalNS.StaticClass();
M.clsName = "UiAttrSystem";
GlobalNS[M.clsName] = M;

function M.ctor()
    
end

--如果一个文件中重复定义了多个 M ，如果不是在 ctor 调用
function M.init()
	M[GlobalNS.UiFormId.eUiTest] = {
            mWidgetPath = "UI/UiTest/UiTest.prefab",
            mLuaScriptPath = "MyLua.Ui.UiTest.UiTest",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	M[GlobalNS.UiFormId.eUiStartGame] = {
            mWidgetPath = "UI/UiStartGame/UiStartGame.prefab",
            mLuaScriptPath = "MyLua.Ui.UiStartGame.UiStartGame",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
    M[GlobalNS.UiFormId.eUiRankListPanel] = {
            mWidgetPath = "UI/UiRankListPanel/UiRankListPanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiRankListPanel.UiRankListPanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
    M[GlobalNS.UiFormId.eUiRelivePanel] = {
            mWidgetPath = "UI/UiRelivePanel/UiRelivePanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiRelivePanel.UiRelivePanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	M[GlobalNS.UiFormId.eUiPlayerDataPanel] = {
            mWidgetPath = "UI/UiPlayerDataPanel/UiPlayerDataPanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiPlayerDataPanel.UiPlayerDataPanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	M[GlobalNS.UiFormId.eUiOptionPanel] = {
            mWidgetPath = "UI/UiOptionPanel/UiOptionPanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiOptionPanel.UiOptionPanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	M[GlobalNS.UiFormId.eUiTopXRankPanel] = {
            mWidgetPath = "UI/UiTopXRankPanel/UiTopXRankPanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiTopXRankPanel.UiTopXRankPanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	M[GlobalNS.UiFormId.eUiConsoleDlg] = {
            mWidgetPath = "UI/UiConsoleDlg/UiConsoleDlg.prefab",
            mLuaScriptPath = "MyLua.Ui.UiConsoleDlg.UiConsoleDlg",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	M[GlobalNS.UiFormId.eUiShop_SkinPanel] = {
            mWidgetPath = "UI/UiPack/UiPack.prefab",
            mLuaScriptPath = "MyLua.Ui.UiPack.UiPack",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	M[GlobalNS.UiFormId.eUiShop_SkinPanel] = {
            mWidgetPath = "UI/UiShop_SkinPanel/UiShop_SkinPanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiShop_SkinPanel.UiShop_SkinPanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	M[GlobalNS.UiFormId.eUiSettingsPanel] = {
            mWidgetPath = "UI/UiSettingsPanel/UiSettingsPanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiSettingsPanel.UiSettingsPanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	M[GlobalNS.UiFormId.eUiMessagePanel] = {
            mWidgetPath = "UI/UiMessagePanel/UiMessagePanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiMessagePanel.UiMessagePanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	M[GlobalNS.UiFormId.eUiSignPanel] = {
            mWidgetPath = "UI/UiSignPanel/UiSignPanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiSignPanel.UiSignPanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
    M[GlobalNS.UiFormId.eUiDayAwardPanel] = {
            mWidgetPath = "UI/UiSignPanel/UiDayAwardPanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiSignPanel.UiDayAwardPanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
    M[GlobalNS.UiFormId.eUiOtherAwardPanel] = {
            mWidgetPath = "UI/UiSignPanel/UiOtherAwardPanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiSignPanel.UiOtherAwardPanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	M[GlobalNS.UiFormId.eUiAccountPanel] = {
            mWidgetPath = "UI/UiAccountPanel/UiAccountPanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiAccountPanel.UiAccountPanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
    M[GlobalNS.UiFormId.eUiAccountAvatarPanel] = {
            mWidgetPath = "UI/UiAccountPanel/UiAccountAvatarPanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiAccountPanel.UiAccountAvatarPanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	M[GlobalNS.UiFormId.eUiBugReportPanel] = {
            mWidgetPath = "UI/UiBugReportPanel/UiBugReportPanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiBugReportPanel.UiBugReportPanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	M[GlobalNS.UiFormId.eUiEmoticonPanel] = {
            mWidgetPath = "UI/UiEmoticonPanel/UiEmoticonPanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UiEmoticonPanel.UiEmoticonPanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	M[GlobalNS.UiFormId.eUiShareSelfPanel] = {
            mWidgetPath = "UI/UIShareSelfPanel/UIShareSelfPanel.prefab",
            mLuaScriptPath = "MyLua.Ui.UIShareSelfPanel.UIShareSelfPanel",
			mLuaScriptTableName = "GlobalNS.UILua",
			mCanvasId = GlobalNS.UiCanvasId.eUIFirstCanvas,
			mLayerId = GlobalNS.UiLayerId.eUISecondLayer,
			mPreFormModeWhenOpen = GlobalNS.PreFormModeWhenOpen.eNONE,
			mPreFormModeWhenClose = GlobalNS.PreFormModeWhenClose.eNONE,
        };
	--[[替换占位符(勿删)--]]
end

M.ctor();

return M;