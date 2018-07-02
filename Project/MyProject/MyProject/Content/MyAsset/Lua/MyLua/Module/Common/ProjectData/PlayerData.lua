local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "PlayerData";
GlobalNS[M.clsName] = M;

MLoader("MyLua.Module.Common.ProjectData.GameData");
MLoader("MyLua.Module.Common.ProjectData.GoodsData");
MLoader("MyLua.Module.Common.ProjectData.SignData");

function M:ctor()
	self.mGameData = GlobalNS.new(GlobalNS.GameData);
    self.mGoodsData = GlobalNS.new(GlobalNS.GoodsData);
    self.mSignData = GlobalNS.new(GlobalNS.SignData);
end

function M:dtor()

end

function M:init()
	self.mGameData:init();
	self.mGoodsData:init();
	self.mGameData:init();
end

function M:dispose()
	self.mGameData:dispose();
	self.mGoodsData:dispose();
	self.mGameData:dispose();
end

return M;