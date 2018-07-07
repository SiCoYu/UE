MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiEmoticonPanel.EmoticonPanelNS");
MLoader("MyLua.Ui.UiEmoticonPanel.EmoticonPanelData");
MLoader("MyLua.Ui.UiEmoticonPanel.EmoticonPanelCV");

--UI区
local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiEmoticonPanel";
GlobalNS.EmoticonPanelNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUiEmoticonPanel;
	self.mData = GlobalNS.new(GlobalNS.EmoticonPanelNS.EmoticonPanelData);

    self.mTimer = GlobalNS.new(GlobalNS.DaoJiShiTimer);
    self.mRollTime = 1;
    self.mInterval = 0.01; --滚动间隔

    self.emoticon = nil;
    self.emoticonindex = 1;
    self.emoticonstart_y = -167.5;
    self.emoticonnum = 10;
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);
end

function M:onReady()
    M.super.onReady(self);
	local rollEmoticonDlg = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, "RollEmoticonDlg");

    self.Emoticon = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(rollEmoticonDlg, "Emoticon");
    self.Emoticon_Big = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(rollEmoticonDlg, "Emoticon_Big");
    self.emoticon = GlobalNS.new(GlobalNS.AuxImage);

    local _time = os.clock();
    math.randomseed(_time);
    self.emoticonindex = math.random(1, self.emoticonnum);

    if self.emoticonindex <= 4 then
        self.emoticon:setSelfGo(self.Emoticon);
        self.Emoticon:SetActive(true);
        self.Emoticon_Big:SetActive(false);
        self.emoticonstart_y = -167.5;
    else
        self.emoticon:setSelfGo(self.Emoticon_Big);
        self.Emoticon:SetActive(false);
        self.Emoticon_Big:SetActive(true);
        self.emoticonstart_y = -117.5;
    end
    
	self.emoticon:setSpritePath("DefaultSkin/Emoticon/"..self.emoticonindex..".png", GlobalNS.UtilStr.tostring(self.emoticonindex));

    self:RollEmoticon();
end

function M:RollEmoticon()
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
    local y = 187 * runval / interval;
    
    if self.emoticonindex <= 4 then
        GlobalNS.UtilEngineWrap.GetComponent(self.Emoticon, "RectTransform").localPosition = Vector3.New(0, self.emoticonstart_y + y, 0); 
    else
        GlobalNS.UtilEngineWrap.GetComponent(self.Emoticon_Big, "RectTransform").localPosition = Vector3.New(0, self.emoticonstart_y + y, 0); 
    end 
    
    --
	if lefttime <= 0 then
        self.emoticon:dispose();
        self.mTimer:Stop();
        self:exit();
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
end

return M;