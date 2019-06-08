namespace SDK.Lib
{
    public class UniqueNumIdGen
    {
        protected uint mBaseId;
        protected uint mPreIdx;
        protected uint mCurId;

        public UniqueNumIdGen(uint baseUniqueId)
        {
            this.mBaseId = baseUniqueId;
            this.mCurId = this.mBaseId;
        }

        public uint genNewId()
        {
            if(uint.MaxValue == this.mCurId)
            {
                this.mPreIdx = this.mCurId;
                this.mCurId = this.mBaseId;
            }

            this.mPreIdx = this.mCurId;
            this.mCurId++;

            return this.mPreIdx;
        }

        public uint getCurId()
        {
            return this.mCurId;
        }
    }
}