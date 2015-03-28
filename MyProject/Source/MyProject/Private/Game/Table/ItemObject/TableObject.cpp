#include "MyProject.h"
#include "TableCard.h"

override public void TableObjectItemBody::parseBodyByteArray(ByteArray bytes, uint offset)
{
    (bytes as ByteArray).position = offset;  // 从偏移处继续读取真正的内容
    m_name = UtilTable.readString(bytes as ByteArray);
    m_maxNum = bytes.readInt();
    m_type = bytes.readInt();
    m_color = bytes.readInt();
    m_prefab = UtilTable.readString(bytes as ByteArray);
}

public string TableObjectItemBody::path
{
    get
    {
        return Ctx.m_instance.m_cfg.m_pathLst[(int)ResPathType.ePathModel] + m_prefab;
    }
}