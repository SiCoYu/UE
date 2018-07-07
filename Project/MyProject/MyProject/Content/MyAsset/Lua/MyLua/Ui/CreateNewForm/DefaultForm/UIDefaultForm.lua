MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UIDefaultForm.DefaultFormNS");
MLoader("MyLua.Ui.UIDefaultForm.DefaultFormData");
MLoader("MyLua.Ui.UIDefaultForm.DefaultFormCV");

--UI区
local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UIDefaultForm";
GlobalNS.DefaultFormNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUIDefaultForm;
	self.mData = GlobalNS.new(GlobalNS.DefaultFormNS.DefaultFormData);
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);
	
	--self.mDefaultBtn = GlobalNS.new(GlobalNS.AuxButton);
	--self.mDefaultBtn:addEventHandle(self, self.onBtnClk, 0);
end

function M:onReady()
    M.super.onReady(self);
	--[[self.mDefaultBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(
			self.mGuiWin, 
			GlobalNS.DefaultFormNS.DefaultFormPath.BtnDefault)
		);
	--]]
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
	GCtx.mLogSys:log("Hello World", GlobalNS.LogTypeId.eLogCommon);
end

return M;