--[[
	@file Prequisites.lua
]]
-- 所有全局类都在这里加载
MLoader("MyLua.Libs.Core.GlobalNS");      -- 加载自己的全局表

-- 基础
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.StaticClass");
MLoader("MyLua.Libs.Core.GObject");
MLoader("MyLua.Libs.Core.ClassLoader");
MLoader("MyLua.Libs.Core.MemoryMalloc");
MLoader("MyLua.Libs.Core.UniqueNumIdGen");
--MLoader("MyLua.Libs.Core.CSImportToLua");

--MLoader("MyLua.Libs.FrameWork.MacroDef");

-- 数据结构
MLoader("MyLua.Libs.DataStruct.MList");
MLoader("MyLua.Libs.DataStruct.MDictionary");
MLoader("MyLua.Libs.DataStruct.NoOrPriorityList.INoOrPriorityList");
MLoader("MyLua.Libs.DataStruct.NoOrPriorityList.INoOrPriorityObject");
MLoader("MyLua.Libs.DataStruct.NoOrPriorityList.PriorityList.PrioritySort");
MLoader("MyLua.Libs.DataStruct.NoOrPriorityList.PriorityList.PriorityProcessObject");
MLoader("MyLua.Libs.DataStruct.NoOrPriorityList.PriorityList.PriorityList");
MLoader("MyLua.Libs.DataStruct.NoOrPriorityList.NoPriorityList.NoPriorityList");

-- Functor
MLoader("MyLua.Libs.Functor.CallFuncObjectBase");
MLoader("MyLua.Libs.Functor.CmpFuncObject");
MLoader("MyLua.Libs.Functor.CallFuncObjectFixParam");
MLoader("MyLua.Libs.Functor.CallFuncObjectVarParam");
MLoader("MyLua.Libs.Functor.PCallFuncObjectFixParam");
MLoader("MyLua.Libs.Functor.PCallFuncObjectVarParam");

-- 延迟处理器
MLoader("MyLua.Libs.DelayHandle.IDelayHandleItem");
MLoader("MyLua.Libs.DelayHandle.DelayNoOrPriorityHandleMgrBase");
MLoader("MyLua.Libs.DelayHandle.DelayNoOrPriorityHandleMgr");
MLoader("MyLua.Libs.DelayHandle.DelayNoPriorityHandleMgrBase");
MLoader("MyLua.Libs.DelayHandle.DelayNoPriorityHandleMgr");
MLoader("MyLua.Libs.DelayHandle.DelayPriorityHandleMgrBase");
MLoader("MyLua.Libs.DelayHandle.DelayPriorityHandleMgr");


-- 事件分发器
MLoader("MyLua.Libs.EventHandle.EventDispatchFunctionObject");
MLoader("MyLua.Libs.EventHandle.IDispatchObject");
MLoader("MyLua.Libs.EventHandle.EventDispatch");
MLoader("MyLua.Libs.EventHandle.EventDispatchGroup");
MLoader("MyLua.Libs.EventHandle.AddOnceAndCallOnceEventDispatch");
MLoader("MyLua.Libs.EventHandle.AddOnceEventDispatch");
MLoader("MyLua.Libs.EventHandle.CallOnceEventDispatch");
MLoader("MyLua.Libs.EventHandle.ResEventDispatch");


-- 帧处理事件
MLoader("MyLua.Libs.FrameHandle.TickMode");
MLoader("MyLua.Libs.FrameHandle.ITickedObject");
MLoader("MyLua.Libs.FrameHandle.TimerItemBase");
MLoader("MyLua.Libs.FrameHandle.TickItemBase");
MLoader("MyLua.Libs.FrameHandle.FrameTimerItem");
MLoader("MyLua.Libs.FrameHandle.DaoJiShiTimer");
MLoader("MyLua.Libs.FrameHandle.SystemTimeData");
MLoader("MyLua.Libs.FrameHandle.SystemFrameData");
MLoader("MyLua.Libs.FrameHandle.TickObjectNoPriorityMgr");
MLoader("MyLua.Libs.FrameHandle.TickObjectPriorityMgr");
MLoader("MyLua.Libs.FrameHandle.TimerMgr");
MLoader("MyLua.Libs.FrameHandle.FrameTimerMgr");
MLoader("MyLua.Libs.FrameHandle.TickMgr");
MLoader("MyLua.Libs.FrameHandle.TimerFunctionObject");
MLoader("MyLua.Libs.FrameHandle.FrameUpdateStatistics");
MLoader("MyLua.Libs.FrameHandle.LoopDepth");

-- UI
MLoader("MyLua.Libs.Ui.Base.FormMode");
MLoader("MyLua.Libs.Ui.Base.UiFormId");
MLoader("MyLua.Libs.Ui.Base.UiLayer");
MLoader("MyLua.Libs.Ui.Base.UiCanvas");
MLoader("MyLua.Libs.Ui.Base.Form");
MLoader("MyLua.Libs.Ui.Base.UiAttrSystem");
MLoader("MyLua.Libs.Ui.Base.UiMgr");

