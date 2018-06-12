namespace SDK.Lib
{
    public class PlayerMainMovement : PlayerMovement
    {
        protected UnityEngine.Quaternion mForwardRotate;     // 记录当前的前向
        protected UnityEngine.Quaternion mRotate;

        protected bool isUpPress = false;
        protected bool isDownPress = false;
        protected bool isLeftPress = false;
        protected bool isRightPress = false;

        public PlayerMainMovement(SceneEntityBase entity)
            : base(entity)
        {
            this.mForwardRotate = UtilMath.UnitQuat;
            this.mRotate = UtilMath.UnitQuat;

            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.UpArrow, EventId.KEYPRESS_EVENT, this.onUpArrowPress);
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.UpArrow, EventId.KEYUP_EVENT, this.onUpArrowUp);
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.W, EventId.KEYPRESS_EVENT, this.onUpArrowPress);
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.W, EventId.KEYUP_EVENT, this.onUpArrowUp);

            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.DownArrow, EventId.KEYPRESS_EVENT, this.onDownArrowPress);
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.DownArrow, EventId.KEYUP_EVENT, this.onDownArrowUp);
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.S, EventId.KEYPRESS_EVENT, this.onDownArrowPress);
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.S, EventId.KEYUP_EVENT, this.onDownArrowUp);

            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.LeftArrow, EventId.KEYPRESS_EVENT, this.onLeftArrowPress);
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.LeftArrow, EventId.KEYUP_EVENT, this.onLeftArrowUp);
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.A, EventId.KEYPRESS_EVENT, onLeftArrowPress);
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.A, EventId.KEYUP_EVENT, onLeftArrowUp);

            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.RightArrow, EventId.KEYPRESS_EVENT, onRightArrowPress);
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.RightArrow, EventId.KEYUP_EVENT, this.onRightArrowUp);
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.D, EventId.KEYPRESS_EVENT, this.onRightArrowPress);
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.D, EventId.KEYUP_EVENT, this.onRightArrowUp);

            //射击
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.J, EventId.KEYPRESS_EVENT, onFirePress);
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.Keypad0, EventId.KEYPRESS_EVENT, onFirePress);

            //分裂
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.K, EventId.KEYPRESS_EVENT, onSplitPress);
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.KeypadPeriod, EventId.KEYPRESS_EVENT, onSplitPress);

            //停止
            Ctx.msInstance.mInputMgr.addKeyListener(InputKey.Space, EventId.KEYPRESS_EVENT, onStopMovePress);
        }

        override public void init()
        {
            base.init();
        }

        override public void dispose()
        {
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.UpArrow, EventId.KEYPRESS_EVENT, onUpArrowPress);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.UpArrow, EventId.KEYUP_EVENT, onUpArrowUp);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.W, EventId.KEYPRESS_EVENT, onUpArrowPress);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.W, EventId.KEYUP_EVENT, onUpArrowUp);

            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.DownArrow, EventId.KEYPRESS_EVENT, onDownArrowPress);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.DownArrow, EventId.KEYUP_EVENT, onDownArrowUp);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.S, EventId.KEYPRESS_EVENT, onDownArrowPress);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.S, EventId.KEYUP_EVENT, onDownArrowUp);

            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.LeftArrow, EventId.KEYPRESS_EVENT, onLeftArrowPress);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.LeftArrow, EventId.KEYUP_EVENT, onLeftArrowUp);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.A, EventId.KEYPRESS_EVENT, onLeftArrowPress);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.A, EventId.KEYUP_EVENT, onLeftArrowUp);

            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.RightArrow, EventId.KEYPRESS_EVENT, onRightArrowPress);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.RightArrow, EventId.KEYUP_EVENT, onRightArrowUp);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.D, EventId.KEYPRESS_EVENT, onRightArrowPress);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.D, EventId.KEYUP_EVENT, onRightArrowUp);

            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.J, EventId.KEYPRESS_EVENT, onFirePress);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.Keypad0, EventId.KEYUP_EVENT, onFirePress);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.K, EventId.KEYPRESS_EVENT, onSplitPress);
            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.KeypadPeriod, EventId.KEYUP_EVENT, onSplitPress);

            Ctx.msInstance.mInputMgr.removeKeyListener(InputKey.Space, EventId.KEYUP_EVENT, onStopMovePress);

            base.dispose();
        }

        public override void onPutInPool()
        {
            this.isUpPress = false;
            this.isDownPress = false;
            this.isLeftPress = false;
            this.isRightPress = false;

            base.onPutInPool();
        }

        override public void onTick(float delta, TickMode tickMode)
        {
            base.onTick(delta, tickMode);
            OnMove();
        }

        public UnityEngine.Quaternion getForwardRotate()
        {
            return mForwardRotate;
        }

        protected void onUpArrowPress(IDispatchObject dispObj, uint uniqueId)
        {
            isUpPress = true;
        }

        protected void onUpArrowUp(IDispatchObject dispObj, uint uniqueId)
        {
            isUpPress = false;
        }

        protected void onDownArrowPress(IDispatchObject dispObj, uint uniqueId)
        {
            isDownPress = true;
        }

        protected void onDownArrowUp(IDispatchObject dispObj, uint uniqueId)
        {
            isDownPress = false;
        }

        protected void onLeftArrowPress(IDispatchObject dispObj, uint uniqueId)
        {
            isLeftPress = true;
        }

        protected void onLeftArrowUp(IDispatchObject dispObj, uint uniqueId)
        {
            isLeftPress = false;
        }

        protected void onRightArrowPress(IDispatchObject dispObj, uint uniqueId)
        {
            isRightPress = true;
        }

        protected void onRightArrowUp(IDispatchObject dispObj, uint uniqueId)
        {
            isRightPress = false;
        }

        static private float lastFireTime = 0;
        protected void onFirePress(IDispatchObject dispObj, uint uniqueId)
        {
            
        }

        static private float lastSplitTime = 0;
        protected void onSplitPress(IDispatchObject dispObj, uint uniqueId)
        {
 
        }

        protected void onStopMovePress(IDispatchObject dispObj, uint uniqueId)
        {
            
        }

        protected void OnMove()
        {
            if (!UtilFileIO.isWindowsRuntime()) return;
            if (!isUpPress && !isDownPress && !isLeftPress && !isRightPress)
            {
                return;
            }

            float x = UnityEngine.Input.GetAxis("Horizontal");
            float y = UnityEngine.Input.GetAxis("Vertical");
            UnityEngine.Vector2 MoveVec = UnityEngine.Vector2.zero;
            MoveVec.x = x;
            MoveVec.y = y;
        }

        //protected void onStartUp(IDispatchObject dispObj, uint uniqueId)
        //{
        //    UnityEngine.Vector3 pos = this.mEntity.getPos();
        //    Player player = Ctx.msInstance.mPlayerMgr.getEntityByIndex(1) as Player;
        //    player.setDestPos(pos);
        //}

        override public void stopMove()
        {
            base.stopMove();

            Ctx.msInstance.mGlobalDelegate.mMainPosStopChangedDispatch.dispatchEvent(this);
        }

        override public void stopRotate()
        {
            base.stopRotate();
        }

        // 更新方向
        protected void updateOrient()
        {
            UnityEngine.Quaternion quat = mForwardRotate;
            
            quat = mForwardRotate * mRotate;
            (this.mEntity as BeingEntity).setDestRotateEulerAngle(quat.eulerAngles, true);
        }

        override public void addActorLocalOffset(UnityEngine.Vector3 DeltaLocation)
        {
            base.addActorLocalOffset(DeltaLocation);
            this.onPosChanged();
        }

        override public void addActorLocalDestOffset(UnityEngine.Vector3 DeltaLocation)
        {
            base.addActorLocalDestOffset(DeltaLocation);
            this.onPosChanged();
        }

        override public void addLocalRotation(UnityEngine.Vector3 DeltaRotation)
        {
            base.addLocalRotation(DeltaRotation);
            Ctx.msInstance.mGlobalDelegate.mMainOrientChangedDispatch.dispatchEvent(this);
        }

        override public void setDestRotateEulerAngle(UnityEngine.Vector3 destRotate)
        {
            base.setDestRotateEulerAngle(destRotate);
            Ctx.msInstance.mGlobalDelegate.mMainOrientChangedDispatch.dispatchEvent(this);
        }

        protected void onAccelerationMovedHandle(IDispatchObject disoObj)
        {
            MAcceleration acceleration = disoObj as MAcceleration;
            (this.mEntity as Player).setDestRotateEulerAngle(acceleration.getOrient().eulerAngles, true);

            this.moveForward();

            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log(string.Format("Acceleration orient is x = {0}, y = {1}, z = {2}", acceleration.getOrient().eulerAngles.x, acceleration.getOrient().eulerAngles.y, acceleration.getOrient().eulerAngles.z), LogTypeId.eLogAcceleration);
            }
        }

        // 主角不移动，通过中心点移动
        override public void moveForward()
        {
            base.moveForward();
            //this.onPosChanged();
        }

        override public void sendMoveMsg()
        {
            
        }

        protected void onPosChanged()
        {
            Ctx.msInstance.mGlobalDelegate.mMainPosChangedDispatch.dispatchEvent(this);

            (this.mEntity as PlayerMain).onChildChanged();
        }

        override public void setForwardRotate(UnityEngine.Vector3 rotate)
        {
            mForwardRotate = UnityEngine.Quaternion.Euler(rotate);
        }
    }
}