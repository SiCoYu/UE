MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "MDebug";
GlobalNS[M.clsName] = M;

function M.traceback(thread, message, level)
    if(nil == level) then
        level = 1;
    end
	
    if(nil ~= thread) then
        message = debug.traceback(thread, message, level);
    else
        message = debug.traceback(message, level);
    end
	
    error(message, 2);
end

return M;