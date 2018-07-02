MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");

--[[
	@brief 缓冲对象类型，缓冲池通过这个去区别类型
]]
 
local M = GlobalNS.StaticClass();
M.clsName = "BufferType";
GlobalNS[M.clsName] = M;

M.eBT_None = 0,       -- 无效的缓冲区类型
M.eBT_SoundClipItem = 1,
M.eBT_SoundPrefabItem = 2,
M.eBT_InfoBoxParam = 3,
M.eBT_SoundParam = 4,

M.eBT_LoadParam = 5,
M.eBT_MsgRouteBase = 6,
M.eBT_CanvasGroupAlphaAnim = 7,
M.eBT_PriorityProcessObject = 8,

return M;