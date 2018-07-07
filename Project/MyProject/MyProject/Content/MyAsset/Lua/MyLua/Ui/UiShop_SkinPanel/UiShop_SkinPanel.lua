MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiShop_SkinPanel.Shop_SkinPanelNS");
MLoader("MyLua.Ui.UiShop_SkinPanel.Shop_SkinPanelData");
MLoader("MyLua.Ui.UiShop_SkinPanel.Shop_SkinPanelCV");
MLoader("MyLua.Ui.UiShop_SkinPanel.GoodsItemData");

--UI区
local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiShop_SkinPanel";
GlobalNS.Shop_SkinPanelNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUiShop_SkinPanel;
	self.mData = GlobalNS.new(GlobalNS.Shop_SkinPanelNS.Shop_SkinPanelData);
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);
    --商店类别
    self.mSkinBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mSkinBtn:addEventHandle(self, self.onSkinBtnClk, 0);
    --[[待扩充
    self.mSkinBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mSkinBtn:addEventHandle(self, self.onSkinBtnClk);
    self.mSkinBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mSkinBtn:addEventHandle(self, self.onSkinBtnClk);
	]]--
    self.mHaiXingBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mHaiXingBtn:addEventHandle(self, self.onHaiXingBtnClk, 0);
    self.mZhenZhuBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mZhenZhuBtn:addEventHandle(self, self.onZhenZhuBtnClk, 0);
    
    --物品类别
    self.mShapeBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mShapeBtn:addEventHandle(self, self.onShapeBtnClk, 0);
    self.mChildBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mChildBtn:addEventHandle(self, self.onChildBtnClk, 0);
    self.mFilterToggle = nil;
    --goodsitem prefab
    self.mGoodsitem_prefab = GlobalNS.new(GlobalNS.AuxPrefabLoader);
	self.mGoodsitem_prefab:setIsNeedInsPrefab(false);
    self.isPrefabLoaded = false;
    --goodsitems gameobject数组
    self.goodsitems = { };

    --返回
	self.mBackBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mBackBtn:addEventHandle(self, self.onBackBtnClk, 0);
end

function M:onReady()
    M.super.onReady(self);
    local BG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, "BG");
    --顶部
    local TitleBG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "TitleBGImage");
	self.mSkinBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(TitleBG, "Skin_BtnTouch"));
    --[[待扩充
    self.mSkinBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(TitleBG, "Skin_BtnTouch"));
    self.mSkinBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(TitleBG, "Skin_BtnTouch"));
    ]]--
    local HaiXingBG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(TitleBG, "HaiXingBG");
    self.HaiXingNumText = GlobalNS.UtilEngineWrap.getComByPath(HaiXingBG, "Num", "Text");
    self.mHaiXingBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(HaiXingBG, "HaiXing_BtnTouch"));

    local ZhenZhuBG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(TitleBG, "ZhenZhuBG");
    self.ZhenZhuNumText = GlobalNS.UtilEngineWrap.getComByPath(ZhenZhuBG, "Num", "Text");
    self.mZhenZhuBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(ZhenZhuBG, "ZhenZhu_BtnTouch"));

    --商品区
    local MiddlePanel = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "MiddlePanel");
    local Middle_TopPanel = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(MiddlePanel, "TopPanel");
    self.mShapeBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Middle_TopPanel, "Shape_BtnTouch"));
    self.mChildBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Middle_TopPanel, "Child_BtnTouch"));
    self.StateText = GlobalNS.UtilEngineWrap.getComByPath(Middle_TopPanel, "StateText", "Text");

    self.mFilterToggle = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(Middle_TopPanel, "FilterToggle")
    GlobalNS.UtilEngineWrap.addToggleHandle(self.mFilterToggle, self, self.onValueChanged);
    --[[下拉列表待补充]]--

    self.scrollrect = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(MiddlePanel, "ScrollRect");
    local viewport =  GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.scrollrect, "Viewport");
    self.GoodsContentRect = GlobalNS.UtilEngineWrap.getComByPath(viewport, "Content", "RectTransform");
    self.Tip = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(MiddlePanel, "Tip");
    self.Tip:SetActive(false);
    --加载goodsitems
	self.mGoodsitem_prefab:asyncLoad("UI/UiShop_SkinPanel/GoodsItem.prefab", self, self.onPrefabLoaded, nil);    

    --底部
    local BottomBG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BG, "BottomBGImage");
	self.mBackBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(BottomBG, "Back_BtnTouch"));

    --货币
    if not GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey(CtxExt.mPlayerData.mGoodsData.HaiXingId) then
        self:refreshGoldNum(10000, 10000);
    else
        local haixing = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt(CtxExt.mPlayerData.mGoodsData.HaiXingId);
        local zhenzhu = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt(CtxExt.mPlayerData.mGoodsData.ZhenZhuId);
        self:refreshGoldNum(haixing, zhenzhu);
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

