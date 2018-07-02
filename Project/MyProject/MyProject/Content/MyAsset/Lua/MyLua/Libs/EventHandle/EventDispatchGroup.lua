MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");
MLoader("MyLua.Libs.DataStruct.MDictionary");
MLoader("MyLua.Libs.FrameHandle.LoopDepth");

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "EventDispatchGroup";
GlobalNS[M.clsName] = M;

function M:ctor()
    self.mGroupId2DispatchDic = GlobalNS.new(GlobalNS.MDictionary);
    self.mLoopDepth = GlobalNS.new(GlobalNS.LoopDepth);
end

-- 添加分发器
function M:addEventDispatch(groupID, disp)
    if (not self.mGroupId2DispatchDic:containsKey(groupID)) then
        self.mGroupId2DispatchDic:add(groupID, disp);
    end
end

function M:addEventHandle(groupID, pThis, handle, eventId)
    if(not self.mGroupId2DispatchDic:containsKey(groupID)) then
        local disp = GlobalNS.new(GlobalNS.EventDispatch);
        self:addEventDispatch(groupID, disp);
    end
	
    self.mGroupId2DispatchDic:value(groupID):addEventHandle(pThis, handle, eventId);
end

function M:removeEventHandle(groupID, pThis, handle, eventId)
    if (self.mGroupId2DispatchDic:containsKey(groupID)) then
        self.mGroupId2DispatchDic:value(groupID):removeEventHandle(pThis, handle, eventId);
    else
        -- 日志
    end
end

function M:dispatchEvent(groupID, dispatchObject)
    self.mLoopDepth:incDepth();
	
    if (self.mGroupId2DispatchDic:containsKey(groupID)) then
        self.mGroupId2DispatchDic:value(groupID):dispatchEvent(dispatchObject);
    else
        -- 日志
    end
	
    self.mIsInLoop:decDepth();
end

function M:clearAllEventHandle()
    if (not self.mLoopDepth:isInDepth()) then
        for _, dispatch in pairs(self.mGroupId2DispatchDic:getData()) do
            dispatch:clearEventHandle();
        end

        self.mGroupId2DispatchDic:clear();
    else
        -- 日志
    end
end

function M:clearGroupEventHandle(groupID)
    if (not self.mLoopDepth:isInDepth()) then
        if self.mGroupId2DispatchDic:containsKey(groupID) then
            self.mGroupId2DispatchDic:value(groupID):clearEventHandle();
            self.mGroupId2DispatchDic:remove(groupID);
        else
            -- 日志
        end
    else
        -- 日志
    end
end

return M;