#include "MyProject.h"
#include "TableCard.h"

#include "ByteBuffer.h"
#include "UtilTable.h"

void TableCardItemBody::parseBodyByteArray(ByteBuffer* bytes, uint32 offset)
{
    bytes->position = offset;
    m_name = UtilTable::readString(bytes);

    m_type = bytes->readInt32();
    m_career = bytes->readInt32();
    m_race = bytes->readInt32();
    m_quality = bytes->readInt32();
    m_magicConsume = bytes->readInt32();

    m_attack = bytes->readInt32();
    m_hp = bytes->readInt32();
    m_Durable = bytes->readInt32();
    m_prefab = UtilTable::readString(bytes);

    m_chaoFeng = bytes->readInt32();
    m_chongFeng = bytes->readInt32();
    m_fengNu = bytes->readInt32();
    m_qianXing = bytes->readInt32();
    m_shengDun = bytes->readInt32();
    m_mpAdded = bytes->readInt32();
    m_guoZai = bytes->readInt32();
    m_faShu = bytes->readInt32();
    m_zhanHou = bytes->readInt32();
    m_wangYu = bytes->readInt32();
    m_jiNu = bytes->readInt32();
    m_bNeedFaShuTarget = bytes->readUnsignedInt8();
}