local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "NetCmdDispatchHandle_KBE";
GlobalNS[M.clsName] = M;

function M:ctor()
    self.mId2HandleDic = GlobalNS.new(GlobalNS.MDictionary);
end

function M:addParamHandle(paramId, pThis, func)
    if(not self.mId2HandleDic:containsKey(paramId)) then
        local disp = GlobalNS.new(GlobalNS.AddOnceEventDispatch);
        self.mId2HandleDic:add(paramId, disp);
    else
        Ctx.mLogSys:log("Msg Id Already Register paramId = " .. paramId, GlobalNS.LogTypeId.eLogCommon);
    end

    self.mId2HandleDic:value(paramId):addEventHandle(pThis, func, 0);
end

function M:removeParamHandle(paramId, pThis, func)
    if(self.mId2HandleDic.ContainsKey(paramId)) then
        self.mId2HandleDic:value(paramId):removeEventHandle(pThis, func, 0);
    else
        Ctx.mLogSys.log("ParamId not Register", GlobalNS.LogTypeId.eLogCommon);
    end
end

function M:handleMsg(msgName, msg)
    --Ctx.mLogSys:log("NetCmdDispatchHandle_KBE Start handleMsg " .. msgName, GlobalNS.LogTypeId.eLogCommon);
    if(self.mId2HandleDic:containsKey(msgName)) then
        --Ctx.mLogSys:log("NetCmdDispatchHandle_KBE in handleMsg " .. msgName, GlobalNS.LogTypeId.eLogCommon);
        self.mId2HandleDic:value(msgName):dispatchEvent(msg);
    else
        
    end
end

return M;