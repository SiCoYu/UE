using SDK.Lib;

namespace ToolSet
{
    public class FieldDefineItem
    {
        protected string mFieldTypeName;
        protected FieldType mFieldType;

        public FieldDefineItem()
        {

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
    }
}