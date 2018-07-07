MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiMessagePanel.MessagePanelNS");
MLoader("MyLua.Ui.UiMessagePanel.MessagePanelData");
MLoader("MyLua.Ui.UiMessagePanel.MessagePanelCV");

--UI区
local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiMessagePanel";
GlobalNS.MessagePanelNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUiMessagePanel;
	self.mData = GlobalNS.new(GlobalNS.MessagePanelNS.MessagePanelData);
    self.mTimer = GlobalNS.new(GlobalNS.DaoJiShiTimer);
    self.mRollTime = 1;
    self.mInterval = 0.01; --滚动间隔
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);
	
	self.mOKBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mOKBtn:addEventHandle(self, self.onOKBtnClk, 0);
end

function M:onReady()
    M.super.onReady(self);
    self.popMessageDlg = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, "PopMessageDlg");
    self.popMessageText = GlobalNS.UtilEngineWrap.getComByPath(self.popMessageDlg, "MsgText", "InputField");
	self.mOKBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.popMessageDlg, "OK_BtnTouch"));

    self.rollMessageDlg = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, "RollMessageDlg");
    self.rollMessageTextGo = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.rollMessageDlg, "MsgText");
    self.rollMessageText = GlobalNS.UtilEngineWrap.getComByPath(self.rollMessageDlg, "MsgText", "Text");

    if 1 == GCtxExt.mPlayerData.mGameData.mMessageType then
        self:ShowPopMessage(GCtxExt.mPlayerData.mGameData.mMessageText);
    elseif(2 == GCtxExt.mPlayerData.mGameData.mMessageType) then
        self:ShowRollMessage(GCtxExt.mPlayerData.mGameData.mMessageText);
    else

    end    
end

function M:onShow()
    M.super.onShow(self);
end

function M:onHide()
    M.super.onHide(self);
end

function M:onExit()
    self.mTimer:Stop();
    M.super.onExit(self);
end

function M:onOKBtnClk()
    self:exit();

    if 1 == GCtxExt.mPlayerData.mGameData.mMessageMethond then
        GCtxExt.mPlayerData.mGameData:returnStartGame();
    end

    GCtxExt.mPlayerData.mGameData.mMessageMethond = 0; --重置
end

function M:ShowPopMessage(msg)
    self.popMessageDlg:SetActive(true);
    self.rollMessageDlg:SetActive(false);
    self.popMessageText.text = msg;
end

function M:ShowRollMessage(msg)
    self.popMessageDlg:SetActive(false);
    self.rollMessageDlg:SetActive(true);
    self.rollMessageText.text = msg;

    self.mTimer:setTotalTime(self.mRollTime);
    self.mTimer.mInternal = self.mInterval;
    self.mTimer:setFuncObject(self, self.onTick, 0);
    self.mTimer:Start();
end

function M:onTick(dispObj, eventId)
    local lefttime = GlobalNS.UtilMath.ceil(self.mTimer:getLeftRunTime());
    --消息滚动
    local runtime = self.mTimer:getRunTime();
    local interval = self.mRollTime / self.mInterval;
    local runval = runtime / self.mInterval;
    local y = 129 * runval / interval;
    GlobalNS.UtilEngineWrap.GetComponent(self.rollMessageTextGo, "RectTransform").localPosition = Vector3.New(0, -43 + y, 0); 
    --
	if lefttime <= 0 then
        self:exit();
    end
end

return M;