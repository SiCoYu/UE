MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");

MLoader("MyLua.Libs.FrameWork.Layer.LayerId");

M = GlobalNS.StaticClass();
M.clsName = "LayerPath";
GlobalNS[M.clsName] = M;

function M.ctor()
	
end

function M.init()
	M.mNoDestroyGo = GlobalNS.UtilEngineWrap.GoFindChildByName(GlobalNS.LayerId.ND_CV_NoDestroy);
	M.mUIFirstCanvasGo = GlobalNS.UtilEngineWrap.GoFindChildByName(GlobalNS.LayerId.ND_CV_UIFirstCanvas);
	M.mUISecondCanvasGo = GlobalNS.UtilEngineWrap.GoFindChildByName(GlobalNS.LayerId.ND_CV_UISecondCanvas);
end

return M;