namespace SDK.Lib
{
    /**
     * @brief PlayerMainChild 行为控制
     */
    public class PlayerMainChildAI
    {
        protected BeingEntity mEntity;
        protected SteerActor mActor;
        protected Biped2D mBiped;
        protected Radar2D mRadar;

        protected SteerForNeighborGroup2D mSteerForNeighborGroup;

        protected SteerForSeparation2D mSteerForSeparation;
        protected SteerForCohesion2D mSteerForCohesion;
        protected SteerForTether2D mSteerForTether;

        protected float mNormalInterval;    // 正常间隔
        protected float mNormalSpeed;       // 正常速度

        protected TimeInterval mUpdateSteerTimeInterval;    // 更新 Steer 行为时间间隔
        protected TimeSegment mEnableUpdateTimeInterval;    // 开启更新行为

        public PlayerMainChildAI(BeingEntity entity)
        {
            this.mEntity = entity;

            this.mActor = new SteerActor();

            this.mBiped = new Biped2D();
            this.mBiped.setSteer2DProxy(mEntity);
            this.mActor.addComponent(this.mBiped);

            this.mRadar = new Radar2D();
            this.mActor.addComponent(this.mRadar);

            this.mSteerForNeighborGroup = new SteerForNeighborGroup2D();
            this.mActor.addComponent(this.mSteerForNeighborGroup);

            this.mSteerForSeparation = new SteerForSeparation2D();
            this.mActor.addComponent(this.mSteerForSeparation);

            //this.mSteerForCohesion = new SteerForCohesion2D();
            //this.mActor.addComponent(this.mSteerForCohesion);

            this.mSteerForTether = new SteerForTether2D();
            this.mActor.addComponent(this.mSteerForTether);
            this.mSteerForTether.enabled = true;

            this.mNormalInterval = 0.15f;
            this.mNormalSpeed = 1.0f;

            this.mUpdateSteerTimeInterval = new TimeInterval();
            this.mUpdateSteerTimeInterval.setInterval(this.mNormalInterval);
            this.mEnableUpdateTimeInterval = new TimeSegment();
            this.mEnableUpdateTimeInterval.setSegment(8);
        }

        public void init()
        {
            this.mBiped.init();
            this.mSteerForNeighborGroup.init();
            this.mSteerForTether.init();
        }

        public Biped2D getVehicle()
        {
            return this.mBiped;
        }

        public void setVehicleList(MList<Vehicle2D> neighbors)
        {
            this.mSteerForNeighborGroup.Neighbors = neighbors;
        }

        public void setPos(UnityEngine.Vector3 pos)
        {
            this.mActor.setPos(pos);
        }

        // 数量添加或者减少
        public void onChildNumChanged()
        {
            this.mEnableUpdateTimeInterval.setCurTime(0);
        }

        public void onTick(float delta, TickMode tickMode)
        {
            if (this.mEnableUpdateTimeInterval.canExec(delta))
            {
                if (this.mUpdateSteerTimeInterval.canExec(delta))
                {
                    // 如果间隔过大，就会导致瞬间移动距离过大
                    this.mBiped.Update(Ctx.msInstance.mSystemTimeData.getFixFrameRateInterval(), tickMode);
                    this.mBiped.updateState();
                }
            }
        }
    }
}