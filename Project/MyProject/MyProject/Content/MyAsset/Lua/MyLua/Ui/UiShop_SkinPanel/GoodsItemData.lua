--region *.lua
--Date
--此文件由[BabeLua]插件自动生成

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "GoodsItemData";
GlobalNS[M.clsName] = M;

function M:ctor(...)
    self.m_go = nil;
    self.m_Id = 0;
    self.m_Name = "";
    self.m_NeedId = 0;
    self.m_NeedNum = 0;
    self.buyItemBtn = nil;
end

function M:dtor()
    self.m_go:dispose();
    self.buyItemBtn:dispose();
end

function M:init(_Prefab, _Content, _index, isOwn)
    self.m_go = GlobalNS.UtilEngineWrap.Instantiate(_Prefab);
    self.m_go.transform.parent = _Content;
    self.m_go.transform.localScale = Vector3.New(1.0, 1.0, 1.0);
    self.m_go.name = "GoodsItem" .. _index;

    self.buyItemBtn = GlobalNS.new(GlobalNS.AuxButton);
    self.buyItemBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.m_go, "BuyItem_BtnTouch"));
    if isOwn then
        self.buyItemBtn:addEventHandle(self, self.onUseBtnClk, 0);
    else
        self.buyItemBtn:addEventHandle(self, self.onBuyBtnClk, 0);
    end
end

function M:onUseBtnClk()
	
end

function M:onBuyBtnClk()
	local haixing = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt(GCtxExt.mPlayerData.mGoodsData.HaiXingId);
    local zhenzhu = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt(GCtxExt.mPlayerData.mGoodsData.ZhenZhuId);

    if self.m_NeedId == tonumber(GCtxExt.mPlayerData.mGoodsData.HaiXingId) then
        if haixing >= self.m_NeedNum then
            haixing = haixing - self.m_NeedNum;
        else
            Ctx.mLogSys:log("海星不足", GlobalNS.LogTypeId.eLogCommon);
        end        
    end

    if self.m_NeedId == tonumber(GCtxExt.mPlayerData.mGoodsData.ZhenZhuId) then
        if zhenzhu >= self.m_NeedNum then
            zhenzhu = zhenzhu - self.m_NeedNum;
        else
            Ctx.mLogSys:log("珍珠不足", GlobalNS.LogTypeId.eLogCommon);
        end
    end

    if Ctx.mUiMgr:hasForm(GlobalNS.UiFormId.eUiShop_SkinPanel) then
        local form = Ctx.mUiMgr:getForm(GlobalNS.UiFormId.eUiShop_SkinPanel);
        if nil ~= form and form.mIsReady then
            form:refreshGoldNum(haixing, zhenzhu);
        end
    end
end

return M;

--endregion
