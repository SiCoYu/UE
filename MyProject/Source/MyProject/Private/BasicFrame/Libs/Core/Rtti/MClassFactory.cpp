#include "MyProject.h"
#include "MClassFactory.h"
#include "GObject.h"
#include "MClassInfo.h"
#include "MyMemory.h"
#include "TypeDef.h"

MClassFactory* MClassFactory::Singleton = 0;

MClassFactory* MClassFactory::Instance()
{
    if (0 == Singleton)
    {
        Singleton = my_new(MClassFactory);
        my_assert(0 != Singleton);
    }
    return Singleton;
}

void MClassFactory::Destroy()
{
    if (0 != Singleton)
    {
		my_delete(Singleton);
        Singleton = 0;
    }
}

MClassFactory::MClassFactory() :
	mNameTable(512)
{
    // empty
}

MClassFactory::~MClassFactory()
{
    this->mNameTable.clear();
}

void MClassFactory::Register(const MClassInfo* rtti, const std::string& className)
{
    my_assert(0 != rtti);

    if (this->ClassExists(className))
    {
        return;
    }

    this->mNameTable.insert(UMap::value_type(className, rtti));
}

bool MClassFactory::ClassExists(const std::string& className) const
{
	my_assert(className.length() > 0);
    return this->mNameTable.find(className) != this->mNameTable.end();
}

const MClassInfo* MClassFactory::GetClassRtti(const std::string& className) const
{
    my_assert(className.length() > 0);
	my_assert(this->ClassExists(className));
    //return this->mNameTable[className];
	return this->mNameTable.find(className)->second;
}

GObject* MClassFactory::Create(const std::string& className) const
{
	my_assert(className.length() > 0);
    
    if (!this->ClassExists(className))
    {
        return 0;
    }
	//const MClassInfo* rtti = this->mNameTable[className];
    const MClassInfo* rtti = this->mNameTable.find(className)->second;

    my_assert(0 != rtti);
	GObject* newObject = rtti->Create();
    return newObject;
}