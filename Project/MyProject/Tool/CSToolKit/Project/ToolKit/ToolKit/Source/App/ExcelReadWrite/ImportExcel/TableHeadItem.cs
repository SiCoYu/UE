namespace ToolSet
{
    public class TableHeadItem
    {
        protected string mFieldExplain;
        protected string mFieldName;
        protected string mFieldTypeName;
        protected FieldType mFieldType;

        public TableHeadItem()
        {

        }

        public void init()
        {

        }

        public void dispose()
        {

        }

        public void setFieldExplain(string value)
        {
            this.mFieldExplain = value;
        }

        public string getFieldExplain()
        {
            return this.mFieldExplain;
        }

        public void setFieldName(string value)
        {
            this.mFieldName = value;
        }

        public string getFieldName()
        {
            return this.mFieldName;
        }

        public void setFieldTypeName(string value)
        {
            this.mFieldTypeName = value;
        }

        public string getFieldTypeName()
        {
            return this.mFieldTypeName;
        }

        public void setFieldType(FieldType value)
        {
            this.mFieldType = value;
        }

        public FieldType getFieldType()
        {
            return this.mFieldType;
        }

        public bool isNumFieldType()
        {
            return (FieldType.eInt == this.mFieldType ||
                    FieldType.eFloat == this.mFieldType);
        }
    }
}