namespace SDK.Lib
{
    /**
     * @brief 全局委托，只要初始化后，就可以注册和使用这些委托，不用等到哪一个资源创建完成
     */
    public class GlobalDelegate
    {
        // PlayerMainChild 的质量发生改变
        public AddOnceEventDispatch mMainChildMassChangedDispatch;
        // Camera 相机方向或者位置发生改变
        public AddOnceEventDispatch mCameraOrientChangedDispatch;

        public AddOnceEventDispatch mMainOrientChangedDispatch;     // PlayerMain 方向改变分发器
        public AddOnceEventDispatch mMainPosChangedDispatch;        // PlayerMain 位置改变分发器
        public AddOnceEventDispatch mMainOrientStopChangedDispatch; // PlayerMain 方向改变停止分发器
        public AddOnceEventDispatch mMainPosStopChangedDispatch;    // PlayerMain 位置改变停止分发器

        // MainPlayer 的 Child 的大小\数量\位置 发生改变触发事件
        public AddOnceEventDispatch mMainChildChangedDispatch;
        // MainPlayer数量改变触发事件，用于设置个体速度
        public AddOnceEventDispatch mMainChildNumChangedDispatch;
        // topx位置改变
        public AddOnceEventDispatch mTopxPosChangedDispatch;
        // 通知GambBox相关模块加载完成
        public AddOnceEventDispatch mGameBoxLoadedDispatch;
        // 语音模块加载完成
        public AddOnceEventDispatch mGiantVoiceLoadedDispatch;
        // 登录返回信息
        public AddOnceEventDispatch mLoginResultDispatch;

        //聊天
        public AddOnceEventDispatch mAddChatUserDispatch;//新玩家聊天
        public AddOnceEventDispatch mAddChatMsgDispatch;//当前私聊玩家新消息

        //邮件
        public AddOnceEventDispatch mAddNewMailDispatch;//新邮件
        public AddOnceEventDispatch mOpenOneMailDispatch;//打开邮件
        public AddOnceEventDispatch mNewMailGetDispatch;//新邮件未读
        public AddOnceEventDispatch mDeleteMailDispatch;//删除邮件
        public AddOnceEventDispatch mAllMailReadedDispatch;//所有邮件已读

        public GlobalDelegate()
        {
            this.mMainChildMassChangedDispatch = new AddOnceEventDispatch();
            this.mCameraOrientChangedDispatch = new AddOnceEventDispatch();
            this.mMainOrientChangedDispatch = new AddOnceEventDispatch();
            this.mMainPosChangedDispatch = new AddOnceEventDispatch();
            this.mMainOrientStopChangedDispatch = new AddOnceEventDispatch();
            this.mMainPosStopChangedDispatch = new AddOnceEventDispatch();
            this.mMainChildChangedDispatch = new AddOnceEventDispatch();
            this.mMainChildNumChangedDispatch = new AddOnceEventDispatch();
            this.mTopxPosChangedDispatch = new AddOnceEventDispatch();
            this.mGameBoxLoadedDispatch = new AddOnceEventDispatch();
            this.mGiantVoiceLoadedDispatch = new AddOnceEventDispatch();
            this.mLoginResultDispatch = new AddOnceEventDispatch();

            this.mAddChatUserDispatch = new AddOnceEventDispatch();
            this.mAddChatMsgDispatch = new AddOnceEventDispatch();
            this.mAddNewMailDispatch = new AddOnceEventDispatch();
            this.mOpenOneMailDispatch = new AddOnceEventDispatch();
            this.mNewMailGetDispatch = new AddOnceEventDispatch();
            this.mDeleteMailDispatch = new AddOnceEventDispatch();
            this.mAllMailReadedDispatch = new AddOnceEventDispatch();
        }

        public void addMainChildChangedHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle)
        {
            this.mMainChildChangedDispatch.addEventHandle(pThis, handle);
        }

