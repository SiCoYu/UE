MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiTest.PackNS");
MLoader("MyLua.Ui.UiTest.PackData");
MLoader("MyLua.Ui.UiTest.PackCV");

local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiPack";
GlobalNS.TestNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUiPack;
	self.mData = GlobalNS.new(GlobalNS.PackNS.PackData);
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);
	self.mTestBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mTestBtn:addEventHandle(self, self.onBtnClk, 0);
end

function M:onReady()
    M.super.onReady(self);
	self.mTestBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, GlobalNS.TestNS.TestPath.BtnTest));
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
	
end

return M;

