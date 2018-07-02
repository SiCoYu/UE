MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

MLoader("MyLua.Test.CSSystemTest.CSSystemTest");
MLoader("MyLua.Test.GlobalEventCmdTest.GlobalEventCmdTest");

MLoader("MyLua.Test.TestCmdDispatch.TestCmdDispatch");
MLoader("MyLua.Test.TestProtoBuf.TestProtoBuf");
MLoader("MyLua.Test.TestUI.TestUI");
MLoader("MyLua.Test.TestTable.TestTable");
MLoader("MyLua.Test.TestStr.TestStr");
MLoader("MyLua.Test.TestBufferPool.TestBufferPool");

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "TestMain";
GlobalNS[M.clsName] = M;

function M:ctor()
	self.mTestProtoBuf = GlobalNS.new(GlobalNS.TestProtoBuf);
	self.mTestCmdDispatch = GlobalNS.new(GlobalNS.TestCmdDispatch);
	self.mTestUI = GlobalNS.new(GlobalNS.TestUI);
	self.mTestTable = GlobalNS.new(GlobalNS.TestTable);
	self.mTestStr = GlobalNS.new(GlobalNS.TestStr);
	self.mTestBufferPool = GlobalNS.new(GlobalNS.TestBufferPool);
	
	self:init();
end

function M:init()
	GlobalNS.CSSystemTest.init();
end

function M:dtor()
	
end

function M:dispose()
	
end

function M:run()
	--self.mTestProtoBuf:run();
	--self.mTestCmdDispatch:run();
	--self.mTestUI:run();
	--self.mTestTable:run();
	--self.mTestStr:run();
	self.mTestBufferPool:run();
end

return M;