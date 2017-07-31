MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.UI.UICore.Form");

MLoader("MyLua.Libs.AuxComponent.AuxUIComponent.AuxButton");

MLoader("MyLua.UI.UIRelivePanel.RelivePanelNS");
MLoader("MyLua.UI.UIRelivePanel.RelivePanelData");
MLoader("MyLua.UI.UIRelivePanel.RelivePanelCV");

local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UIRelivePanel";
GlobalNS.RelivePanelNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UIFormId.eUIRelivePanel;
	self.mData = GlobalNS.new(GlobalNS.RelivePanelNS.RelivePanelData);
    self.mTimer = GlobalNS.new(GlobalNS.TimerItemBase);
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);

    self.roomFatherBtn = GlobalNS.new(GlobalNS.AuxButton);

    self.mBackRoomBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mBackRoomBtn:addEventHandle(self, self.onBtnBackRoomClk);
	
	self.mReliveBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mReliveBtn:addEventHandle(self, self.onBtnReliveClk);
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

function M:onBtnReliveClk()
    self.mTimer:Stop();
	self:exit();
end

function M:onBtnBackRoomClk()
	GCtx.mLogSys:log("Back Room", GlobalNS.LogTypeId.eLogCommon);
end

function M:Client_notifyReliveSeconds(reliveseconds, entityID)
    self.mReliveBtn:setText("立即复活（<color=#00FF01FF>" .. reliveseconds .. "</color>）");
    local enemyname;
    local entity = GlobalNS.CSSystem.Ctx.mInstance.mPlayerMgr:getEntityByThisId(entityID):getEntity();
    
    if nil ~= entity and nil ~= entity.mEntity_SDK then
        enemyname = entity:getDefinedProperty("name");
    end
    self.roomFatherBtn:setText("你被  <color=#00FF01FF>" .. enemyname .. "</color> 吃掉了");

    self.mTimer:setTotalTime(reliveseconds);
    self.mTimer:setFuncObject(self, self.onTick);
    self.mTimer:Start();
end

function M:onTick()
	local lefttime = GlobalNS.UtilMath.ceil(self.mTimer:getLeftRunTime());
    if lefttime <= 0 then
        self:exit();
    else
        self.mReliveBtn:setText("立即复活（<color=#00FF01FF>" .. lefttime .. "</color>）");
    end    
end

return M;