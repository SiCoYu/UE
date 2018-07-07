MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiAccountPanel.AccountPanelNS");
MLoader("MyLua.Ui.UiAccountPanel.AccountPanelData");
MLoader("MyLua.Ui.UiAccountPanel.AccountPanelCV");

--UI区
local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiAccountPanel";
GlobalNS.AccountPanelNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUiAccountPanel;
	self.mData = GlobalNS.new(GlobalNS.AccountPanelNS.AccountPanelData);
    self.index = 1;
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);
	
    self.mAvatarBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mAvatarBtn:addEventHandle(self, self.onAvatarBtnClk, 0);

	self.mCloseBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mCloseBtn:addEventHandle(self, self.onBtnClk, 0);

    self.mShareBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mShareBtn:addEventHandle(self, self.onShareBtnClk, 0);
end

function M:onReady()
    M.super.onReady(self);
    local BG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, "BG");    
	self.mCloseBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(
			BG, 
			GlobalNS.AccountPanelNS.AccountPanelPath.BtnClose)
		);
    self.mShareBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "Share_BtnTouch"));

    local Avatar = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "Avatar");
    self.mAvatarBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Avatar, "Avatar_BtnTouch"));
    local Info = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Avatar, "Info");

    --头像   
    if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey("Avatar") then
        self.index = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt("Avatar");
    end
    self:resetAvatar(self.index);

    --账号
    local Name = GlobalNS.UtilEngineWrap.getComByPath(Info, "Name", "Text");
    local username = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getString(SDK.Lib.SystemSetting.USERNAME);
    if username == nil then
        username = "游客";
    end
    Name.text = username;

    --签名
    self.Sign = GlobalNS.UtilEngineWrap.getComByPath(Info, "Sign", "InputField");
    if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey("SIGN") then
        local signText = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getString("SIGN");
        self.Sign.text = signText;
    end
    
    --游戏数据
    local Game_Data = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "Game_Data");

    local zhenzhu = GlobalNS.UtilEngineWrap.getComByPath(Game_Data, "ZhenZhu", "Text");
    if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey(CtxExt.mPlayerData.mGoodsData.ZhenZhuId) then
        local num = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt(CtxExt.mPlayerData.mGoodsData.ZhenZhuId);
        zhenzhu.text = "珍珠: "..num;
    end

    local haixing = GlobalNS.UtilEngineWrap.getComByPath(Game_Data, "HaiXing", "Text");
    if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey(CtxExt.mPlayerData.mGoodsData.HaiXingId) then
        local num = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt(CtxExt.mPlayerData.mGoodsData.HaiXingId);
        haixing.text = "海星: "..num;
    end

    local HuiHe = GlobalNS.UtilEngineWrap.getComByPath(Game_Data, "HuiHe", "Text");
    if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey("HuiHe") then
        local num = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt("HuiHe");
        HuiHe.text = "游戏回合数: "..num;
    end

    local SwallowNum = GlobalNS.UtilEngineWrap.getComByPath(Game_Data, "SwallowNum", "Text");
    if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey("SwallowNum") then
        local num = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt("SwallowNum");
        SwallowNum.text = "总吞噬人数: "..num;
    end

    local MaxMass = GlobalNS.UtilEngineWrap.getComByPath(Game_Data, "MaxMass", "Text");
    if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey("MaxMass") then
        local mass = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getFloat("MaxMass");
        local radius = GlobalNS.UtilMath.getRadiusByMass(mass); --服务器传过来的是质量
        MaxMass.text = "历史最大重量: "..GlobalNS.UtilMath.getShowMass(radius);
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

function M:onBtnClk()
    GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setString("SIGN", self.Sign.text);
    self.mAvatarBtn:dispose();
	self:exit();
end

function M:onAvatarBtnClk()
	Ctx.mUiMgr:loadAndShow(GlobalNS.UiFormId.eUiAccountAvatarPanel);
end

function M:onShareBtnClk()
	--GlobalNS.CSSystem.Ctx.msInstance.mCamSys:ShareTo3Party();
    self:exit();
end

function M:resetAvatar(index)
    self.index = index;
	self.mAvatarBtn.mImage:setSelfGo(self.mAvatarBtn:getSelfGo());
	self.mAvatarBtn.mImage:setSpritePath("DefaultSkin/Avatar/"..self.index..".png", GlobalNS.UtilStr.tostring(self.index));
    --self.mAvatarBtn.mImage:setSpritePath("DefaultSkin/Avatar/Avatar_RGB.png", GlobalNS.UtilStr.tostring(self.index));
end

return M;