function M:onSkinBtnClk()
	CtxExt.mPlayerData.mGoodsData.CurrentShopType = GlobalNS.UiFormId.eUiShop_SkinPanel;
end
--[[待扩充
function M:onSkinBtnClk()
	Ctx.mLogSys:log("Shop Skin Clk", GlobalNS.LogTypeId.eLogCommon);
end

function M:onSkinBtnClk()
	Ctx.mLogSys:log("Shop Skin Clk", GlobalNS.LogTypeId.eLogCommon);
end
]]--

function M:onHaiXingBtnClk()
	Ctx.mLogSys:log("海星： " .. self.HaiXingNumText.text, GlobalNS.LogTypeId.eLogCommon);
end

function M:onZhenZhuBtnClk()
	Ctx.mLogSys:log("珍珠： " .. self.ZhenZhuNumText.text, GlobalNS.LogTypeId.eLogCommon);
end

function M:onShapeBtnClk()
    self.StateText.text = "正在出售";
    CtxExt.mPlayerData.mGoodsData.CurrentGoodsType = 1;
    CtxExt.mPlayerData.mGoodsData:getGoodsItems(CtxExt.mPlayerData.mGoodsData.CurrentShopType, CtxExt.mPlayerData.mGoodsData.CurrentGoodsType);
end

function M:onChildBtnClk()
    self.StateText.text = "正在出售";
    CtxExt.mPlayerData.mGoodsData.CurrentGoodsType = 2;
    CtxExt.mPlayerData.mGoodsData:getGoodsItems(CtxExt.mPlayerData.mGoodsData.CurrentShopType, CtxExt.mPlayerData.mGoodsData.CurrentGoodsType);
end

function M:onPrefabLoaded(dispObj)
    --获取goodsitem prefab对象
    self.mGoodsItemPrefab = self.mGoodsitem_prefab:getPrefabTmpl();
    self.isPrefabLoaded = true;
    CtxExt.mPlayerData.mGoodsData.CurrentGoodsType = 1;
    CtxExt.mPlayerData.mGoodsData:getGoodsItems(CtxExt.mPlayerData.mGoodsData.CurrentShopType, CtxExt.mPlayerData.mGoodsData.CurrentGoodsType); --初始打开
end

function M:CreateGoodsItem(isOwn)
    if not self.isPrefabLoaded then
        return;
    end

    --清空
    for i=1, #self.goodsitems do
        local goodsitem = self.goodsitems[i];
        GlobalNS.UtilEngineWrap.Destroy(goodsitem.m_go);
    end
    self.goodsitems = {};

    --重新生成
    for i=1, CtxExt.mPlayerData.mGoodsData.goodsCount do
        local goodsitem = GlobalNS.new(GlobalNS.GoodsItemData);
        
        --用goodsitem prefab生成GameObject对象
        goodsitem:init(self.mGoodsItemPrefab, self.GoodsContentRect, i, isOwn);
        self.goodsitems[i] = goodsitem;
    end

    --滚动到起始位置，默认会在中间
    GlobalNS.UtilEngineWrap.GetComponent(self.scrollrect, "ScrollRect").verticalNormalizedPosition = 1;
end

