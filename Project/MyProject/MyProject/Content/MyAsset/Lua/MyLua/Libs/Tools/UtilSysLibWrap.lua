MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");

local M = GlobalNS.StaticClass();
local this = M;
M.clsName = "UtilSysLibWrap";
GlobalNS[M.clsName] = M;

--初始化系统库
function M.init()
	--[[
	@brief 关于lua5.2中table.getn方法不能用的代替方案
	@url https://blog.csdn.net/zhuoyuetec/article/details/22192855
	]]
	if(string.find(_VERSION, "5.3")) then
		table.getn = function (t)
			if(t.n) then
				return t.n;
			else
				local n = 0;
				
				for i in pairs(t) do
					if(type(i) == "number") then
						n = math.max(n, i);
					end
				end
				
				return n;
			end
		end
	end
end

M.init()

return M;