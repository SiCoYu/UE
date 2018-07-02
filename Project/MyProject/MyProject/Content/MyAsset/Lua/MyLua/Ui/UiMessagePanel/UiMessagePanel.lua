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
    self.popMessageDlg = GlobalNS.UtilApi.TransFindChildByPObjAndPath(self.mGuiWin, "PopMessageDlg");
    self.popMessageText = GlobalNS.UtilApi.getComByPath(self.popMessageDlg, "MsgText", "InputField");
	self.mOKBtn:setSelfGo(GlobalNS.UtilApi.TransFindChildByPObjAndPath(self.popMessageDlg, "OK_BtnTouch"));

    self.rollMessageDlg = GlobalNS.UtilApi.TransFindChildByPObjAndPath(self.mGuiWin, "RollMessageDlg");
    self.rollMessageTextGo = GlobalNS.UtilApi.TransFindChildByPObjAndPath(self.rollMessageDlg, "MsgText");
    self.rollMessageText = GlobalNS.UtilApi.getComByPath(self.rollMessageDlg, "MsgText", "Text");

    if 1 == GCtx.mGameData.mMessageType then
        self:ShowPopMessage(GCtx.mGameData.mMessageText);
    elseif(2 == GCtx.mGameData.mMessageType) then
        self:ShowRollMessage(GCtx.mGameData.mMessageText);
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

    if 1 == GCtx.mGameData.mMessageMethond then
        GCtx.mGameData:returnStartGame();
    end

    GCtx.mGameData.mMessageMethond = 0; --重置
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
    GlobalNS.UtilApi.GetComponent(self.rollMessageTextGo, "RectTransform").localPosition = Vector3.New(0, -43 + y, 0); 
    --
	if lefttime <= 0 then
        self:exit();
    end
end

return M;