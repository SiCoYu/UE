MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");

--[[
 * @brief 缓冲对象工厂
]]

local M = GlobalNS.StaticClass();
M.clsName = "NumIdBufferObjectFactory";
GlobalNS[M.clsName] = M;

-- 新创建一个对象
function M.newObject(clsT, bufferType, isUsePool)
	--isUsePool = false;
	
	if(nil == isUsePool) then
		isUsePool = true;
	end

	local ret = nil;

	if(isUsePool) then
		ret = M.getObject(bufferType);
	end

	if(nil == ret) then
		ret = GlobalNS.new(clsT);
	end

	ret:setIsUsePool(isUsePool);

	return ret;
end

function M.deleteObject(obj)
	if(nil ~= obj) then
		if(obj:isUsePool()) then
			Ctx.mObjectNumIdPoolSys:returnObject(obj:getBufferType(), obj);
			obj:putInPool();
		else
			obj:dispose();
		end
	end
end

function M.getObject(bufferType)
	local ret = nil;
	ret = Ctx.mObjectNumIdPoolSys:getObject(bufferType);

	if(nil ~= ret) then
		ret:getFromPool();
	end

	return ret;
end

return M;