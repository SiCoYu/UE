namespace SDK.Lib
{
    /**
     * @brief 定时器，这个是不断增长的
     */
    public class TimerItemBase : GObject, IDispatchObject, INoOrPriorityObject
    {
        public float mInternal;        // 定时器间隔
        public float mTotalTime;       // 总共定时器时间
        public float mCurRunTime;      // 当前定时器运行的时间
        public float mCurCallTime;     // 当前定时器已经调用的时间
        public bool mIsInfineLoop;      // 是否是无限循环
        public float mIntervalLeftTime; // 定时器调用间隔剩余时间
        public TimerFunctionObject mTimerDispatch;       // 定时器分发
        public bool mIsDisposed;             // 是否已经被释放
        public bool mIsContinuous;         // 是否是连续的定时器

        public TimerItemBase()
        {
            this.mInternal = 1;
            this.mTotalTime = 1;
            this.mCurRunTime = 0;
            this.mCurCallTime = 0;
            this.mIsInfineLoop = false;
            this.mIntervalLeftTime = 0;
            this.mTimerDispatch = new TimerFunctionObject();
            this.mIsDisposed = false;
            this.mIsContinuous = false;
        }

        public void setFuncObject(ICalleeObject pThis, MEventDispatchAction<TimerItemBase> handle)
        {
            this.mTimerDispatch.setFuncObject(pThis, handle, 0);
        }

        virtual public void setTotalTime(float value)
        {
            this.mTotalTime = value;
        }

        virtual public float getRunTime()
        {
            return this.mCurRunTime;
        }

        virtual public float getCallTime()
        {
            return this.mCurCallTime;
        }

        virtual public float getLeftRunTime()
        {
            return this.mTotalTime - this.mCurRunTime;
        }

        virtual public float getLeftCallTime()
        {
            return this.mTotalTime - this.mCurCallTime;
        }

        // 在调用回调函数之前处理
        protected virtual void onPreCallBack()
        {

        }

        public virtual void OnTimer(float delta)
        {
            if (this.mIsDisposed)
            {
                return;
            }

            this.mCurRunTime += delta;

            if (this.mCurRunTime > this.mTotalTime)
            {
                this.mCurRunTime = this.mTotalTime;
            }
            this.mIntervalLeftTime += delta;

            if (this.mIsInfineLoop)
            {
                this.checkAndDispatch();
            }
            else
            {
                if (this.mCurRunTime >= this.mTotalTime)
                {
                    this.disposeAndDispatch();
                }
                else
                {
                    this.checkAndDispatch();
                }
            }
        }

        public virtual void disposeAndDispatch()
        {
            if (this.mIsContinuous)
            {
                this.continueDisposeAndDispatch();
            }
            else
            {
                this.discontinueDisposeAndDispatch();
            }
        }

        protected void continueDisposeAndDispatch()
        {
            this.mIsDisposed = true;

            while (this.mIntervalLeftTime >= this.mInternal && this.mCurCallTime < this.mTotalTime)
            {
                this.mCurCallTime = this.mCurCallTime + this.mInternal;
                this.mIntervalLeftTime = this.mIntervalLeftTime - this.mInternal;
                this.onPreCallBack();

                if (this.mTimerDispatch.isValid())
                {
                    this.mTimerDispatch.call(this);
                }
            }
        }

        protected void discontinueDisposeAndDispatch()
        {
            this.mIsDisposed = true;
            this.mCurCallTime = this.mTotalTime;
            this.onPreCallBack();

            if (this.mTimerDispatch.isValid())
            {
                this.mTimerDispatch.call(this);
            }
        }

        public virtual void checkAndDispatch()
        {
            if(this.mIsContinuous)
            {
                this.continueCheckAndDispatch();
            }
            else
            {
                this.discontinueCheckAndDispatch();
            }
        }

        // 连续的定时器
        protected void continueCheckAndDispatch()
        {
            while (this.mIntervalLeftTime >= this.mInternal)
            {
                // 这个地方 m_curCallTime 肯定会小于 m_totalTime，因为在调用这个函数的外部已经进行了判断
                this.mCurCallTime = this.mCurCallTime + this.mInternal;
                this.mIntervalLeftTime = this.mIntervalLeftTime - this.mInternal;
                this.onPreCallBack();

                if (this.mTimerDispatch.isValid())
                {
                    this.mTimerDispatch.call(this);
                }
            }
        }

        // 不连续的定时器
        protected void discontinueCheckAndDispatch()
        {
            if (this.mIntervalLeftTime >= this.mInternal)
            {
                // 这个地方 m_curCallTime 肯定会小于 m_totalTime，因为在调用这个函数的外部已经进行了判断
                this.mCurCallTime = this.mCurCallTime + (((int)(this.mIntervalLeftTime / this.mInternal)) * this.mInternal);
                this.mIntervalLeftTime = this.mIntervalLeftTime % this.mInternal;   // 只保留余数
                this.onPreCallBack();

                if (this.mTimerDispatch.isValid())
                {
                    this.mTimerDispatch.call(this);
                }
            }
        }

        public virtual void reset()
        {
            this.mCurRunTime = 0;
            this.mCurCallTime = 0;
            this.mIntervalLeftTime = 0;
            this.mIsDisposed = false;
        }

        public void startTimer()
        {
            Ctx.msInstance.mTimerMgr.addTimer(this);
        }

        public void stopTimer()
        {
            Ctx.msInstance.mTimerMgr.removeTimer(this);
        }
    }
}