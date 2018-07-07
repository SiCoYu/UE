--region *.lua
--Date
--此文件由[BabeLua]插件自动生成

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "ItemData";
GlobalNS[M.clsName] = M;

function M:ctor(...)
    self.m_go = nil;
    self.day = 1;
    self.m_Id = 0;
    self.m_Name = "";
    self.m_Enable = false;
    self.ItemBtn = false;
end

function M:dtor()
    self.m_go:dispose();
    self.ItemBtn:dispose();
end

function M:init(_Prefab, _Content, _day)
    self.m_go = GlobalNS.UtilEngineWrap.Instantiate(_Prefab);
    self.m_go.transform.parent = _Content;
    self.m_go.transform.localScale = Vector3.New(1.0, 1.0, 1.0);
    self.m_go.name = "Item" .. _day .. "BtnTouch";

    self.ItemBtn = GlobalNS.new(GlobalNS.AuxButton);
    self.ItemBtn:setSelfGo(self.m_go);
    self.ItemBtn:addEventHandle(self, self.onItemBtnClk, 0);

    self.day = _day;
end

function M:onItemBtnClk()
    if GCtxExt.mPlayerData.mSignData.day ~= 0 then
        GCtxExt.mPlayerData.mSignData:setBtnState(GCtxExt.mPlayerData.mSignData.day);
    end
    
    GlobalNS.UtilEngineWrap.disableBtn(self.m_go);
	GCtxExt.mPlayerData.mSignData.day = self.day;
end

return M;

--endregion