function M:updateUIData(isOwn)
    if CtxExt.mPlayerData.mGoodsData.goodsCount == 0 then
        self.scrollrect:SetActive(false);
        self.Tip:SetActive(true);
        return;
    else
        self.scrollrect:SetActive(true);
        self.Tip:SetActive(false);
    end

    self:CreateGoodsItem(isOwn);

    if #self.goodsitems == CtxExt.mPlayerData.mGoodsData.goodsCount then        
        self:SetGoodsItems(isOwn);
    end
end

--物品数据
function M:SetGoodsItems(isOwn)
    for i=1, CtxExt.mPlayerData.mGoodsData.goodsCount do
        local goodsitem = self.goodsitems[i].m_go.transform;
        
        --热卖标识
        local HotImage = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.goodsitems[i].m_go, "HotImage");
        local Hot = GlobalNS.UtilEngineWrap.getComByPath(HotImage, "HotText", "Text");
        Hot.text = CtxExt.mPlayerData.mGoodsData.goodsitems[i].m_hot;

        --形状
        local Avatar = GlobalNS.UtilEngineWrap.getComByPath(goodsitem, "GoodsImage", "Image");
        --Sprite avatarSprite = Resources.Load("Avatar/DefaultAvatar", typeof(Sprite)) as Sprite;
        --Avatar.overrideSprite = avatarSprite;

        --物品名
        local Name = GlobalNS.UtilEngineWrap.getComByPath(goodsitem, "GoodsName", "Text");
        Name.text = CtxExt.mPlayerData.mGoodsData.goodsitems[i].m_goodsName;        

        --材料数量
        local BuyItemBtn = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.goodsitems[i].m_go, "BuyItem_BtnTouch");
        if isOwn then --已拥有物品
            local usingStr = "使用";
            if CtxExt.mPlayerData.mGoodsData.goodsitems[i].m_needNum == 0 then
                usingStr = "使用";
            else
                usingStr = "已使用";
            end
            GlobalNS.UtilEngineWrap.getComByPath(BuyItemBtn, "Num", "Text").text = usingStr;
        else
            GlobalNS.UtilEngineWrap.getComByPath(BuyItemBtn, "Num", "Text").text = CtxExt.mPlayerData.mGoodsData.goodsitems[i].m_needNum;
            --GlobalNS.UtilEngineWrap.getComByPath(BuyItemBtn, "Kind", "Image");
        end

        --专属标识
        local OnlyImage = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.goodsitems[i].m_go, "OnlyImage");
        local Only = GlobalNS.UtilEngineWrap.getComByPath(OnlyImage, "OnlyText", "Text");
        Only.text = CtxExt.mPlayerData.mGoodsData.goodsitems[i].m_only;

        --商品数据
        self.goodsitems[i].m_Id = CtxExt.mPlayerData.mGoodsData.goodsitems[i].m_goodsID;
        self.goodsitems[i].m_Name = CtxExt.mPlayerData.mGoodsData.goodsitems[i].m_goodsName;
        self.goodsitems[i].m_NeedId = CtxExt.mPlayerData.mGoodsData.goodsitems[i].m_needID;
        self.goodsitems[i].m_NeedNum = CtxExt.mPlayerData.mGoodsData.goodsitems[i].m_needNum;
    end
end

function M:refreshGoldNum(HaiXingNum, ZhenZhuNum)
	GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setInt(CtxExt.mPlayerData.mGoodsData.HaiXingId, HaiXingNum);
    GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setInt(CtxExt.mPlayerData.mGoodsData.ZhenZhuId, ZhenZhuNum);

    self.HaiXingNumText.text = HaiXingNum;
    self.ZhenZhuNumText.text = ZhenZhuNum;
end

function M:onBackBtnClk()
    --清空
    for i=1, #self.goodsitems do
        local goodsitem = self.goodsitems[i];
        GlobalNS.UtilEngineWrap.Destroy(goodsitem.m_go);
    end
    self.goodsitems = {};
    self.mGoodsitem_prefab:dispose();
	self:exit();
end

function M:onValueChanged(check)
    if check then
        Ctx.mLogSys:log("true", GlobalNS.LogTypeId.eLogCommon);
    else
        Ctx.mLogSys:log("false", GlobalNS.LogTypeId.eLogCommon);
    end
end

return M;