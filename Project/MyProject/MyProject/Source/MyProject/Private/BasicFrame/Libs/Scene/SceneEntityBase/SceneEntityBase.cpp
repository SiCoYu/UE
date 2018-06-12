using UnityEngine;

namespace SDK.Lib
{
    /**
     * @brief 场景中的实体，定义接口，逻辑相关的一些实现放在 BeingEntity 里面，例如: 地形， Player， Npc
     */
    public class SceneEntityBase : GObject, IDispatchObject, ITickedObject, INoOrPriorityObject
    {
        protected EntityRenderBase mRender;
        //protected bool mIsClientDispose;    // 客户端已经释放这个对象，但是由于在遍历中，等着遍历结束再删除，所有多这个对象的操作都是无效的
        protected MVector3 mWorldPos;   // 世界空间
        protected Area mArea;           // 服务器区域
        protected TDTile mTDTile;       // 屏区域
        protected MDistrict mDistrict;  // 裁剪区域
        protected bool mIsInSceneGraph; // 是否在场景图中，如果不在场景图中，肯定不可见，不管是否在可视范围内
        protected EntityType mEntityType;   // Entity 类型
        protected string mEntityUniqueId;   // Entity 唯一 Id

        protected UnityEngine.Vector3 mPos;         // 当前位置信息
        protected MWrapQuaternion mRotate;   // 当前方向信息
        protected UnityEngine.Vector3 mScale;       // 当前缩放信息

        protected bool mIsVisible;          // 是否可见，数据是否可见
        protected bool mIsClipVisible;      // 裁剪是否可见
        protected uint mThisId;             // 唯一 Id

        protected bool mIsGod;      // 是否是无敌模式
        protected bool mIsFirst;    // 第一次设置位置
        protected bool mIsUsePool;  // 是否使用缓冲池
        protected bool mIsInPoolOrDispose;  // 是否被放入Pool或者销毁

        protected EventDispatch mOnSelfActorChangedDispatch;    // Actor 改变事件

        public SceneEntityBase()
        {
            this.mRotate = new MWrapQuaternion(0, 0, 0, 1);
            this.mRender = null;
            this.mOnSelfActorChangedDispatch = new AddOnceEventDispatch();
            this.onGetFromPool();
        }

        // 这个接口调用之前，一定要先设置 ThisId ，调用 setThisId，必须先设置这个
        virtual public void init()
        {
            this.onInit();
        }

        virtual protected void _onPreInit()
        {

        }

        virtual protected void _onExecInit()
        {

        }

        virtual protected void _onPostInit()
        {

        }

        virtual public void onInit()
        {
            this._onPreInit();
            this._onExecInit();
            this._onPostInit();
        }

        // 释放接口
        virtual public void dispose()
        {
            this.onDestroy();
        }

        // 释放的时候回调的接口
        virtual public void onDestroy()
        {
            if (null != this.mRender)
            {
                this.mRender.dispose();
                this.mRender = null;
            }

            if(null != this.mTDTile)
            {
                this.mTDTile.removeEntity(this);
                this.mTDTile = null;
            }

            this.setClientDispose(true);
        }

        public bool isUsePool()
        {
            return this.mIsUsePool;
        }

        public void setIsUsePool(bool value)
        {
            this.mIsUsePool = value;
        }

        virtual public void putInPool()
        {
            this.onPutInPool();
        }

        virtual public void getFromPool()
        {
            this.onGetFromPool();
        }

        // 缓存回收
        virtual public void onPutInPool()
        {
            this.mIsInPoolOrDispose = true;

            if (null != this.mRender)
            {
                this.mRender.putInPool();
            }
            if (null != this.mTDTile)
            {
                this.mTDTile.removeEntity(this);
                this.mTDTile = null;
            }
            this.mRotate.clear();
            this.mOnSelfActorChangedDispatch.clearEventHandle();
        }

        virtual public void onGetFromPool()
        {
            this.mIsInPoolOrDispose = false;
            //this.mIsClientDispose = false;
            this.mIsInSceneGraph = true;

            this.mPos = UtilMath.ZeroVec3;
            this.mRotate.setRotateXYZW(0, 0, 0, 1);
            this.mScale = Vector3.one;

            this.mIsVisible = false;        // 当前逻辑是否可见
            this.mIsClipVisible = false;    // 裁剪是否可见

            this.mIsGod = false;
            this.mIsFirst = true;
            this.mIsUsePool = false;
        }

        virtual public int getBufferType()
        {
            return (int)this.mEntityType;
        }

        public void setThisId(uint thisId)
        {
            this.mThisId = (uint)thisId;
        }