        public void init()
        {
            this.mMainChildMassChangedDispatch.init();
            this.mCameraOrientChangedDispatch.init();
            this.mMainOrientChangedDispatch.init();
            this.mMainPosChangedDispatch.init();
            this.mMainOrientStopChangedDispatch.init();
            this.mMainPosStopChangedDispatch.init();
            this.mMainChildChangedDispatch.init();
            this.mMainChildNumChangedDispatch.init();
            this.mTopxPosChangedDispatch.init();
            this.mGameBoxLoadedDispatch.init();
            this.mGiantVoiceLoadedDispatch.init();
            this.mLoginResultDispatch.init();
            this.mAddChatUserDispatch.init();
            this.mAddChatMsgDispatch.init();
            this.mAddNewMailDispatch.init();
            this.mOpenOneMailDispatch.init();
            this.mNewMailGetDispatch.init();
            this.mDeleteMailDispatch.init();
            this.mAllMailReadedDispatch.init();
        }

        public void dispose()
        {
            if (null != this.mMainChildMassChangedDispatch)
            {
                this.mMainChildMassChangedDispatch.dispose();
                this.mMainChildMassChangedDispatch = null;
            }
            if (null != this.mCameraOrientChangedDispatch)
            {
                this.mCameraOrientChangedDispatch.dispose();
                this.mCameraOrientChangedDispatch = null;
            }
            if (null != this.mMainOrientChangedDispatch)
            {
                this.mMainOrientChangedDispatch.dispose();
                this.mMainOrientChangedDispatch = null;
            }
            if (null != this.mMainPosChangedDispatch)
            {
                this.mMainPosChangedDispatch.dispose();
                this.mMainPosChangedDispatch = null;
            }
            if (null != this.mMainOrientStopChangedDispatch)
            {
                this.mMainOrientStopChangedDispatch.dispose();
                this.mMainOrientStopChangedDispatch = null;
            }
            if (null != this.mMainPosStopChangedDispatch)
            {
                this.mMainPosStopChangedDispatch.dispose();
                this.mMainPosStopChangedDispatch = null;
            }
            if (null != this.mMainChildChangedDispatch)
            {
                this.mMainChildChangedDispatch.dispose();
                this.mMainChildChangedDispatch = null;
            }
            if (null != this.mMainChildNumChangedDispatch)
            {
                this.mMainChildNumChangedDispatch.dispose();
                this.mMainChildNumChangedDispatch = null;
            }
            if (null != this.mTopxPosChangedDispatch)
            {
                this.mTopxPosChangedDispatch.dispose();
                this.mTopxPosChangedDispatch = null;
            }
            if (null != this.mGameBoxLoadedDispatch)
            {
                this.mGameBoxLoadedDispatch.dispose();
                this.mGameBoxLoadedDispatch = null;
            }
            if (null != this.mGiantVoiceLoadedDispatch)
            {
                this.mGiantVoiceLoadedDispatch.dispose();
                this.mGiantVoiceLoadedDispatch = null;
            }
            if (null != this.mLoginResultDispatch)
            {
                this.mLoginResultDispatch.dispose();
                this.mLoginResultDispatch = null;
            }
            if (null != this.mAddChatUserDispatch)
            {
                this.mAddChatUserDispatch.dispose();
                this.mAddChatUserDispatch = null;
            }
            if (null != this.mAddChatMsgDispatch)
            {
                this.mAddChatMsgDispatch.dispose();
                this.mAddChatMsgDispatch = null;
            }
            if (null != this.mAddNewMailDispatch)
            {
                this.mAddNewMailDispatch.dispose();
                this.mAddNewMailDispatch = null;
            }
            if (null != this.mOpenOneMailDispatch)
            {
                this.mOpenOneMailDispatch.dispose();
                this.mOpenOneMailDispatch = null;
            }
            if (null != this.mNewMailGetDispatch)
            {
                this.mNewMailGetDispatch.dispose();
                this.mNewMailGetDispatch = null;
            }
            if (null != this.mDeleteMailDispatch)
            {
                this.mDeleteMailDispatch.dispose();
                this.mDeleteMailDispatch = null;
            }
            if (null != this.mAllMailReadedDispatch)
            {
                this.mAllMailReadedDispatch.dispose();
                this.mAllMailReadedDispatch = null;
            }
        }
    }
}