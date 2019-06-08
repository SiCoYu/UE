using SDK.Lib;

namespace ToolSet
{
    public class TableBody
    {
        protected MKeyIndexList<int, TableBodyRow> mTableBodyRowList;

        public TableBody()
        {
            this.mTableBodyRowList = new MKeyIndexList<int, TableBodyRow>();
        }

        public void init()
        {

        }

        public void dispose()
        {
            int index = 0;
            int listLen = this.mTableBodyRowList.count();
            TableBodyRow item = null;

            while (index < listLen)
            {
                item = this.mTableBodyRowList.get(index);
                item.dispose();

                index += 1;
            }

            this.mTableBodyRowList.clear();
            this.mTableBodyRowList = null;
        }

        public int getRowCount()
        {
            return this.mTableBodyRowList.count();
        }

        public AuxPropertyBase getPropertyByIndex(int rowIndex, int columnIndex)
        {
            AuxPropertyBase ret = null;
            TableBodyRow tableBodyRow = this.mTableBodyRowList.get(rowIndex);
            ret = tableBodyRow.getPropertyByIndex(columnIndex);
            return ret;
        }

        public TableBodyRow getTableBodyRowByIndex(int rowIndex)
        {
            return this.mTableBodyRowList.value(rowIndex);
        }

        public void addFieldByRowIndex(int rowIndex, AuxPropertyBase property)
        {
            TableBodyRow row = null;

            if (!this.mTableBodyRowList.containsKey(rowIndex))
            {
                row = new TableBodyRow();
                this.mTableBodyRowList.add(rowIndex, row);
            }
            else
            {
                row = this.mTableBodyRowList.value(rowIndex);
            }

            row.addProperty(property);
        }
    }
}