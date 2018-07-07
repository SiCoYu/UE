MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiOptionPanel.OptionPanelNS");
MLoader("MyLua.Ui.UiOptionPanel.OptionPanelData");
MLoader("MyLua.Ui.UiOptionPanel.OptionPanelCV");

--UI区
local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiOptionPanel";
GlobalNS.OptionPanelNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUiOptionPanel;
	self.mData = GlobalNS.new(GlobalNS.OptionPanelNS.OptionPanelData);

    self.mTimer = GlobalNS.new(GlobalNS.DaoJiShiTimer);
    self.mCoolTime = 1;
    self.mInterval = 0.01;
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);

    self.mSwallowBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mSwallowBtn:addEventHandle(self, self.onSwallowBtnClk, 0);
	--self.mSwallowBtn:addDownEventHandle(self, self.onSwallowBtnDown, 0);
	--self.mSwallowBtn:addUpEventHandle(self, self.onSwallowBtnUp, 0);
end

function M:onReady()
    M.super.onReady(self);

    self.mSwallowBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(
			self.mGuiWin, 
			GlobalNS.OptionPanelNS.OptionPanelPath.BtnSwallow)
		);
    self.mSwallowImage = GlobalNS.UtilEngineWrap.getComByPath(self.mGuiWin, GlobalNS.OptionPanelNS.OptionPanelPath.BtnSwallow, "Image");
    GlobalNS.CSSystem.Ctx.msInstance.mGlobalDelegate.mMainChildNumChangedDispatch:addEventHandle(nil, nil, 0, self, self.refreshNum, 0);
end

function M:refreshNum()
    if(GlobalNS.CSSystem.Ctx.msInstance.mPlayerMgr:getHero() ~= nil and
       GlobalNS.CSSystem.Ctx.msInstance.mPlayerMgr:getHero().mPlayerSplitMerge ~= nil) then
         local num = GlobalNS.CSSystem.Ctx.msInstance.mPlayerMgr:getHero().mPlayerSplitMerge.mPlayerChildMgr:getEntityCount();
         if num > GlobalNS.CSSystem.Ctx.msInstance.mSnowBallCfg.mMaxShotNum then
            self.mCoolTime = GlobalNS.CSSystem.Ctx.msInstance.mSnowBallCfg.mMaxShotSeconds;
         else
            self.mCoolTime = GlobalNS.CSSystem.Ctx.msInstance.mSnowBallCfg.mMinShotSeconds + num * GlobalNS.CSSystem.Ctx.msInstance.mSnowBallCfg.mShotInteval;
         end
         self.mCoolTime = GlobalNS.UtilMath.keepTwoDecimalPlaces(self.mCoolTime);
    end
end

--射击冷却
function M:Fire(totalTime)
    self.mTimer.mIsDisposed = false;
    self.mTimer:setTotalTime(totalTime);
    self.mTimer.mInternal = self.mInterval;
    self.mTimer:setFuncObject(self, self.onTick, 0);
    self.mTimer:Start();
end

function M:onTick(dispObj, eventId)
    local lefttime = GlobalNS.UtilMath.keepTwoDecimalPlaces(self.mTimer:getLeftRunTime());
    self.mSwallowImage.fillAmount = lefttime / self.mCoolTime;
	if lefttime <= 0 then
        self.mSwallowImage.fillAmount = 1.0;
        self.mSwallowBtn:enable();
    end
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
    GlobalNS.CSSystem.Ctx.msInstance.mGlobalDelegate.mMainChildNumChangedDispatch:removeEventHandle(nil, nil, 0, self, self.refreshNum, 0);
end

function M:onSplitBtnClk()
	GlobalNS.CSSystem.startSplit();
end

function M:onSwallowBtnClk()
	GlobalNS.CSSystem.Fire();
    self.mSwallowBtn:disable();
    self:Fire(self.mCoolTime);
end

function M:onSwallowBtnDown()
	GlobalNS.CSSystem.startEmitSnowBlock();
end

function M:onSwallowBtnUp()
	GlobalNS.CSSystem.stopEmitSnowBlock();
end

return M;