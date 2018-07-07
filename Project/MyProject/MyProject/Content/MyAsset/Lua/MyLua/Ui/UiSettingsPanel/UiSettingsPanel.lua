MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiSettingsPanel.SettingsPanelNS");
MLoader("MyLua.Ui.UiSettingsPanel.SettingsPanelData");
MLoader("MyLua.Ui.UiSettingsPanel.SettingsPanelCV");

--UI区
local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiSettingsPanel";
GlobalNS.SettingsPanelNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUiSettingsPanel;
	self.mData = GlobalNS.new(GlobalNS.SettingsPanelNS.SettingsPanelData);
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);
	
	self.CloseBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.CloseBtn:addEventHandle(self, self.onCloseBtnClk, 0);

    self.TipBtn = GlobalNS.new(GlobalNS.AuxButton);
    self.TipBtn:addEventHandle(self, self.onTipBtnClk, 0);
end

function M:onReady()
    M.super.onReady(self);
    local BG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, "BG");
	self.CloseBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(
			BG, 
			GlobalNS.SettingsPanelNS.SettingsPanelPath.CloseBtn)
		);

    self:setOptModel();
    self:setServerAddr();
    self:setBgMusic();
    self:setSwallowState();
end

function M:setBgMusic()
    local BG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, "BG");
    local Bg_Center = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "Bg_Center");
    local Op_Bg = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Bg_Center, "Op_Bg");

    local Music_Switch = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Op_Bg, "Music_Switch");
    local MusicModel = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Music_Switch, "MusicModel");
    self.BG_Music = GlobalNS.UtilEngineWrap.getComByPath(MusicModel, "BG_Music", "Toggle");

    if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey("MusicModel") then
        if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt("MusicModel") == 1 then
            self.BG_Music.isOn = true;
        else
            self.BG_Music.isOn = false;
        end
    else
        self.BG_Music.isOn = true;
    end
end

function M:setOptModel()
    local BG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, "BG");
    local Bg_Center = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "Bg_Center");
    local Op_Bg = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Bg_Center, "Op_Bg");

    local Opt_Switch = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Op_Bg, "Opt_Switch");
    local OpModel = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Opt_Switch, "OptModel");
    self.JoyStickOp = GlobalNS.UtilEngineWrap.getComByPath(OpModel, "JoyStick", "Toggle");
    self.GravityOp = GlobalNS.UtilEngineWrap.getComByPath(OpModel, "Gravity", "Toggle");
    self.TipBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(OpModel, "Tip_BtnTouch"));

    if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey("OptionModel") then
        if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt("OptionModel") == 1 then
            self.JoyStickOp.isOn = true;
            self.GravityOp.isOn = false;
        else
            self.JoyStickOp.isOn = false;
            self.GravityOp.isOn = true;
        end
    else
        self.JoyStickOp.isOn = true;
        self.GravityOp.isOn = false;
    end
end

function M:setServerAddr()
    local BG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, "BG");
    local Bg_Center = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "Bg_Center");
    local Op_Bg = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Bg_Center, "Op_Bg");

    local Server_Switch = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Op_Bg, "Server_Switch");
    local ServerAddr = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Server_Switch, "ServerAddr");
    self.Server1 = GlobalNS.UtilEngineWrap.getComByPath(ServerAddr, "Server1", "Toggle");
    self.Server2 = GlobalNS.UtilEngineWrap.getComByPath(ServerAddr, "Server2", "Toggle");
    self.Server_input = GlobalNS.UtilEngineWrap.getComByPath(ServerAddr, "Server_input", "Toggle");

    self.ip = GlobalNS.UtilEngineWrap.getComByPath(ServerAddr, "ip", "InputField");
    self.port = GlobalNS.UtilEngineWrap.getComByPath(ServerAddr, "port", "InputField");
    self:setServerIP();

    if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey("ServerAddr") then
        if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt("ServerAddr") == 1 then
            self.Server1.isOn = true;
            self.Server2.isOn = false;
            self.Server_input.isOn = false;
        elseif GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt("ServerAddr") == 2 then
            self.Server1.isOn = false;
            self.Server2.isOn = true;
            self.Server_input.isOn = false;
        else
            self.Server1.isOn = false;
            self.Server2.isOn = false;
            self.Server_input.isOn = true;
        end
    else
        self.Server1.isOn = true;
        self.Server2.isOn = false;
        self.Server_input.isOn = false;
    end
end

function M:setServerIP()
    if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey("ip") then
        local ipStr = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getString("ip");
        self.ip.text = ipStr;
    else
        self.ip.text = "192.168.93.187";
    end

    if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey("port") then
        local port = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt("port");
        self.port.text = tostring(port);
    else
        self.port.text = "8002";
    end
end

function M:setSwallowState()
    local BG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, "BG");
    local Bg_Center = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "Bg_Center");
    local Op_Bg = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Bg_Center, "Op_Bg");

    local Swallow_Switch = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Op_Bg, "Swallow_Switch");
    local SwallowModel = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Swallow_Switch, "SwallowModel");
    self.BtnState = GlobalNS.UtilEngineWrap.getComByPath(SwallowModel, "BtnState", "Toggle");

    if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey("SwallowModel") then
        if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt("SwallowModel") == 1 then
            self.BtnState.isOn = true;
        else
            self.BtnState.isOn = false;
        end
    else
        self.BtnState.isOn = true;
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
end

function M:onCloseBtnClk()
    if self.BG_Music.isOn then
        GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setInt("MusicModel", 1);
    else
        GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setInt("MusicModel", 0);
    end

    if self.JoyStickOp.isOn then
        GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setInt("OptionModel", 1);
    else
        GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setInt("OptionModel", 2);
    end

    if self.BtnState.isOn then
        GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setInt("SwallowModel", 1);
    else
        GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setInt("SwallowModel", 0);
    end

    if self.Server1.isOn then
        GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setInt("ServerAddr", 1);
    elseif self.Server2.isOn then
        GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setInt("ServerAddr", 2);
    else
        GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setInt("ServerAddr", 10086);
        GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setString("ip", self.ip.text);
        GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setInt("port", tonumber(self.port.text));
    end
    GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:SetServerIP();

	self:exit();
end

function M:onTipBtnClk()
    GCtxExt.mPlayerData.mGameData:ShowMessageBox("摇杆模式：使用左侧摇杆控制方向\n重力模式：使用重力控制方向，按\n                   下左侧界面时向前移动");
end

return M;