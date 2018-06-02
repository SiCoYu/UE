#include "MyProject.h"
#include "MString.h"

MY_BEGIN_NAMESPACE(MyNS)

MString::MString()
{

}

MString::~MString()
{

}

typename MString::StringRef MString::getString()
{
	return this->mString;
}

int MString::getUniqueId()
{
	return this->mUniqueId;
}

void MString::setUniqueId(int value)
{
	this->mUniqueId = value;
}

MY_END_NAMESPACE