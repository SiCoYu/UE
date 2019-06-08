using SDK.Lib;

namespace ToolSet
{
    public class TableBodyRow
    {
        protected MList<AuxPropertyBase> mPropertyList;

        public TableBodyRow()
        {
            this.mPropertyList = new MList<AuxPropertyBase>();
        }

        public void init()
        {

        }

        public void dispose()
        {
            int index = 0;
            int listLen = this.mPropertyList.count();
            AuxPropertyBase item = null;

            while (index < listLen)
            {
                item = this.mPropertyList.get(index);
                item.dispose();

                index += 1;
            }

            this.mPropertyList.clear();
            this.mPropertyList = null;
        }

        public void addProperty(AuxPropertyBase value)
        {
            this.mPropertyList.add(value);
        }

        public AuxPropertyBase getPropertyByIndex(int index)
        {
            return this.mPropertyList.get(index);
        }
    }
}