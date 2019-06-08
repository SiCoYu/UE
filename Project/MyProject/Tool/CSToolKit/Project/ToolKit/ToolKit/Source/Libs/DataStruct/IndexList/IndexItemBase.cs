namespace SDK.Lib
{
    public class IndexItemBase : GObject
    {
        protected int mIndex;   // 索引

        public IndexItemBase()
        {
            this.mIndex = -1;
        }

        override public void init()
        {

        }

        override public void dispose()
        {

        }

        public int getIndex()
        {
            return this.mIndex;
        }

        public void setIndex(int value)
        {
            this.mIndex = value;
        }

        public void resetIndex()
        {
            this.mIndex = -1;
        }
    }
}