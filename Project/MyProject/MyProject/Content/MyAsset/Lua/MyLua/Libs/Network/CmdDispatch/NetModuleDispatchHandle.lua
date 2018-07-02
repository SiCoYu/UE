local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "NetModuleDispatchHandle";
GlobalNS[M.clsName] = M;

function M:ctor()
    self.mId2DispatchDic = GlobalNS.new(GlobalNS.MDictionary);
    --self.mCmdDispInfo = GlobalNS.new(GlobalNS.CmdDispatchInfo);
end

function M:addCmdHandle(cmdId, pThis, func, eventId)
    if (not self.mId2DispatchDic:containsKey(cmdId)) then
        local disp = GlobalNS.new(GlobalNS.AddOnceEventDispatch);
        self.mId2DispatchDic:add(cmdId, disp);
    end

    self.mId2DispatchDic:value(cmdId):addEventHandle(pThis, func, eventId);
end

function M:removeCmdHandle(cmdId, pThis, func, eventId)
    if(not self.mId2DispatchDic.ContainsKey(cmdId)) then
        GCtx.mLogSys:log("Cmd Handle Not Register");
    end

    self.mId2DispatchDic[cmdId]:removeEventHandle(pThis, func, eventId);
end

function M:handleMsg(msg)
    --local byCmd = msg.mByCmd;
    --byCmd = msg.readUnsignedInt8(byCmd);
    --local byParam = msg.mByParam;
    --byParam = msg.readUnsignedInt8(byParam);
    --msg.setPos(0);
    GCtx.mLogSys:log("NetModuleDispatchHandle Start handleMsg", GlobalNS.LogTypeId.eLogCommon);
	
    if(self.mId2DispatchDic:containsKey(msg.byCmd)) then
        GCtx.mLogSys:log("NetModuleDispatchHandle In handleMsg", GlobalNS.LogTypeId.eLogCommon);
        --self.mCmdDispInfo.bu = msg.mMsgBody;
        --self.mCmdDispInfo.byCmd = byCmd;
        --self.mCmdDispInfo.byParam = byParam;
        self.mId2DispatchDic:value(msg.byCmd):dispatchEvent(msg);
    else
        
    end
end

return M;