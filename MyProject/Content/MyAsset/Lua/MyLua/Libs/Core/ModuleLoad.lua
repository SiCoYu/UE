-- 模块导入，这个添加到全局表 _G 里面，因为这样才能保证自己的代码使用肯定正确
function MLoader(path)
	path = (string.gsub(path, "%.", "/")); 	-- 替换点(.)成斜杠(/)，(string.gsub(path, '%.', '/')); 这样替换是替换字符，是错误的
	
    local M = require(path);
	
	if(false == M) then
		error(string.format("Error %s load failed", tostring(path)));
	end
	
	return M;
end

function MUnload(path)
    path = (string.gsub(path, "%.", "/"));
    package.loaded[path] = nil;
end

function MReload(path)
    MUnload(path);
    return MLoader(path);
end

--[[
--http://lua-users.org/wiki/LuaModulesLoader
module(..., package.seeall)

local function load(modulename)
	local errmsg = ""
	-- Find source
	local modulepath = string.gsub(modulename, "%.", "/")
	for path in string.gmatch(package.path, "([^;]+)") do
		local filename = string.gsub(path, "%?", modulepath)
		local file = io.open(filename, "rb")
		if file then
			-- Compile and return the module
			return assert(loadstring(assert(file:read("*a")), filename))
		end
		errmsg = errmsg.."\n\tno file '"..filename.."' (checked with custom loader)"
	end
	return errmsg
end

-- Install the loader so that it's called just before the normal Lua loader
table.insert(package.loaders, 2, load)
]]