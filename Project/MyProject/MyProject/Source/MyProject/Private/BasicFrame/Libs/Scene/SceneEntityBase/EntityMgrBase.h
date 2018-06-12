namespace SDK.Lib
{
    public class EntityMgrBase : DelayPriorityHandleMgrBase, ITickedObject, INoOrPriorityObject
    {
        protected MList<SceneEntityBase> mSceneEntityList;
        protected MDictionary<string, SceneEntityBase> mId2EntityDic;
        protected MDictionary<uint, SceneEntityBase> mThisId2EntityDic;
        protected UniqueStrIdGen mUniqueStrIdGen;
        protected UniqueNumIdGen mUniqueNumIdGen;

        public EntityMgrBase()
        {
            this.mSceneEntityList = new MList<SceneEntityBase>();
            this.mSceneEntityList.setIsSpeedUpFind(true);
            this.mSceneEntityList.setIsOpKeepSort(true);

            this.mId2EntityDic = new MDictionary<string, SceneEntityBase>();
            this.mThisId2EntityDic = new MDictionary<uint, SceneEntityBase>();

            this.mUniqueNumIdGen = new UniqueNumIdGen(0);
        }

        override public void init()
        {

        }

        override public void dispose()
        {
            this.clearAll();
        }

        public UniqueNumIdGen getUniqueNumIdGen()
        {
            return this.mUniqueNumIdGen;
        }

        virtual public void onPutInPool()
        {
            this.clearAll();
        }

        override protected void _addObject(IDelayHandleItem entity, float priority = 0.0f)
        {
            if (this._isInDepth())
            {
                base._addObject(entity);
            }
            else
            {
                if (!this.mSceneEntityList.contains(entity as SceneEntityBase))
                {
                    this.mSceneEntityList.add(entity as SceneEntityBase);
                }
            }
        }

        override protected void _removeObject(IDelayHandleItem entity)
        {
            if (this._isInDepth())
            {
                base._removeObject(entity);
            }
            else
            {
                if (this.mSceneEntityList.contains(entity as SceneEntityBase))
                {
                    this.mSceneEntityList.remove(entity as SceneEntityBase);
                }
            }
        }

        virtual public void addEntity(SceneEntityBase entity)
        {
            this._addObject(entity);

            if(!this.mId2EntityDic.containsKey(entity.getEntityUniqueId()))
            {
                this.mId2EntityDic[entity.getEntityUniqueId()] = entity;
            }
            else
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log("EntityMgrBase already exist key", LogTypeId.eLogCommon);
                }
            }

            if (!this.mThisId2EntityDic.containsKey(entity.getThisId()))
            {
                this.mThisId2EntityDic[entity.getThisId()] = entity;
            }

            //entity.onInit();
        }

        virtual public void removeEntity(SceneEntityBase entity)
        {
            this._removeObject(entity);

            if (this.mId2EntityDic.containsKey(entity.getEntityUniqueId()))
            {
                this.mId2EntityDic.remove(entity.getEntityUniqueId());
            }
            else
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log("EntityMgrBase::removeEntity, already remove key", LogTypeId.eLogCommon);
                }
            }

            if (this.mThisId2EntityDic.containsKey(entity.getThisId()))
            {
                this.mThisId2EntityDic.remove(entity.getThisId());
            }
        }

        public bool Contains(SceneEntityBase entity)
        {
            return this.mSceneEntityList.contains(entity);
        }

        virtual public void onTick(float delta, TickMode tickMode)
        {
            this._incDepth();

            this._onTickExec(delta, tickMode);

            this._decDepth();
        }

        virtual protected void _onTickExec(float delta, TickMode tickMode)
        {
            int idx = 0;
            int count = this.mSceneEntityList.count();

            SceneEntityBase entity = null;

            while(idx < count)
            {
                entity = this.mSceneEntityList[idx];

                if (!entity.isClientDispose())
                {
                    entity.onTick(delta, tickMode);
                }

                ++idx;
            }
        }

        public void setClientDispose(bool isDispose)
        {

        }

        public bool isClientDispose()
        {
            return false;
        }

        // 通过 Id 获取元素
        public SceneEntityBase getEntityByThisId(uint thisId)
        {
            SceneEntityBase ret = null;

            this.mThisId2EntityDic.tryGetValue(thisId, out ret);

            return ret;
        }

        // 通过 Unique Id 获取元素，Unique Id 是客户端自己的唯一 id ，与服务器没有关系
        public SceneEntityBase getEntityByUniqueId(string uniqueId)
        {
            SceneEntityBase ret = null;

            this.mId2EntityDic.tryGetValue(uniqueId, out ret);

            return ret;
        }

        // 通过数组下标获取元素
        public SceneEntityBase getEntityByIndex(int index)
        {
            if (index < this.mSceneEntityList.count())
            {
                return this.mSceneEntityList[index];
            }

            return null;
        }

        public string genNewStrId()
        {
            return this.mUniqueStrIdGen.genNewStrId();
        }

        public string getCurStrId()
        {
            return this.mUniqueStrIdGen.getCurStrId();
        }

        public uint getCurId()
        {
            return this.mUniqueStrIdGen.getCurId();
        }

        public string genStrIdById(uint id)
        {
            return this.mUniqueStrIdGen.genStrIdById(id);
        }

        public int getEntityCount()
        {
            return this.mSceneEntityList.count();
        }

        public MList<SceneEntityBase> getSceneEntityList()
        {
            return this.mSceneEntityList;
        }

        virtual public void clearAll()
        {
            this._incDepth();

            int len = this.mSceneEntityList.count();
            int idx = len - 1;
            SceneEntityBase entity = null;

            // 一定要从后往前删除，这样更新索引的时候不会更新所有的索引
            while (idx >= 0)
            {
                entity = this.mSceneEntityList[idx];

                if (!entity.isClientDispose())
                {
                    EntityNumIdBufferObjectFactory.deleteObject(entity);
                }

                idx -= 1;
            }

            this._decDepth();
        }

        public void changeThisId(uint srcThisId, uint destThisId, SceneEntityBase entity)
        {
            this.mThisId2EntityDic.remove(srcThisId);
            this.mThisId2EntityDic[destThisId] = entity;
        }
    }
}