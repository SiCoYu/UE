MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "Form";
GlobalNS[M.clsName] = M;

function M:ctor(...)
    self.mGuiWin = nil;        -- 自己的 GameObject 根节点
    self.mId = 0;              -- 自己的 Id
    self.mIsExit = true;        -- 点击返回按钮的时候退出还是隐藏
    self.mIsReady = false;      -- 是否 onReady 函数被调用
    self.mIsVisible = false;    -- 是否可见
    self.mParam = ...;          -- 参数值，当前只能传递一个参数进来，尽量使用表传递进来所有需要的参数
	--self.mWillVisible = false; 	-- 是否是调用显示接口，但是资源还没有加载完成
	self.mHideOnCreate = false; -- 是否创建之后隐藏
end

function M:dtor()

end

-- 加载完成是否立刻显示，如果不是立刻显示，就需要自己再次手工调用 show 函数才行
function M:isHideOnCreate()
    return self.mHideOnCreate;
end

-- 加载
function M:load()

end

-- 显示
function M:show()
    GCtx.mUiMgr:showForm(self.mId);
end

-- 加载并显示
function M:loadAndShow(param)
    GCtx.mUiMgr:loadAndShow(self.mId, param);
end

-- 隐藏
function M:hide()
    GCtx.mUiMgr:hideForm(self.mId); 
end

-- 退出
function M:exit()
    GCtx.mUiMgr:exitForm(self.mId);
end

-- 界面代码创建后就调用
function M:onInit()
    
end

-- 第一次显示之前会调用一次
function M:onReady()
    self.mIsReady = true;
end

-- 每一次显示都会调用一次
function M:onShow()
    self.mIsVisible = true;
end

-- 每一次隐藏都会调用一次
function M:onHide()
    self.mIsVisible = false;
end

-- 每一次关闭都会调用一次
function M:onExit()
    self.mIsReady = false;
	self.mIsVisible = false;
end

function M:isReady()
    return self.mIsReady;
end

function M:isVisible()
    return self.mIsVisible;
end

function M:onCloseBtnClk()
    if(self:isVisible()) then
        if(self.mIsExit) then
            self:exit();
        else
            self:hide();
        end
    end
end

return M;