-- 组件类型
MLoader("MyLua.Libs.Ui.Base.ComponentStyle.LabelStyleID");
MLoader("MyLua.Libs.Ui.Base.ComponentStyle.BtnStyleID");
MLoader("MyLua.Libs.Ui.Base.ComponentStyle.WidgetStyleID");
MLoader("MyLua.Libs.Ui.Base.ComponentStyle.WidgetStyle");
MLoader("MyLua.Libs.Ui.Base.ComponentStyle.LabelStyleBase");
MLoader("MyLua.Libs.Ui.Base.ComponentStyle.ButtonStyleBase");
MLoader("MyLua.Libs.Ui.Base.ComponentStyle.WidgetStyleMgr");

-- Aux 组件
MLoader("MyLua.Libs.Auxiliary.AuxComponent");
MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxWindow");
MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");
MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxInputField");
MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxLabel");
MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxImage");

MLoader("MyLua.Libs.Auxiliary.AuxLoader.AuxLoaderBase");
MLoader("MyLua.Libs.Auxiliary.AuxLoader.AuxPrefabLoader");
MLoader("MyLua.Libs.Auxiliary.AuxLoader.AuxUiPrefabLoader");
MLoader("MyLua.Libs.Auxiliary.AuxLoader.AuxBytesLoader");
MLoader("MyLua.Libs.Auxiliary.AuxLoader.AuxSpriteAtlasLoader");
MLoader("MyLua.Libs.Auxiliary.AuxLoader.AuxTextureLoader");
MLoader("MyLua.Libs.Auxiliary.AuxLoader.AuxTextLoader");
MLoader("MyLua.Libs.Auxiliary.AuxLoader.AuxLevelLoader");
MLoader("MyLua.Libs.Auxiliary.AuxLoader.AuxDownloader");

-- FrameWork 脚本
MLoader("MyLua.Libs.FrameWork.ProcessSys");
MLoader("MyLua.Libs.FrameWork.CSSystem");
MLoader("MyLua.Libs.FrameWork.Config");
MLoader("MyLua.Libs.FrameWork.Layer.LayerPath");

-- 工具
MLoader("MyLua.Libs.Tools.MEndian");
MLoader("MyLua.Libs.Tools.MEncode");
MLoader("MyLua.Libs.Tools.UtilStr");
MLoader("MyLua.Libs.Tools.UtilApi");
MLoader("MyLua.Libs.Tools.UtilPath");
MLoader("MyLua.Libs.Tools.UtilMath");
MLoader("MyLua.Libs.Tools.UtilSysLibWrap");

-- 日志
MLoader("MyLua.Libs.Log.LogTypeId");
MLoader("MyLua.Libs.Log.LogSys");

-- 网络
MLoader("MyLua.Libs.Network.CmdDispatch.NetCmdDispatchHandle");
MLoader("MyLua.Libs.Network.CmdDispatch.NetCmdDispatchHandle_KBE");
MLoader("MyLua.Libs.Network.CmdDispatch.NetModuleDispatchHandle");
MLoader("MyLua.Libs.Network.CmdDispatch.NetCmdNotify");
MLoader("MyLua.Libs.Network.CmdDispatch.CmdDispatchInfo");

MLoader("MyLua.Libs.Network.PBFileList");
MLoader("MyLua.Libs.Network.NetCommand");
MLoader("MyLua.Libs.Network.NetMgr");
MLoader("MyLua.Libs.Tools.UtilMsg");

-- 资源系统
MLoader("MyLua.Libs.Resource.ResLoadData.ResPathType");

-- 表系统
MLoader("MyLua.Libs.Table.TableId");

MLoader("MyLua.Libs.Table.TableItemBodyBase");

MLoader("MyLua.Libs.Table.ItemObject.TableCard");
MLoader("MyLua.Libs.Table.ItemObject.TableJob");
MLoader("MyLua.Libs.Table.ItemObject.TableObject");
MLoader("MyLua.Libs.Table.ItemObject.TableRace");
MLoader("MyLua.Libs.Table.ItemObject.TableSkill");
MLoader("MyLua.Libs.Table.ItemObject.TableSpriteAni");
MLoader("MyLua.Libs.Table.ItemObject.TableState");

MLoader("MyLua.Libs.Table.TableItemHeader");
MLoader("MyLua.Libs.Table.TableItemBase");
MLoader("MyLua.Libs.Table.TableBase");

MLoader("MyLua.Libs.Table.UtilTable");
MLoader("MyLua.Libs.Table.TableSys");

-- ObjectPool
--MLoader("MyLua.Libs.ObjectPool.StrIdPoolSys");
--MLoader("MyLua.Libs.ObjectPool.NumIdPoolSys");