using SDK.Lib;

namespace ToolSet
{
    public class TableHead
    {
        protected MList<TableHeadItem> mTableHeadItemList;

        public TableHead()
        {
            this.mTableHeadItemList = new MList<TableHeadItem>();
        }

        public void init()
        {

        }

        public void dispose()
        {
            int index = 0;
            int listLen = this.mTableHeadItemList.count();
            TableHeadItem item = null;

            while (index < listLen)
            {
                item = this.mTableHeadItemList.get(index);
                item.dispose();

                index += 1;
            }

            this.mTableHeadItemList.clear();
            this.mTableHeadItemList = null;
        }

        public int getItemCount()
        {
            return this.mTableHeadItemList.count();
        }

        public void addTableHeadItem(TableHeadItem item)
        {
            this.mTableHeadItemList.add(item);
        }

        public TableHeadItem getTableHeadItemByColumnIndex(int columnIndex)
        {
            return this.mTableHeadItemList.get(columnIndex);
        }
    }
}