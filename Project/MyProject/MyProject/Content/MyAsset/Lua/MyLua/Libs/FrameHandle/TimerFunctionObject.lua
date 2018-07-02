MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "TimerFunctionObject";
GlobalNS[M.clsName] = M;

function M:ctor()
    self.mHandle = nil;
    self.mThis = nil;
    self.mParam = nil;
	self.mEventId = 0;
end

function M:dtor()

end

function M:setPThisAndHandle(pThis, handle, eventId)
    self.mThis = pThis;
    self.mHandle = handle;
	self.mEventId = eventId;
end

function M:clear()
    self.mHandle = nil;
    self.mThis = nil;
	self.mEventId = 0;
end

function M:isValid()
    if(nil ~= self.mThis and nil ~= self.mHandle) then
        return true;
    elseif(nil ~= self.mHandle) then
        return true;
    else
        return false;
    end
end

function M:call(param)
    self.mParam = param;

    if(nil ~= self.mThis and nil ~= self.mHandle) then
        return self.mHandle(self.mThis, self.mParam, self.mEventId);
    elseif(nil ~= self.mHandle) then
        return self.mHandle(self.mParam, self.mEventId);
    else
        return 0;
    end
end

return M;