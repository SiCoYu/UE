MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");

-- CS 中的绑定
local M = GlobalNS.StaticClass();
M.clsName = "CSSystem";
GlobalNS[M.clsName] = M;
local this = M;

function M.init()
    this.Ctx = SDK.Lib.Ctx;
    this.UtilPath = SDK.Lib.UtilPath;
    this.GlobalEventCmd = SDK.Lib.GlobalEventCmd;
    this.AuxPrefabLoader = SDK.Lib.AuxPrefabLoader;
	this.AuxBytesLoader = SDK.Lib.AuxBytesLoader;
	this.UtilApi = SDK.Lib.UtilApi;
	this.MFileSys = SDK.Lib.MFileSys;
	this.EEndian = SDK.Lib.EEndian;
	this.GkEncode = SDK.Lib.GkEncode;
    this.ModuleId = SDK.Lib.ModuleId;
end

--[[
function M.setNeedUpdate(value)
    
end
]]

-- LogSys 日志区域
function M.log(message, logTypeId)
    if(this.Ctx.mInstance.mLogSys ~= nil) then
        if(logTypeId == nil) then
            GlobalNS.UtilApi.error("CSSystem logTypeId is nil");
        else
            this.Ctx.mInstance.mLogSys:lua_log(message, logTypeId);
        end
    else
        GlobalNS.UtilApi.error("CSSystem LogSys is nil");
    end
end

function M.warn(message, logTypeId)
    this.Ctx.mInstance.mLogSys:lua_warn(message, logTypeId);
end

function M.error(message, logTypeId)
    this.Ctx.mInstance.mLogSys:lua_error(message, logTypeId);
end

-- GlobalEventCmd 交互区域
function M.onTestProtoBuf(msg)
    this.GlobalEventCmd.onTestProtoBuf(msg);
end

function M.onTestProtoBufBuffer(commandID, buffer)
    this.GlobalEventCmd.onTestProtoBufBuffer(commandID, buffer);
end

-- 网络区域
function M.sendFromLua(id, buffer)
    this.Ctx.mInstance.mLuaSystem:sendFromLua(id, buffer);
end

function M.sendFromLuaRpc(buffer)
    this.Ctx.mInstance.mLuaSystem:sendFromLuaRpc(buffer);
end

function M.readLuaBufferToFile(file)
    return this.MFileSys.readLuaBufferToFile(file);
end

-- UtilApi 接口
function M.addEventHandleByPath(go, path, luaTable, luaFunction)
    this.UtilApi.addEventHandle(go, path, luaTable, luaFunction);
end

function M.addEventHandleSelf(go, luaTable, luaFunction)
    this.UtilApi.addEventHandle(go, luaTable, luaFunction, false);
end

function M.GoFindChildByName(name)
    return this.UtilApi.GoFindChildByName(name);
end

function M.TransFindChildByPObjAndPath(pObject, path)
    return this.UtilApi.TransFindChildByPObjAndPath(pObject, path);
end

function M.SetParent(child, parent, worldPositionStays)
    this.UtilApi.SetParent(child, parent, worldPositionStays);
end

function M.SetRectTransformParent(child, parent, worldPositionStays)
    this.UtilApi.SetRectTransParent(child, parent, worldPositionStays);
end

function M.buildByteBuffer()
	return this.Ctx.mInstance.mFactoryBuild:buildByteBuffer();
end

--进行分裂
function M.startSplit()
	this.Ctx.mInstance.mPlayerMgr:startSplit();
end

--吐一个小球
function M.emitSnowBlock()
	this.Ctx.mInstance.mPlayerMgr:emitSnowBlock();
end

return M;