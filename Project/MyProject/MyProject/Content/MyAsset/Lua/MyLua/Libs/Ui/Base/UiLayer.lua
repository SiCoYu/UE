MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

MLoader("MyLua.Libs.Ui.Base.UiLayerId");

M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "UiLayer";
GlobalNS[M.clsName] = M;

function M:ctor()
	self.mName = "";
	self.mGo = nil;
end

function M:setGoName(name)
	self.mName = name;
end

function M:init()
	--self.mGo = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(GlobalNS.LayerPath.mNoDestroyGo, self.mName);
end

function M:getLayerGo()
	return self.mGo;
end

return M;