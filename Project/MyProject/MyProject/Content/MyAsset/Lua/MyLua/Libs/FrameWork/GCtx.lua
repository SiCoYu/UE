MLoader("MyLua.Libs.Core.Prequisites");
MLoader("MyLua.Libs.Network.NetMgr");

-- 全局变量表，自己定义的所有的变量都放在 GCtx 表中，不放在 GlobalNS 表中
GCtx = {};
local M = GCtx;
local this = GCtx;

function M.ctor()
	
end

function M.dtor()
	
end

function M.preInit()
	--主要执行构造
    this.mConfig = GlobalNS.new(GlobalNS.Config);
    this.mTimerIdGentor = GlobalNS.new(GlobalNS.UniqueNumIdGen);
    this.mProcessSys = GlobalNS.new(GlobalNS.ProcessSys);
	
	this.mTickMgr = GlobalNS.new(GlobalNS.TickMgr);
    this.mTimerMgr = GlobalNS.new(GlobalNS.TimerMgr);
    this.mNetMgr = GlobalNS.new(GlobalNS.NetMgr);     -- Net 使用原始的表
    this.mLogSys = GlobalNS.new(GlobalNS.LogSys);
	
    this.mWidgetStyleMgr = GlobalNS.new(GlobalNS.WidgetStyleMgr);
	this.mUiMgr = GlobalNS.new(GlobalNS.UiMgr);
	this.mTableSys = GlobalNS.new(GlobalNS.TableSys);
	
    this.mNetCmdNotify = GlobalNS.new(GlobalNS.NetCmdNotify);
	this.mNetCmdNotify_KBE = GlobalNS.new(GlobalNS.NetCmdDispatchHandle_KBE);
	this.mFrameUpdateStatistics = GlobalNS.new(GlobalNS.FrameUpdateStatistics);
	
	this.mStrIdPoolSys = GlobalNS.new(GlobalNS.StrIdPoolSys);
	this.mObjectStrIdPoolSys = GlobalNS.new(GlobalNS.StrIdPoolSys);
	this.mObjectNumIdPoolSys = GlobalNS.new(GlobalNS.NumIdPoolSys);
	this.mSceneIdPoolSys = GlobalNS.new(GlobalNS.NumIdPoolSys);
end

function M.execInit()
	--主要执行 init 初始化
    GlobalNS.CSSystem.init();
    this.mNetMgr:init();
	GlobalNS.NoDestroyGo.init();
	this.mUiMgr:init();
	
	this.mFrameUpdateStatistics:init();
	this.mStrIdPoolSys.init();
	this.mObjectNumIdPoolSys.init();
	this.mSceneIdPoolSys.init();
end

function M.postInit()
	--主要处理真正的逻辑
    -- 加载逻辑处理
    GlobalNS.ClassLoader.loadClass("MyLua.Libs.FrameWork.GlobalEventCmd");
end

function M.init()
    this.preInit();
    this.execInit();
    this.postInit();
end

M.ctor();
M.init();

return M;