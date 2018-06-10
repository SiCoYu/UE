#include "MyProject.h"
#include "UniqueNumIdGen.h"
#include <limits>
#include "TypeDef.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(UniqueNumIdGen, GObject)

UniqueNumIdGen::UniqueNumIdGen(uint baseUniqueId)
{
	this->mBaseId = baseUniqueId;
	this->mCurId = this->mBaseId;
}

uint UniqueNumIdGen::genNewId()
{
	if(std::numeric_limits<uint>::max() == this->mCurId)
	{
		this->mPreIdx = this->mCurId;
		this->mCurId = this->mBaseId;
	}

	this->mPreIdx = this->mCurId;
	this->mCurId++;

	return this->mPreIdx;
}

uint UniqueNumIdGen::getCurId()
{
	return this->mCurId;
}

MY_END_NAMESPACE