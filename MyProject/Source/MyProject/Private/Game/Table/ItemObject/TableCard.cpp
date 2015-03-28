#include "MyProject.h"
#include "TableCard.h"

override public void TableCardItemBody ::parseBodyByteArray(ByteArray bytes, uint offset)
{
    (bytes as ByteArray).position = offset;
    m_name = UtilTable.readString(bytes as ByteArray);

    m_type = bytes.readInt();
    m_career = bytes.readInt();
    m_race = bytes.readInt();
    m_quality = bytes.readInt();
    m_magicConsume = bytes.readInt();

    m_attack = bytes.readInt();
    m_hp = bytes.readInt();
    m_Durable = bytes.readInt();
    m_prefab = UtilTable.readString(bytes as ByteArray);

    m_chaoFeng = bytes.readInt();
    m_chongFeng = bytes.readInt();
    m_fengNu = bytes.readInt();
    m_qianXing = bytes.readInt();
    m_shengDun = bytes.readInt();
    m_mpAdded = bytes.readInt();
    m_guoZai = bytes.readInt();
    m_faShu = bytes.readInt();
    m_zhanHou = bytes.readInt();
    m_wangYu = bytes.readInt();
    m_jiNu = bytes.readInt();
    m_bNeedFaShuTarget = bytes.readByte();
}

public string TableCardItemBody::path
{
    get
    {
        return Ctx.m_instance.m_cfg.m_pathLst[(int)ResPathType.ePathModel] + m_prefab;
    }
}