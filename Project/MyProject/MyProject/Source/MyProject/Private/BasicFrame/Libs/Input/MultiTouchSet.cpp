namespace SDK.Lib
{
    /**
     * @brief 触碰集合
     */
    public class MultiTouchSet : IDispatchObject
    {
        protected MList<MMouseOrTouch> mTouchList;

        public MultiTouchSet()
        {
            this.mTouchList = new MList<MMouseOrTouch>();
        }

        public void reset()
        {
            this.mTouchList.clear();
        }

        public void addTouch(MMouseOrTouch touch)
        {
            this.mTouchList.add(touch);
        }

        public void onTick(float delta, TickMode tickMode)
        {
            bool isTouchBegan = false;
            bool isMove = false;
            bool isStationary = false;
            bool isEnd = false;

            MMouseOrTouch touch = null;

            int idx = 0;
            int len = this.mTouchList.count();

            while (idx < len)
            {
                touch = this.mTouchList[idx];
                if(touch.mTouchBegan)
                {
                    isTouchBegan = true;
                }
                else if(touch.mTouchEnd)
                {
                    isEnd = true;
                }
                else if(touch.isPosChanged())
                {
                    isMove = true;
                    break;
                }
                else
                {
                    isStationary = true;
                }
                ++idx;
            }

            // 暂时只支持多触碰移动
            if(isMove)
            {
                Ctx.msInstance.mInputMgr.handleMultiTouchMoved(this);
            }
        }
    }
}