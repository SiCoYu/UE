MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiConsoleDlg.ConsoleDlgNS");
MLoader("MyLua.Ui.UiConsoleDlg.ConsoleDlgData");
MLoader("MyLua.Ui.UiConsoleDlg.ConsoleDlgCV");

--UI区
local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiConsoleDlg";
GlobalNS.ConsoleDlgNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUiConsoleDlg;
	self.mData = GlobalNS.new(GlobalNS.ConsoleDlgNS.ConsoleDlgData);
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);
    self.mData:init();

    self.MAX_LOG_NUM = 50; --最大记录数量
    self.num = 0;
    self.log = "";
	
	self.mSendBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mSendBtn:addEventHandle(self, self.onSendBtnClk, 0);

    self.mExitBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mExitBtn:addEventHandle(self, self.onExitBtnClk, 0);

    self.mClearBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mClearBtn:addEventHandle(self, self.onClearBtnClk, 0);
end

function M:onReady()
    M.super.onReady(self);
    local BG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, "BG_Image");
	self.mSendBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(
			BG, 
			GlobalNS.ConsoleDlgNS.ConsoleDlgPath.BtnSend)
		);
    self.mExitBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(
			BG, 
			GlobalNS.ConsoleDlgNS.ConsoleDlgPath.BtnExit)
		);
    self.mClearBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "Clear_BtnTouch"));

    self.mCmdInput = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "CmdInput");
    self.inputText = GlobalNS.UtilEngineWrap.GetComponent(self.mCmdInput, "InputField");

    self.viewbg = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "ViewBG");
    --self.viewtxet = GlobalNS.UtilEngineWrap.getComByPath(self.viewbg, "ShowView", "InputField");
    self.viewtxet = GlobalNS.UtilEngineWrap.getComByPath(self.viewbg, "ShowView", "Text");

    self.locklog = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "LockLog");
    self.locklogtoggle = GlobalNS.UtilEngineWrap.GetComponent(self.locklog, "Toggle");
    --self.locklog:addEventHandle(self, self.onToggleChanged, 0);

    local cmdtoggle = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "Cmd_Toggle");
    self.ClientToggle = GlobalNS.UtilEngineWrap.getComByPath(cmdtoggle, "ClientToggle", "Toggle");
    self.ServerToggle = GlobalNS.UtilEngineWrap.getComByPath(cmdtoggle, "ServerToggle", "Toggle");

    if self.locklogtoggle.isOn then
        GCtx.mLogSys:log("locked  ", GlobalNS.LogTypeId.eLogCommon);
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

function M:onSendBtnClk()
	local cmdtext = self.inputText.text;
    if self.ClientToggle.isOn then
        cmdtext = "client " .. cmdtext;
    end
    if self.ServerToggle.isOn then
        cmdtext = "server " .. cmdtext;
    end

    if string.len(cmdtext) > 0 then
        if string.find(cmdtext,"client") == 1 then
            self:doClientCmd(cmdtext);
        else
            --发送给服务器
            self:sendServerCmd(cmdtext);
        end
    end
end

function M:doClientCmd(str)
    local index = string.find(str," ");
    if nil == index then
        self:onSetLogText("<color=#FF0000>指令错误，检查是否以空格分割</color>");
    else
        local cmd = string.sub(str, index+1);
        self:doCmd(cmd);
        self:onSetLogText("<color=#00FF00>[client指令]</color> " .. str);
    end
end

function M:doCmd(str)
    local index = string.find(str," ");
    local cmd = nil;
    local params = nil;
    if index == nil then
        cmd = str;
    else
        cmd = string.sub(str, 1, index-1);
        params = string.sub(str, index+1);
    end 
    if self.mData.mId2HandleDic:containsKey(cmd) then        
        self.mData.mId2HandleDic:value(cmd)(self.mData, params);
    else
        self:onSetLogText(cmd .. " <color=#FF0000>指令不存在</color>");
    end
end

function M:sendServerCmd(str)
    local index = string.find(str," ");
    if nil == index then
        self:onSetLogText("<color=#FF0000>指令错误，检查是否以空格分割</color>");
    else
        local cmd = string.sub(str, index+1);
        --发送
        --[[ for Kbe
        self.heroentity = GlobalNS.CSSystem.Ctx.msInstance.mPlayerMgr:getHero():getEntity();
        self.heroentity:cellCall("exeGMCommand", cmd);
        ]]--
        self:onSetLogText("<color=#00FF00>[Server指令]</color> " .. str);
    end
end

function M:onExitBtnClk()
    self:ResetParams();
	self:exit();
end

function M:onClearBtnClk()
	self:ResetParams();
end

function M:ResetParams()
    self.viewtxet.text = "";
    self.log = "";
    self.num = 0;
end

function M:onSetLogText(text)
    self.num = self.num + 1;
    if self.num > self.MAX_LOG_NUM then
        local index = string.find(self.log,"\n");
        self.log = string.sub(self.log, index+1);
    end

    self.log = self.log .. text .. "\n";
    if self.locklogtoggle.isOn then
        GCtx.mLogSys:log("locked  ", GlobalNS.LogTypeId.eLogCommon);
    else
        self.viewtxet.text = self.log;
    end

    GlobalNS.UtilEngineWrap.GetComponent(self.viewbg, "ScrollRect").verticalNormalizedPosition = 0;
end

function M:onToggleChanged(value)
    if value then
        GCtx.mLogSys:log("locked  true", GlobalNS.LogTypeId.eLogCommon);
    else
        GCtx.mLogSys:log("locked  false", GlobalNS.LogTypeId.eLogCommon);
    end
end

return M;