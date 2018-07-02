MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiPlayerDataPanel.PlayerDataPanelNS");
MLoader("MyLua.Ui.UiPlayerDataPanel.PlayerDataPanelData");
MLoader("MyLua.Ui.UiPlayerDataPanel.PlayerDataPanelCV");

local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiPlayerDataPanel";
GlobalNS.PlayerDataPanelNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUiPlayerDataPanel;
	self.mData = GlobalNS.new(GlobalNS.PlayerDataPanelNS.PlayerDataPanelData);    
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);    
end

function M:onReady()
    M.super.onReady(self);    
   
    self:refreshScore(GCtx.mGameData.mMyScore); --加载完成主动刷新一次分数
end

function M:refreshScore(score)
    if score == nil then
        score = 0;
    end
	
	if self.mGuiWin == nil then
        return;
    end
	
    self.mMass = GlobalNS.UtilApi.getComByPath(self.mGuiWin, "Mass_Text", "Text");         
    self.mMass.text = "分数：" .. score;
end

function M:refreshLeftTime(leftseconds)
    --获取Time_Text的Text组件
    if self.mGuiWin == nil then
        return;
    end
    self.mMass = GlobalNS.UtilApi.getComByPath(self.mGuiWin, "Time_Text", "Text");
    self.mMass.text = "时间：" .. self:getTimeText(leftseconds);
end

function M:getTimeText(leftseconds)
    local min = leftseconds / 60;
    min = math.floor(min);
    local second = leftseconds % 60;

    local timestr = "";
    if min > 9 then
        timestr = min .. ":";
    else
        timestr = "0" .. min .. ":";
    end

    if second > 9 then
        timestr = timestr .. second;
    else
        timestr = timestr .. "0" .. second;
    end

    return timestr;
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

return M;