        public uint getThisId()
        {
            // this.mThisId 这个需要单独保存，不要从 mEntity_KBE 获取，因为只有 PlayerMain 才有 Avatar , 其它 PlayerOther 是没有 Avatar 的
            return this.mThisId;
        }

        virtual public void show()
        {
            if (!this.mIsVisible)
            {
                this.mIsVisible = true;
                //this.mIsInScreenRange = true;   // 显示不一定在 Screen 可见

                if (null != this.mRender)
                {
                    this.mRender.show();
                }

                this.onClipShow();
            }
        }

        virtual public void hide()
        {
            if (this.mIsVisible)
            {
                this.mIsVisible = false;
                this.mIsClipVisible = false;  // 逻辑隐藏，直接设定不在屏幕范围内

                if (null != this.mRender)
                {
                    this.mRender.hide();
                }

                this.onClipHide();
            }
        }

        virtual public void forceShow()
        {
            if (!this.mIsVisible)
            {
                this.mIsVisible = true;

                if (null != this.mRender)
                {
                    this.mRender.forceShow();
                }
            }
        }

        virtual public void forceHide()
        {
            if (this.mIsVisible)
            {
                this.mIsVisible = false;

                if (null != this.mRender)
                {
                    this.mRender.forceHide();
                }
            }
        }

        virtual public bool IsVisible()
        {
            return this.mIsVisible;
        }

        public void setClipVisible(bool value)
        {
            this.mIsClipVisible = value;
        }

        public bool isClipVisible()
        {
            return this.mIsClipVisible;
        }

        // 进入可见
        virtual public void onClipShow()
        {
            if (!this.mIsClipVisible)
            {
                this.mIsClipVisible = true;

                if (null != this.mRender)
                {
                    this.mRender.onClipShow();
                }
            }
        }

        // 离开可见
        virtual public void onClipHide()
        {
            if (this.mIsClipVisible)
            {
                this.mIsClipVisible = false;

                if (null != this.mRender)
                {
                    this.mRender.onClipHide();
                }
            }
        }

        // 第一次创建确保屏幕可视化
        virtual public void firstCheckScreenVisible()
        {
            if (this.mIsClipVisible)
            {
                if (null != this.mRender)
                {
                    this.mRender.onClipShow();
                }
            }
        }

        virtual public void setClientDispose(bool isDispose)
        {
            //this.mIsClientDispose = isDispose;
            this.mIsInPoolOrDispose = isDispose;

            if (null != this.mRender)
            {
                this.mRender.setClientDispose(isDispose);
            }
        }

        virtual public bool isClientDispose()
        {
            //return this.mIsClientDispose;
            return this.mIsInPoolOrDispose;
        }

        public UnityEngine.GameObject getGameObject()
        {
            if(null != this.mRender)
            {
                return this.mRender.getSelfActor();
            }

            return null;
        }

        // 获取特效插槽
        public UnityEngine.GameObject getEffectSocket()
        {
            if (null != this.mRender)
            {
                return this.mRender.getEffectSocket();
            }

            return null;
        }

        // 每一帧执行
        virtual public void onTick(float delta, TickMode tickMode)
        {
            this._onPreTick(delta, tickMode);
            this._onExecTick(delta, tickMode);
            this._onPostTick(delta, tickMode);
            if(null != this.mRender) this.mRender.onTick(delta, tickMode);
        }

        // Tick 第一阶段执行
        virtual protected void _onPreTick(float delta, TickMode tickMode)
        {

        }

        virtual protected void _onExecTick(float delta, TickMode tickMode)
        {

        }

        // Tick 第二阶段执行
        virtual protected void _onPostTick(float delta, TickMode tickMode)
        {

        }

        virtual public GameObject gameObject()
        {
            if (null != this.mRender)
            {
                return this.mRender.getSelfActor();
            }

            return null;
        }

        virtual public void setGameObject(GameObject rhv)
        {
            if (null != this.mRender)
            {
                this.mRender.setSelfActor(rhv);
            }
        }

        virtual public Transform transform()
        {
            if (null != this.mRender)
            {
                return this.mRender.transform();
            }

            return null;
        }

        virtual public void setPnt(GameObject pntGO_)
        {
            if (null != this.mRender)
            {
                this.mRender.setParentActor(pntGO_);
            }
        }

        virtual public GameObject getPnt()
        {
            if (null != this.mRender)
            {
                return this.mRender.getParentActor();
            }

            return null;
        }

        virtual public bool checkRender()
        {
            if (null != this.mRender)
            {
                return this.mRender.checkRender();
            }

            return false;
        }

        virtual public float getWorldPosX()
        {
            return this.mWorldPos.x;
        }

        virtual public float getWorldPosY()
        {
            return this.mWorldPos.z;
        }

