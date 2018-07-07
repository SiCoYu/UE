MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

MLoader("MyLua.Libs.DataStruct.NoOrPriorityList.NoPriorityList.NoPriorityList");
MLoader("MyLua.Libs.DelayHandle.DelayNoOrPriorityHandleMgr");

-- 延迟优先级处理管理器
local M = GlobalNS.Class(GlobalNS.DelayNoOrPriorityHandleMgr);
M.clsName = "DelayPriorityHandleMgr";
GlobalNS[M.clsName] = M;

function M:ctor()
	self.mDeferredAddQueue = GlobalNS.new(GlobalNS.NoPriorityList);
	self.mDeferredAddQueue:setIsSpeedUpFind(true);
	self.mDeferredDelQueue = GlobalNS.new(GlobalNS.NoPriorityList);
	self.mDeferredDelQueue:setIsSpeedUpFind(true);

	self.mNoOrPriorityList = GlobalNS.new(GlobalNS.PriorityList);
	self.mNoOrPriorityList:setIsSpeedUpFind(true);
	self.mNoOrPriorityList:setIsOpKeepSort(true);
end

function M:init()
	M.super.init(self);
end

function M:dispose()
	M.super.dispose(self);
end

function M:addPriorityObject(priorityObject, priority)
	self:addNoOrPriorityObject(priorityObject, priority);
end

function M:removePriorityObject(tickObj)
	self:removeNoOrPriorityObject(tickObj);
end

return M;