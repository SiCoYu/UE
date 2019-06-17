#include "MyProject.h"
#include "UniqueStrIdGen.h"
#include "TypeDef.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(UniqueStrIdGen, GObject)

UniqueStrIdGen::UniqueStrIdGen(std::string prefix, uint baseUniqueId)
	: Super(baseUniqueId)
{
	this->mPrefix = prefix;
}

std::string UniqueStrIdGen::genNewStrId()
{
	this->mStrStream.str("");

	this->mStrStream << this->mPrefix;
	this->mStrStream << "_";
	this->mStrStream << this->genNewId();

	this->mRetId = this->mStrStream.str();
	return this->mRetId;
}

std::string UniqueStrIdGen::getCurStrId()
{
	return this->mRetId;
}

std::string UniqueStrIdGen::genStrIdById(uint id)
{
	this->mStrStream.str("");

	this->mStrStream << this->mPrefix;
	this->mStrStream << "_";
	this->mStrStream << id;

	this->mRetId = this->mStrStream.str();
	return this->mRetId;
}

MY_END_NAMESPACE