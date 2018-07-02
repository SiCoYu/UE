MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiRelivePanel.RelivePanelNS");
MLoader("MyLua.Ui.UiRelivePanel.RelivePanelData");
MLoader("MyLua.Ui.UiRelivePanel.RelivePanelCV");

local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiRelivePanel";
GlobalNS.RelivePanelNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUiRelivePanel;
	self.mData = GlobalNS.new(GlobalNS.RelivePanelNS.RelivePanelData);
    self.mTimer = GlobalNS.new(GlobalNS.DaoJiShiTimer);
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);

    self.roomFatherBtn = GlobalNS.new(GlobalNS.AuxButton);

    self.mBackRoomBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mBackRoomBtn:addEventHandle(self, self.onBtnBackRoomClk, 0);
	
	self.mReliveBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mReliveBtn:addEventHandle(self, self.onBtnReliveClk, 0);
end

function M:onReady()
    M.super.onReady(self);
    self.roomFatherBtn:setSelfGo(GlobalNS.UtilApi.TransFindChildByPObjAndPath(self.mGuiWin, "BackRoom"));
    self.mBackRoomBtn:setSelfGo(GlobalNS.UtilApi.TransFindChildByPObjAndPath(
			self.roomFatherBtn:getSelfGo(), 
			GlobalNS.RelivePanelNS.RelivePanelPath.BtnBackRoom)
		);

	self.mReliveBtn:setSelfGo(GlobalNS.UtilApi.TransFindChildByPObjAndPath(
			self.mGuiWin, 
			GlobalNS.RelivePanelNS.RelivePanelPath.BtnRelive)
		);

    if GCtxExt.mPlayerData.mGameData.enemyId ~= 0 then
        self:UpdateReliveTimeAndEnemyName(GCtxExt.mPlayerData.mGameData.reliveTime, GCtxExt.mPlayerData.mGameData.enemyName);
    end 
    
    GlobalNS.CSSystem.Ctx.msInstance.mDataPlayer.mDataHero:setCanMove(false);
end

function M:onShow()
    M.super.onShow(self);
end

function M:onHide()
    M.super.onHide(self);
end

function M:onExit()
    M.super.onExit(self);
    self.mTimer:Stop();
    GlobalNS.CSSystem.Ctx.msInstance.mDataPlayer.mDataHero:setCanMove(true);
end

function M:onBtnReliveClk()
    self.mTimer:Stop();
	self:exit();
end

function M:onBtnBackRoomClk()
    self.mTimer:Stop();
	GCtxExt.mPlayerData.mGameData:returnStartGame();
end

function M:UpdateReliveTimeAndEnemyName(reliveseconds, enemyName)
    self.mReliveBtn:setText("立即复活（<color=#00FF01FF>" .. reliveseconds .. "</color>）");

    if GCtxExt.mPlayerData.mGameData.iskilledbyself then
        self.roomFatherBtn:setText("你在危险区 <color=#CC0033FF>自杀了</color>");
    else
        self.roomFatherBtn:setText("你被  <color=#00FF01FF>" .. enemyName .. "</color>  击败了");
    end

    self.mTimer:setTotalTime(reliveseconds);
    self.mTimer:setFuncObject(self, self.onTick, 0);
    self.mTimer:Start();
end

function M:onTick(dispObj, eventId)
	local lefttime = GlobalNS.UtilMath.ceil(self.mTimer:getLeftRunTime());
    if lefttime <= 0 then
        self:exit();
    else
        self.mReliveBtn:setText("立即复活（<color=#00FF01FF>" .. lefttime .. "</color>）");
    end    
end

return M;