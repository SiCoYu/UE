MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

MLoader("MyLua.Libs.Network.CmdDispatch.NetModuleDispatchHandle");

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "NetCmdNotify";
GlobalNS[M.clsName] = M;

function M:ctor()
    self.mRevMsgCnt = 0;
    self.mHandleMsgCnt = 0;
    self.mNetDispatchList = GlobalNS.new(GlobalNS.MList);
    self.mIsStopNetHandle = false;
end

function M:getStopNetHandle()
    return self.mIsStopNetHandle;
end

function M:setStopNetHandle(value)
    self.mIsStopNetHandle = value;
end

function M:addOneDispatch(disp)
    if(not self.mNetDispatchList:contains(disp)) then
        self.mNetDispatchList:add(disp);
    end
end

function M:removeOneDispatch(disp)
    if(self.mNetDispatchList:contains(disp)) then
        self.mNetDispatchList:remove(disp);
    end
end

function M:handleMsg(msg)
    --if (false == mIsStopNetHandle) then -- 如果没有停止网络处理
        GCtx.mLogSys:log("NetCmdNotify::handleMsg", GlobalNS.LogTypeId.eLogCommon);
        for _, item in pairs(self.mNetDispatchList:list()) do
            item:handleMsg(msg);
        end
    --end
end

function M:addOneRevMsg()
    self.mRevMsgCnt = self.mRevMsgCnt + 1;
end

function M:addOneHandleMsg()
    self.mHandleMsgCnt = self.mHandleMsgCnt + 1;
end

function M:clearOneRevMsg()
    self.mRevMsgCnt = 0;
end

function M:clearOneHandleMsg()
    self.mHandleMsgCnt = 0;
end

return M;