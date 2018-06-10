#include "MyProject.h"
#include "UniqueStrIdGen.h"
#include "TypeDef.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(UniqueStrIdGen, GObject)

UniqueStrIdGen::UniqueStrIdGen(string prefix, uint baseUniqueId)
	: Super(baseUniqueId)
{
	this->mPrefix = prefix;
}

std::string UniqueStrIdGen::genNewStrId()
{
	this.mRetId = this->mPrefix + "_" + this->genNewId();
	return this->mRetId;
}

std::string UniqueStrIdGen::getCurStrId()
{
	return this->mRetId;
}

std::string UniqueStrIdGen::genStrIdById(uint id)
{
	this.mStringBuilder = new System.Text.StringBuilder();
	this.mStringBuilder.Append(this.mPrefix);
	this.mStringBuilder.Append('_');
	this.mStringBuilder.Append(id);
	this.mRetId = this.mStringBuilder.ToString();
	return this.mRetId;
}

MY_END_NAMESPACE