MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiAccountPanel.AccountPanelNS");
MLoader("MyLua.Ui.UiAccountPanel.AccountPanelData");
MLoader("MyLua.Ui.UiAccountPanel.AccountPanelCV");
MLoader("MyLua.Ui.UiAccountPanel.AvatarItemData");

--UI区
local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiAccountAvatarPanel";
GlobalNS.AccountPanelNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUiAccountAvatarPanel;
	self.mData = GlobalNS.new(GlobalNS.AccountPanelNS.AccountPanelData);

    self.mAvatarNum = 4;
    self.index = 1;
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);
    
    self.mAvataritem_prefab = GlobalNS.new(GlobalNS.AuxPrefabLoader);
	self.mAvataritem_prefab:setIsNeedInsPrefab(false);
    self.isPrefabLoaded = false;
    self.avataritems = { };

    self.mCloseBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mCloseBtn:addEventHandle(self, self.onCloseBtnClk, 0);

	self.mOKBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mOKBtn:addEventHandle(self, self.onOKBtnClk, 0);
end

function M:onReady()
    M.super.onReady(self);
    local BG = GlobalNS.UtilApi.TransFindChildByPObjAndPath(self.mGuiWin, "BG");
    local TopBG = GlobalNS.UtilApi.TransFindChildByPObjAndPath(BG, "TitleBGImage");
	self.mCloseBtn:setSelfGo(GlobalNS.UtilApi.TransFindChildByPObjAndPath(TopBG, "Close_BtnTouch"));
    
    --Avatar区
    local MiddlePanel = GlobalNS.UtilApi.TransFindChildByPObjAndPath(BG, "MiddlePanel");    
    self.scrollrect = GlobalNS.UtilApi.TransFindChildByPObjAndPath(MiddlePanel, "ScrollRect");
    local viewport =  GlobalNS.UtilApi.TransFindChildByPObjAndPath(self.scrollrect, "Viewport");
    self.AvatarContentRect = GlobalNS.UtilApi.getComByPath(viewport, "Content", "RectTransform");

    --加载avataritems
	self.mAvataritem_prefab:asyncLoad("UI/UiAccountPanel/AvatarItem.prefab", self, self.onPrefabLoaded, nil);    

    --底部
    local BottomBG = GlobalNS.UtilApi.TransFindChildByPObjAndPath(BG, "BottomBGImage");
	self.mOKBtn:setSelfGo(GlobalNS.UtilApi.TransFindChildByPObjAndPath(BottomBG, "OK_BtnTouch"));
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

function M:onPrefabLoaded(dispObj)
    self.mAvatarItemPrefab = self.mAvataritem_prefab:getPrefabTmpl();
    self.isPrefabLoaded = true;

    self:updateUIData();
end

function M:CreateAvatarItem()
    if not self.isPrefabLoaded then
        return;
    end

    --清空
    self:clearObj();

    --重新生成
    for i=1, self.mAvatarNum do
        local avataritem = GlobalNS.new(GlobalNS.AvatarItemData);
        
        avataritem:init(self.mAvatarItemPrefab, self.AvatarContentRect, i);
        
        self.avataritems[i] = avataritem;
    end

    --滚动到起始位置，默认会在中间
    GlobalNS.UtilApi.GetComponent(self.scrollrect, "ScrollRect").verticalNormalizedPosition = 1;
end

function M:updateUIData()   
    self:CreateAvatarItem();
    
    if #self.avataritems == self.mAvatarNum then
        local index = 1;
        if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey("Avatar") then
            index = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt("Avatar");
        end
        self:SetAvatarItems(index);
    end
end

--物品数据
function M:SetAvatarItems(index)
    for i=1, self.mAvatarNum do
        --标识
        local HotImage = GlobalNS.UtilApi.TransFindChildByPObjAndPath(self.avataritems[i].m_go, "Flag");
        HotImage:SetActive(false);
    end
    local HotImage = GlobalNS.UtilApi.TransFindChildByPObjAndPath(self.avataritems[index].m_go, "Flag");
    HotImage:SetActive(true);
    self.index = index;
end

function M:onOKBtnClk()
    self:clearObj();
    
    if GCtx.mUiMgr:hasForm(GlobalNS.UiFormId.eUiAccountPanel) then
        local form = GCtx.mUiMgr:getForm(GlobalNS.UiFormId.eUiAccountPanel);
        if nil ~= form and form.mIsReady then
            form:resetAvatar(self.index);
        end
    end

    if GCtx.mUiMgr:hasForm(GlobalNS.UiFormId.eUiStartGame) then
        local form = GCtx.mUiMgr:getForm(GlobalNS.UiFormId.eUiStartGame);
        if nil ~= form and form.mIsReady then
            form:resetAvatar(self.index);
        end
    end

    GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setInt("Avatar", self.index);
	self:exit();
end

function M:onCloseBtnClk()
    self:clearObj();
    self.mAvataritem_prefab:dispose();
	self:exit();
end

function M:clearObj()
    --清空
    for i=1, #self.avataritems do
        local avataritem = self.avataritems[i];
        GlobalNS.delete(avataritem.avatarItemBtn);
        GlobalNS.UtilApi.Destroy(avataritem.m_go);
    end
    self.avataritems = {};
end

return M;