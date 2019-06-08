namespace SDK.Lib
{
    /**
     * @brief 事件分发，之分发一类事件，不同类型的事件使用不同的事件分发
     * @brief 注意，事件分发缺点就是，可能被调用的对象已经释放，但是没有清掉事件处理器，结果造成空指针
     * @brief 事件添加一个事件 Id ，这个主要是事件分发使用，资源加载那边基本都没有使用这个事件 Id，因为 java7 不支持函数指针，只能传递 java 对象
     */
    public class EventDispatch : DelayPriorityHandleMgrBase
    {
        protected uint mEventId;
        protected MList<EventDispatchFunctionObject> mHandleList;
        //protected int mDebugUniqueId;       // 唯一 Id ，调试使用

        public EventDispatch(uint eventId_ = 0)
        {
            this.mEventId = eventId_;
            this.mHandleList = new MList<EventDispatchFunctionObject>();
        }

        override public void init()
        {
            base.init();
        }

        override public void dispose()
        {
            if (null != this.mHandleList)
            {
                this.clearEventHandle();
                this.mHandleList = null;
            }

            base.dispose();
        }

        protected MList<EventDispatchFunctionObject> handleList
        {
            get
            {
                return this.mHandleList;
            }
        }

        //public int getDebugUniqueId()
        //{
        //    return this.mDebugUniqueId;
        //}

        //public void setDebugUniqueId(int value)
        //{
        //    this.mDebugUniqueId = value;
        //    this.mHandleList.uniqueId = this.mDebugUniqueId;
        //}

        public void addDispatch(EventDispatchFunctionObject dispatch)
        {
            this._addObject(dispatch);
        }

        public void removeDispatch(EventDispatchFunctionObject dispatch)
        {
            this._removeObject(dispatch);
        }

        // 相同的函数只能增加一次，Lua ，Python 这些语言不支持同时存在几个相同名字的函数，只支持参数可以赋值，因此不单独提供同一个名字不同参数的接口了，但是 java 不支持参数默认值，只能通过重载实现参数默认值，真是悲剧中的悲剧， eventId: 分发事件上层唯一 Id，这样一个事件处理函数可以根据 EventId 处理不同的事件。可以添加一个事件处理的优先级，优先级大的放在前面，优先级小的，放在后面
        virtual public void addEventHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle, uint eventId = 0)
        {
            if (null != pThis || null != handle)
            {
                EventDispatchFunctionObject funcObject = new EventDispatchFunctionObject();

                if (null != handle)
                {
                    funcObject.setFuncObject(pThis, handle, eventId);
                }

                this.addDispatch(funcObject);
            }
            else
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log("EventDispatch::addEventHandle, error, addEventHandle failed", LogTypeId.eLogEventHandle);
                }
            }
        }

        public void removeEventHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle, uint eventId = 0)
        {
            int idx = 0;
            int elemLen = 0;
            elemLen = this.mHandleList.count();

            while (idx < elemLen)
            {
                if (this.mHandleList[idx].isEqual(pThis, handle, eventId))
                {
                    break;
                }

                idx += 1;
            }

            if (idx < this.mHandleList.count())
            {
                this.removeDispatch(this.mHandleList[idx]);
            }
            else
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log("EventDispatch::removeEventHandle, error, cannot find handle", LogTypeId.eLogEventHandle);
                }
            }
        }

        override protected void _addObject(IDelayHandleItem delayObject, float priority = 0.0f)
        {
            if (this._isInDepth())
            {
                base._addObject(delayObject, priority);
            }
            else
            {
                // 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
                this.mHandleList.add(delayObject as EventDispatchFunctionObject);
            }
        }

        override protected void _removeObject(IDelayHandleItem delayObject)
        {
            if (this._isInDepth())
            {
                base._removeObject(delayObject);
            }
            else
            {
                if (!this.mHandleList.remove(delayObject as EventDispatchFunctionObject))
                {
                    if (MacroDef.ENABLE_LOG)
                    {
                        Ctx.msInstance.mLogSys.log("EventDispatch::_removeObject, error, failed", LogTypeId.eLogEventHandle);
                    }
                }
            }
        }

        virtual public void dispatchEvent(IDispatchObject dispatchObject)
        {
            //try
            //{
            this._incDepth();

            //foreach (EventDispatchFunctionObject handle in this.mHandleList.list())

            int idx = 0;
            int len = this.mHandleList.count();
            EventDispatchFunctionObject handle = null;

            while (idx < len)
            {
                handle = this.mHandleList[idx];

                if (!handle.isClientDispose())
                {
                    handle.call(dispatchObject);
                }

                ++idx;
            }

            this._decDepth();
            //}
            //catch (Exception ex)
            //{
            //    Ctx.msInstance.mLogSys.catchLog(ex.ToString());
            //}
        }

        public void clearEventHandle()
        {
            if (this._isInDepth())
            {
                //foreach (EventDispatchFunctionObject item in this.mHandleList.list())
                if (null != this.mHandleList)
                {
                    int idx = 0;
                    int len = this.mHandleList.count();
                    EventDispatchFunctionObject item = null;

                    while (idx < len)
                    {
                        item = this.mHandleList[idx];

                        this.removeDispatch(item);

                        ++idx;
                    }
                }
            }
            else
            {
                if (null != this.mHandleList)
                {
                    this.mHandleList.clear();
                }
            }
        }

        // 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
        public bool isExistEventHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle, uint eventId)
        {
            bool isFinded = false;
            //foreach (EventDispatchFunctionObject item in this.mHandleList.list())
            int idx = 0;
            int len = this.mHandleList.count();
            EventDispatchFunctionObject item = null;

            while (idx < len)
            {
                item = this.mHandleList[idx];

                if (item.isEqual(pThis, handle, eventId))
                {
                    isFinded = true;
                    break;
                }

                ++idx;
            }

            return isFinded;
        }

        public void copyFrom(EventDispatch rhv)
        {
            //foreach(EventDispatchFunctionObject handle in rhv.handleList.list())
            int idx = 0;
            int len = this.mHandleList.count();
            EventDispatchFunctionObject handle = null;

            while (idx < len)
            {
                handle = this.mHandleList[idx];

                this.mHandleList.add(handle);

                ++idx;
            }
        }

        public bool hasEventHandle()
        {
            return this.mHandleList.count() > 0;
        }

        public int getEventHandleCount()
        {
            return this.mHandleList.count();
        }
    }
}