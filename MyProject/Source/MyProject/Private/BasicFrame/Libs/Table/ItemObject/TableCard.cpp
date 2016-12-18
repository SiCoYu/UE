#include "MyProject.h"
#include "TableCard.h"

#include "ByteBuffer.h"
#include "UtilTable.h"

void TableCardItemBody::parseBodyByteBuffer(ByteBuffer* bytes, uint32 offset)
{
    bytes->setPos(offset);
	UtilTable::readString(bytes, mName);

	bytes->readInt32(mType);
	bytes->readInt32(mCareer);
	bytes->readInt32(mRace);
	bytes->readInt32(mQuality);
	bytes->readInt32(mMagicConsume);

	bytes->readInt32(mAttack);
	bytes->readInt32(mHp);
	bytes->readInt32(mDurable);

	bytes->readInt32(mChaoFeng);
	bytes->readInt32(mChongFeng);
	bytes->readInt32(mFengNu);
	bytes->readInt32(mQianXing);
    bytes->readInt32(mShengDun);
	bytes->readInt32(mMpAdded);
	bytes->readInt32(mGuoZai);
	bytes->readInt32(mFaShu);
	bytes->readInt32(mZhanHou);
	bytes->readUnsignedInt8(mIsNeedFaShuTarget);
	bytes->readInt32(mIsNeedZhanHouTarget);
	UtilTable::readString(bytes, mCardDesc);
	UtilTable::readString(bytes, mCardHeader);
	bytes->readUnsignedInt32(mSkillPrepareEffect);
}