MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiSignPanel.SignPanelNS");
MLoader("MyLua.Ui.UiSignPanel.SignPanelData");
MLoader("MyLua.Ui.UiSignPanel.SignPanelCV");

--UI区
local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiOtherAwardPanel";
GlobalNS.SignPanelNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUiOtherAwardPanel;
	self.mData = GlobalNS.new(GlobalNS.SignPanelNS.SignPanelData);
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);
	
	self.mCloseBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mCloseBtn:addEventHandle(self, self.onCloseBtnClk, 0);

    self.mGetBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mGetBtn:addEventHandle(self, self.onGetBtnClk, 0);
end

function M:onReady()
    M.super.onReady(self);
	self.mCloseBtn:setSelfGo(GlobalNS.UtilApi.TransFindChildByPObjAndPath(self.mGuiWin, "Close_BtnTouch"));

    self.Award = GlobalNS.UtilApi.TransFindChildByPObjAndPath(self.mGuiWin, "Award");
    self.AwardName = GlobalNS.UtilApi.getComByPath(self.Award, "Name", "Text");

    self.mGetBtn:setSelfGo(GlobalNS.UtilApi.TransFindChildByPObjAndPath(self.mGuiWin, "Get_BtnTouch"));

    self:UpdateUIData(nil);
end

function M:onShow()
    M.super.onShow(self);
end

function M:onHide()
    M.super.onHide(self);
end

function M:onExit()
    M.super.onExit(self);
end

function M:onCloseBtnClk()
	self:exit();
end

function M:onGetBtnClk()
	GCtx.mLogSys:log("领取奖励", GlobalNS.LogTypeId.eLogCommon);
end

function M:UpdateUIData(args)
    self.AwardName.text = "神杖 x" .. GCtx.mSignData.rangeDay;
end

return M;