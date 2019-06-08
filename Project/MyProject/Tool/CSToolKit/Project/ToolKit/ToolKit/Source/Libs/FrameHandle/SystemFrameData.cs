namespace SDK.Lib
{
    public class SystemFrameData
    {
        protected uint mTotalFrameCount;       // 总帧数
        protected uint mCurFrameCount;         // 当前帧数
        protected float mCurTime;          // 当前一秒内时间
        protected int mFps;                // 帧率

        protected uint mLostFocusFrameCount;    // 失去焦点时候的帧数
        protected uint mGetFocusFrameCount;     // 获取焦点时候的帧数

        public SystemFrameData()
        {

        }

        public void init()
        {

        }

        public void dispose()
        {

        }

        public uint getTotalFrameCount()
        {
            return this.mTotalFrameCount;
        }

        public void nextFrame(float delta)
        {
            this.mTotalFrameCount += 1;
            this.mCurFrameCount += 1;
            this.mCurTime += delta;

            if(this.mCurTime > 1.0f)
            {
                this.mFps = (int)(this.mCurFrameCount / this.mCurTime);
                this.mCurFrameCount = 0;
                this.mCurTime = 0;
            }
        }

        public uint getGetFocusFrameCount()
        {
            return this.mGetFocusFrameCount;
        }

        public void setGetFocusFrameCount(uint value)
        {
            this.mGetFocusFrameCount = value;
        }

        public uint getLostFocusFrameCount()
        {
            return this.mLostFocusFrameCount;
        }

        public void setLostFocusFrameCount(uint value)
        {
            this.mLostFocusFrameCount = value;
        }

        // 获取帧率
        public int getFps()
        {
            return this.mFps;
        }

        public string getFpsStr()
        {
            return this.mFps.ToString();
        }
    }
}