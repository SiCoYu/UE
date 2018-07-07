MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");
MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxWindow");
MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxUITypeId");

local M = GlobalNS.Class(GlobalNS.AuxWindow);
M.clsName = "AuxButton";
GlobalNS[M.clsName] = M;

function M:ctor(...)
    self:AuxButton_1(...);
    self.mText = "";
    self.mImage = GlobalNS.new(GlobalNS.AuxImage);
end

function M:dtor()
	
end

function M:dispose()
	if (self.mClickEventDispatch ~= nil) then
        GlobalNS.UtilEngineWrap.RemoveListener(self.mBtn, self, self.onBtnClk);
    end
	if (self.mDownEventDispatch ~= nil) then
        GlobalNS.UtilEngineWrap.removeButtonDownEventHandle(self.mBtn, self, self.onBtnClk);
    end
	if (self.mUpEventDispatch ~= nil) then
        GlobalNS.UtilEngineWrap.removeButtonUpEventHandle(self.mBtn, self, self.onBtnClk);
    end
	if (self.mExitEventDispatch ~= nil) then
        GlobalNS.UtilEngineWrap.removeButtonExitEventHandle(self.mBtn, self, self.onBtnClk);
    end
	
    if self.mImage ~= nil then
        self.mImage:dispose();
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
    
    self.mClickEventDispatch = GlobalNS.new(GlobalNS.EventDispatch);
	self.mDownEventDispatch = GlobalNS.new(GlobalNS.EventDispatch);
	self.mUpEventDispatch = GlobalNS.new(GlobalNS.EventDispatch);
	self.mExitEventDispatch = GlobalNS.new(GlobalNS.EventDispatch);
	
    if (pntNode ~= nil) then
        self.mSelfGo = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(pntNode, path);
        self:updateBtnCom(nil);
    end
end

function M:onSelfChanged()
	M.super.onSelfChanged(self);
	
	self:updateBtnCom(nil);
end

function M:updateBtnCom(dispObj)
    self.mBtn = GlobalNS.UtilEngineWrap.getComFromSelf(self.mSelfGo, GlobalNS.AuxUITypeId.Button);
    --GlobalNS.UtilEngineWrap.addEventHandle(self.mBtn, self, self.onBtnClk);
	GlobalNS.UtilEngineWrap.addEventHandleSelf(self.mSelfGo, self, self.onBtnClk);
	GlobalNS.UtilEngineWrap.addButtonDownEventHandle(self.mSelfGo, self, self.OnPointerDown);
	GlobalNS.UtilEngineWrap.addButtonUpEventHandle(self.mSelfGo, self, self.OnPointerUp);
	GlobalNS.UtilEngineWrap.addButtonExitEventHandle(self.mSelfGo, self, self.OnPointerExit);

    if "" ~= self.mText then
        self:setText(self.mText);
    end
end

function M:enable()
    self.mBtn.interactable = true;
end

function M:disable()
    self.mBtn.interactable = false;
end

-- 点击回调
function M:onBtnClk()
    self.mClickEventDispatch:dispatchEvent(self);
end

function M:OnPointerDown(dispObj)
	self.mDownEventDispatch:dispatchEvent(self);
end

function M:OnPointerUp(dispObj)
	self.mUpEventDispatch:dispatchEvent(self);
end

function M:OnPointerExit(dispObj)
	self.mExitEventDispatch:dispatchEvent(self);
end

function M:addEventHandle(pThis, btnClk, eventId)
    self.mClickEventDispatch:addEventHandle(pThis, btnClk, eventId);
end

function M:addDownEventHandle(pThis, btnClk, eventId)
    self.mDownEventDispatch:addEventHandle(pThis, btnClk, eventId);
end

function M:addUpEventHandle(pThis, btnClk, eventId)
    self.mUpEventDispatch:addEventHandle(pThis, btnClk, eventId);
end

function M:addExitEventHandle(pThis, btnClk, eventId)
    self.mExitEventDispatch:addEventHandle(pThis, btnClk, eventId);
end

function M:syncUpdateCom()

end

function M:setText(text)
    self.mText = text;

    if("" ~= self.mText) then
        if(self.mBtn ~= nil) then
            local btn_text = GlobalNS.UtilEngineWrap.getComByPath(self.mSelfGo, "Text", "Text");
            btn_text.text = self.mText;
        end
    end
end

return M;