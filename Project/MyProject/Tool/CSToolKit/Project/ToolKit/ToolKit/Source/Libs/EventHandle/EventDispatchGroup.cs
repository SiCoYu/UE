namespace SDK.Lib
{
    public class EventDispatchGroup
    {
        protected EventDispatchTypeId mEventDispatchTypeId; // 创建的类型 Id
        protected MDictionary<int, EventDispatch> mGroupId2DispatchDic;
        protected LoopDepth mLoopDepth;       // 是否是在循环遍历中

        public EventDispatchGroup()
        {
            this.mEventDispatchTypeId = EventDispatchTypeId.eAddOnceEventDispatch;
            this.mGroupId2DispatchDic = new MDictionary<int, EventDispatch>();
            this.mLoopDepth = new LoopDepth();
        }

        public void setEventDispatchTypeId(EventDispatchTypeId value)
        {
            this.mEventDispatchTypeId = value;
        }

        // 添加分发器
        public void addEventDispatch(int groupID, EventDispatch disp)
        {
            if (!this.mGroupId2DispatchDic.containsKey(groupID))
            {
                this.mGroupId2DispatchDic[groupID] = disp;
            }
        }

        public void addEventHandle(int groupID, ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle, uint eventId)
        {
            // 如果没有就创建一个
            if (!this.mGroupId2DispatchDic.containsKey(groupID))
            {
                EventDispatch tmp = null;

                if (EventDispatchTypeId.eEventDispatch == this.mEventDispatchTypeId)
                {
                    tmp = new EventDispatch();
                }
                else if (EventDispatchTypeId.eAddOnceEventDispatch == this.mEventDispatchTypeId)
                {
                    tmp = new AddOnceEventDispatch();
                }

                this.addEventDispatch(groupID, tmp);
            }

            this.mGroupId2DispatchDic[groupID].addEventHandle(pThis, handle, eventId);
        }

        public void removeEventHandle(int groupID, ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle, uint eventId)
        {
            if (this.mGroupId2DispatchDic.containsKey(groupID))
            {
                this.mGroupId2DispatchDic[groupID].removeEventHandle(pThis, handle, eventId);

                // 如果已经没有了
                if (!this.mGroupId2DispatchDic[groupID].hasEventHandle())
                {
                    this.mGroupId2DispatchDic.remove(groupID);
                }
            }
            else
            {
             
            }
        }

        public void dispatchEvent(int groupID, IDispatchObject dispatchObject)
        {
            this.mLoopDepth._incDepth();

            if (this.mGroupId2DispatchDic.containsKey(groupID))
            {
                this.mGroupId2DispatchDic[groupID].dispatchEvent(dispatchObject);
            }
            else
            {
             
            }

            this.mLoopDepth._decDepth();
        }

        public void clearAllEventHandle()
        {
            if (!this.mLoopDepth._isInDepth())
            {
                foreach (EventDispatch dispatch in this.mGroupId2DispatchDic.values)
                {
                    dispatch.clearEventHandle();
                }

                this.mGroupId2DispatchDic.clear();
            }
            else
            {
            
            }
        }

        public void clearGroupEventHandle(int groupID)
        {
            if (!this.mLoopDepth._isInDepth())
            {
                if (this.mGroupId2DispatchDic.containsKey(groupID))
                {
                    this.mGroupId2DispatchDic[groupID].clearEventHandle();
                    this.mGroupId2DispatchDic.remove(groupID);
                }
                else
                {
                 
                }
            }
            else
            {
             
            }
        }

        public bool hasEventHandle(int groupID)
        {
            if(this.mGroupId2DispatchDic.containsKey(groupID))
            {
                return this.mGroupId2DispatchDic[groupID].hasEventHandle();
            }

            return false;
        }
    }
}