MLoader("MyLua.Libs.Core.DataPrequisites");

GCtxExt = {};
local M = GCtxExt;
local this = GCtxExt;

function M.ctor()
	
end

function M.dtor()
	
end

function M.preInit()
    this.mPlayerData = GlobalNS.new(GlobalNS.PlayerData);
    this.mEntityData = GlobalNS.new(GlobalNS.EntityData);
end

function M.execInit()
	this.mPlayerData.init();
	this.mEntityData.init();
end

function M.postInit()
	
end

function M.init()
    this.preInit();
    this.execInit();
    this.postInit();
end

function M.dispose()
	
end

M.ctor();
M.init();

return M;