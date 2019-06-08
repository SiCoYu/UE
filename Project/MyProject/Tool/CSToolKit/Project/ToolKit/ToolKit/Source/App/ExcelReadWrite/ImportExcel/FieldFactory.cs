using SDK.Lib;

namespace ToolSet
{
    public class FieldFactory
    {
        protected MKeyIndexList<string, FieldDefineItem> mFieldDefineList;

        public FieldFactory()
        {
            this.mFieldDefineList = new MKeyIndexList<string, FieldDefineItem>();
        }

        public void init()
        {
            this._registerFieldDefine();
        }

        public void dispose()
        {

        }

        public void _addOneFieldDefine(string name, FieldType type)
        {
            FieldDefineItem item = new FieldDefineItem();
            this.mFieldDefineList.add(name, item);

            item.setFieldTypeName(name);
            item.setFieldType(type);
        }

        public void _registerFieldDefine()
        {
            this._addOneFieldDefine("string", FieldType.eStr);
            this._addOneFieldDefine("String", FieldType.eStr);
            this._addOneFieldDefine("int", FieldType.eInt);
            this._addOneFieldDefine("Int32", FieldType.eInt);
            this._addOneFieldDefine("float", FieldType.eFloat);
        }

        public AuxPropertyBase _createPropertyByFieldType(FieldType fieldType)
        {
            AuxPropertyBase ret = null;

            if (FieldType.eInt == fieldType)
            {
                ret = new AuxIntProperty();
            }
            else if (FieldType.eFloat == fieldType)
            {
                ret = new AuxFloatProperty();
            }
            else if (FieldType.eStr == fieldType)
            {
                ret = new AuxStrProperty();
            }

            return ret;
        }

        public FieldType getFieldTypeByFieldTypeName(string fieldTypeName)
        {
            FieldType ret = FieldType.eStr;
            FieldDefineItem defineItem = null;

            defineItem = this.mFieldDefineList.value(fieldTypeName);

            if(null != defineItem)
            {
                ret = defineItem.getFieldType();
            }

            return ret;
        }

        public AuxPropertyBase getPropertyByFieldTypeName(string fieldTypeName)
        {
            AuxPropertyBase ret = null;

            ret = this._createPropertyByFieldType(
                this.mFieldDefineList.value(fieldTypeName).getFieldType()
            );

            return ret;
        }

        public AuxPropertyBase getPropertyByFieldType(FieldType fieldType)
        {
            AuxPropertyBase ret = null;

            ret = this._createPropertyByFieldType(
                fieldType
            );

            return ret;
        }
    }
}