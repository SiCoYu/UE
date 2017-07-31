MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");
MLoader("MyLua.Libs.AuxComponent.AuxUIComponent.AuxWindow");
MLoader("MyLua.Libs.AuxComponent.AuxUIComponent.AuxUITypeId");

local M = GlobalNS.Class(GlobalNS.AuxWindow);
M.clsName = "AuxButton";
GlobalNS[M.clsName] = M;

function M:ctor(...)
    self:AuxButton_1(...);
    self.mText = "";
end

function M:dtor()
	
end

function M:dispose()
	if (self.m_eventDisp ~= nil) then
        GlobalNS.UtilApi.RemoveListener(self.m_btn, self, self.onBtnClk);
    end
    M.super.dispose(self);
end

function M:AuxButton_1(...)
    local pntNode, path, styleId = ...;
    if(path == nil) then
        path = '';
    end
    if(styleId == nil) then
        styleId = GlobalNS.BtnStyleID.eBSID_None;
    end
    
    self.m_eventDisp = GlobalNS.new(GlobalNS.EventDispatch);
    if (pntNode ~= nil) then
        self.mSelfGo = GlobalNS.UtilApi.TransFindChildByPObjAndPath(pntNode, path);
        self:updateBtnCom(nil);
    end
end

function M:onSelfChanged()
	M.super.onSelfChanged(self);
	
	self:updateBtnCom(nil);
end

function M:updateBtnCom(dispObj)
    self.m_btn = GlobalNS.UtilApi.getComFromSelf(self.mSelfGo, GlobalNS.AuxUITypeId.Button);
    --GlobalNS.UtilApi.addEventHandle(self.m_btn, self, self.onBtnClk);
	GlobalNS.UtilApi.addEventHandleSelf(self.mSelfGo, self, self.onBtnClk);

    if "" ~= self.mText then
        self:setText(self.mText);
    end
end

function M:enable()
    self.m_btn.interactable = true;
end

function M:disable()
    self.m_btn.interactable = false;
end

-- 点击回调
function M:onBtnClk()
    self.m_eventDisp:dispatchEvent(self);
end

function M:addEventHandle(pThis, btnClk)
    self.m_eventDisp:addEventHandle(pThis, btnClk);
end

function M:syncUpdateCom()

end

function M:setText(text)
    self.mText = text;

    if("" ~= self.mText) then
        if(self.m_btn ~= nil) then
            local btn_text = GlobalNS.UtilApi.getComByPath(self.mSelfGo, "Text", "Text");
            btn_text.text = self.mText;
        end
    end
end

return M;