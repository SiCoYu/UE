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
	this.AuxSpriteAtlasLoader = SDK.Lib.AuxSpriteAtlasLoader;
	this.UtilApi = SDK.Lib.UtilApi;
	this.MFileSys = SDK.Lib.MFileSys;
	this.MEndian = SDK.Lib.MEndian;
	this.MEncode = SDK.Lib.MEncode;
    this.ModuleId = SDK.Lib.ModuleId;
end

-- 需要从外部更新 Lua 系统
function M.setNeedUpdateFromExternal(value)
    this.Ctx.msInstance.mLuaSystem:setNeedUpdateLua(value);
end

-- LogSys 日志区域
function M.log(message, logTypeId)
    if(this.Ctx.msInstance.mLogSys ~= nil) then
        if(logTypeId == nil) then
            GlobalNS.UtilApi.error("CSSystem logTypeId is nil");
        else
            this.Ctx.msInstance.mLogSys:lua_log(message, logTypeId);
        end
    else
        GlobalNS.UtilApi.error("CSSystem LogSys is nil");
    end
end

function M.warn(message, logTypeId)
    this.Ctx.msInstance.mLogSys:lua_warn(message, logTypeId);
end

function M.error(message, logTypeId)
    this.Ctx.msInstance.mLogSys:lua_error(message, logTypeId);
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
    this.Ctx.msInstance.mLuaSystem:sendFromLua(id, buffer);
end

function M.sendFromLuaRpc(buffer)
    this.Ctx.msInstance.mLuaSystem:sendFromLuaRpc(buffer);
end

function M.readLuaBufferToFile(file)
    return this.MFileSys.readLuaBufferToFile(file);
end

-- UtilApi 接口
function M.addEventHandleByPath(go, path, luaTable, luaFunction)
    this.UtilApi.addEventHandle(go, path, luaTable, luaFunction);
end

function M.addEventHandleSelf(go, luaTable, luaFunction)
    this.UtilApi.addEventHandle(go, luaTable, luaFunction, 0, false);
end

function M.addButtonDownEventHandle(go, luaTable, luaFunction)
    this.UtilApi.addButtonDownEventHandle(go, luaTable, luaFunction, 0);
end

function M.addButtonUpEventHandle(go, luaTable, luaFunction)
    this.UtilApi.addButtonUpEventHandle(go, luaTable, luaFunction, 0);
end

function M.addButtonExitEventHandle(go, luaTable, luaFunction)
    this.UtilApi.addButtonExitEventHandle(go, luaTable, luaFunction, 0);
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

function M.addToggleHandle(go, table, method)
    this.UtilApi.addToggleHandle(go, table, method);
end

function M.buildByteBuffer()
	return this.Ctx.msInstance.mFactoryBuild:buildByteBuffer();
end

--进行分裂
function M.startSplit()
	this.Ctx.msInstance.mPlayerMgr:startSplit();
end

--吐一个小球
function M.Fire()
	this.Ctx.msInstance.mPlayerMgr:FireInTheHole();
end

function M.startEmitSnowBlock()
	this.Ctx.msInstance.mPlayerMgr:startEmitSnowBlock();
end

function M.stopEmitSnowBlock()
	this.Ctx.msInstance.mPlayerMgr:stopEmitSnowBlock();
end

--设置 Lua 初始化完成
function M.setLuaInited(value)
	this.Ctx.msInstance.mLuaSystem:setLuaInited(value);
end

return M;