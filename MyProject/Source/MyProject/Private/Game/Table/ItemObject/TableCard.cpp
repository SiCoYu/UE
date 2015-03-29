#include "MyProject.h"
#include "TableCard.h"

#include "ByteBuffer.h"
#include "UtilTable.h"

void TableCardItemBody::parseBodyByteArray(ByteBuffer* bytes, uint32 offset)
{
    bytes->pos(offset);
	UtilTable::readString(bytes, m_name);

	bytes->readInt32(m_type);
	bytes->readInt32(m_career);
	bytes->readInt32(m_race);
	bytes->readInt32(m_quality);
	bytes->readInt32(m_magicConsume);

	bytes->readInt32(m_attack);
	bytes->readInt32(m_hp);
	bytes->readInt32(m_Durable);
	UtilTable::readString(bytes, m_prefab);

	bytes->readInt32(m_chaoFeng);
	bytes->readInt32(m_chongFeng);
	bytes->readInt32(m_fengNu);
	bytes->readInt32(m_qianXing);
    bytes->readInt32(m_shengDun);
	bytes->readInt32(m_mpAdded);
	bytes->readInt32(m_guoZai);
	bytes->readInt32(m_faShu);
	bytes->readInt32(m_zhanHou);
	bytes->readInt32(m_wangYu);
	bytes->readInt32(m_jiNu);
	bytes->readUnsignedInt8(m_bNeedFaShuTarget);
}