        public MVector3 getWorldPos()
        {
            return this.mWorldPos;
        }

        public void setArea(Area area)
        {
            this.mArea = area;
        }

        public void setTile(TDTile tile)
        {
            this.mTDTile = tile;
        }

        public TDTile getTile()
        {
            return this.mTDTile;
        }

        public void setDistrict(MDistrict district)
        {
            this.mDistrict = district;
        }

        public void setInSceneGraph(bool value)
        {
            this.mIsInSceneGraph = value;
        }

        public bool getInSceneGraph()
        {
            return this.mIsInSceneGraph;
        }

        // 从 KBE 设置位置，必须要从这个接口设置
        public void setPos_FromKBE(Vector3 pos)
        {
            pos = UtilEngineWrap.convPosByMode(pos);

            this.setPos(pos);
        }
        
        virtual public void setPos(Vector3 pos)
        {
            if (!UtilMath.isEqualVec3(this.mPos, pos) || this.mIsFirst)
            {
                this.mIsFirst = false;
                pos = Ctx.msInstance.mSceneSys.adjustPosInRange(this, pos);

                this.mPos = pos;

                if (null != this.mRender)
                {
                    this.mRender.setPos(pos);
                }

                if (MacroDef.ENABLE_SCENE2D_CLIP)
                {
                    this.updateClip();
                }

                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("BeingEntity::setPos, BasicInfo is {0}, X = {1}, Y = {2}, Z = {3}", this.getBasicInfoStr(), this.mPos.x, this.mPos.y, this.mPos.z), LogTypeId.eLogBeingMove);
                }
            }
        }

        virtual public void setRenderPos(Vector3 pos)
        {
            if (!UtilEngineWrap.isInFakePos(pos) && !UtilMath.isEqualVec3(this.mPos, pos))
            {
                this.mPos = pos;

                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("BeingEntity::setRenderPos, BasicInfo is {0}, mPosX = {1}, mPosY = {2}, mPosZ = {3}", this.getBasicInfoStr(), this.mPos.x, this.mPos.y, this.mPos.z), LogTypeId.eLogBeingMove);
                }
            }
        }

        public UnityEngine.Vector3 getPos()
        {
            return this.mPos;
        }

        // 获取世界空间中的绝对位置
        virtual public UnityEngine.Vector3 getFullPos()
        {
            return this.mPos;
        }

        virtual public void setRotate(Quaternion rotation)
        {
            if (!UtilMath.isEqualQuat(this.mRotate.getRotate(), rotation))
            {
                this.mRotate.setRotation(rotation);

                // Player 是不更新转换的, FlyBulletFlock 也是不更新的
                if (EntityType.eFlyBulletFlock != this.mEntityType &&
                    EntityType.ePlayerMain != this.getEntityType() &&
                    EntityType.ePlayerOther != this.getEntityType())
                {
                    if (null != this.mRender)
                    {
                        this.mRender.setRotate(rotation);
                    }
                }

                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("BeingEntity::setRotation, BasicInfo is {0}, X = {1}, Y = {2}, Z = {3}, W = {4}", this.getBasicInfoStr(), this.mRotate.getX(), this.mRotate.getY(), this.mRotate.getZ(), this.mRotate.getW()), LogTypeId.eLogBeingMove);
                }
            }
        }

        public void setRotateEulerAngle_FromKBE(UnityEngine.Vector3 rotation)
        {
            rotation = UtilEngineWrap.convRotByMode(rotation);
            this.setRotateEulerAngle(rotation);
        }

        // 这个是单位方向向量
        public void setRotateNormalDir(UnityEngine.Vector3 normalDir)
        {
            UnityEngine.Quaternion quad = UtilMath.getRotateByOrient(normalDir);
            this.setRotateEulerAngle(quad.eulerAngles);
        }

        // 这个是欧拉角
        public void setRotateEulerAngle(UnityEngine.Vector3 rotation)
        {
            if (!UtilMath.isEqualVec3(this.mRotate.getRotateEulerAngle(), rotation))
            {
                // 只能绕 Y 轴旋转
                if (MacroDef.XZ_MODE)
                {
                    rotation.x = 0;
                    rotation.z = 0;
                }
                else if (MacroDef.XY_MODE)
                {
                    // 只能绕 Z 轴旋转
                    rotation.x = 0;
                    rotation.y = 0;
                }

                this.mRotate.setRotateEulerAngle(rotation);

                // Player 是不更新转换的
                if (EntityType.ePlayerMain != this.getEntityType() &&
                    EntityType.ePlayerOther != this.getEntityType() &&
                    EntityType.eFlyBulletFlock != this.getEntityType())
                {
                    if (null != this.mRender)
                    {
                        this.mRender.setRotate(this.mRotate.getRotate());
                    }
                }

                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("BeingEntity::setRotateEulerAngle, BasicInfo is {0}, X = {1}, Y = {2}, Z = {3}, W = {4}", this.getBasicInfoStr(), this.mRotate.getX(), this.mRotate.getY(), this.mRotate.getZ(), this.mRotate.getW()), LogTypeId.eLogBeingMove);
                }
            }
        }

        // 获取前向向量
        public UnityEngine.Vector3 getForward()
        {
            UnityEngine.Vector3 forward = this.mRotate.getRotate() * UnityEngine.Vector3.forward;

            return forward;
        }

        public UnityEngine.Quaternion getRotate()
        {
            return this.mRotate.getRotate();
        }

        public UnityEngine.Vector3 getRotateEulerAngle()
        {
            return this.mRotate.getRotateEulerAngle();
        }

        public Vector3 getScale()
        {
            return this.mScale;
        }

        virtual public Vector3 getPreScale()
        {
            return UtilMath.OneVec3;
        }

        virtual public void setScale(UnityEngine.Vector3 value)
        {
            if (!UtilMath.isEqualVec3(this.mScale, value))
            {
                this.mScale = value;

                if (null != this.mRender)
                {
                    this.mRender.setScale(this.mScale);
                }

                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("BeingEntity::setScale, BasicInfo is {0}, X = {1}, Y = {2}, Z = {3}", this.getBasicInfoStr(), this.mScale.x, this.mScale.y, this.mScale.z), LogTypeId.eLogBeingMove);
                }
            }
        }

        public void setSelfName(string name)
        {
            if (null != this.mRender)
            {
                if (!MacroDef.MOBILE_PLATFORM)
                    this.mRender.setSelfName(name);
            }
        }

        public Bounds getBounds()
        {
            Bounds retBounds = new Bounds(UtilMath.ZeroVec3, UtilMath.ZeroVec3);

            if (null != this.mRender)
            {
                retBounds = this.mRender.getBounds();
            }

            return retBounds;
        }

        public void AddRelativeForce(Vector3 force, ForceMode mode = ForceMode.Force)
        {
            if (null != this.mRender)
            {
                this.mRender.AddRelativeForce(force, mode);
            }
        }

        virtual public void AddForce(Vector3 force, ForceMode mode = ForceMode.Force)
        {
            if (null != this.mRender)
            {
                this.mRender.AddForce(force, mode);
            }
        }

        // 自动管理
        virtual public void autoHandle()
        {

        }

        // 初始化渲染器
        virtual public void initRender()
        {

        }

        virtual public void loadRenderRes()
        {

        }

        public EntityType getEntityType()
        {
            return this.mEntityType;
        }

        public UnityEngine.Rigidbody getRigidbody()
        {
            if (null != this.mRender)
            {
                return this.mRender.getRigidbody();
            }

            return null;
        }

        public EntityRenderBase getRender()
        {
            return this.mRender;
        }

        public string getEntityUniqueId()
        {
            return this.mEntityUniqueId;
        }

        // 获取基本信息字符串
        protected string getBasicInfoStr()
        {
            return string.Format("ThisId = {0}, TypeId = {1}", this.getThisId(), this.getTypeId());
        }

        public bool getIsGod()
        {
            return this.mIsGod;
        }

        public void setIsGod(bool _god)
        {
            this.mIsGod = _god;
        }

        virtual public void updateClip()
        {
            // Child\Bullet\LinkEffect 不做裁剪，只做 Player\BulletFlock 的裁剪，因为现在 Child 挂在 Player Node 下面
            if (EntityType.ePlayerMainChild != this.mEntityType &&
                EntityType.ePlayerOtherChild != this.mEntityType &&
                EntityType.eFlyBullet != this.mEntityType &&
                EntityType.eLinkEffect != this.mEntityType)
            {
                Ctx.msInstance.mTileMgr.updateEntity(this);
            }
        }

        public void addSelfActorChangedHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle)
        {
            this.mOnSelfActorChangedDispatch.addEventHandle(pThis, handle);
        }

        public void onSelfActorChangedDispatch()
        {
            this.mOnSelfActorChangedDispatch.dispatchEvent(this);
        }

        virtual public int getSortingOrder()
        {
            if(null != this.mRender)
            {
                return this.mRender.getSortingOrder();
            }

            return 0;
        }

        virtual public void setSortingOrder(int order)
        {
            if (null != this.mRender)
            {
                this.mRender.setSortingOrder(order);
            }
        }

        virtual public Vector3 getArrowDirectionScale()
        {
            return UtilMath.OneVec3;
        }
    }
}