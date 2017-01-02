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
        n_assert(0 != Singleton);
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
    nameTable(512)
{
    // empty
}

MClassFactory::~MClassFactory()
{
    this->nameTable.Clear();
}

void MClassFactory::Register(const Rtti* rtti, const String& className, const FourCC& classFourCC)
{
    n_assert(0 != rtti);

    // check if class name already exists
    if (this->ClassExists(className))
    {
        return;
    }

    // check if class fourcc already exists
    if (this->ClassExists(classFourCC))
    {
        return;
    }

    // register with lookup tables
    this->nameTable.Add(className, rtti);
}

void MClassFactory::Register(const Rtti* rtti, const String& className)
{
    n_assert(0 != rtti);

    // check if class name already exists
    if (this->ClassExists(className))
    {
        return;
    }

    // register with lookup tables
    this->nameTable.Add(className, rtti);
}

bool MClassFactory::ClassExists(const std::string& className) const
{
	my_assert(className.IsValid());
    return this->nameTable.Contains(className);
}

const MClassInfo* MClassFactory::GetClassRtti(const std::string& className) const
{
    n_assert(className.IsValid());
    n_assert(this->ClassExists(className));
    return this->nameTable[className];
}

RefCounted* MClassFactory::Create(const std::string& className) const
{
    n_assert(className.IsValid());
    
    // check if class exists, otherwise give a meaningful error
    if (!this->ClassExists(className))
    {
        return 0;
    }

    // lookup RTTI object of class through hash table and create new object
    const MClassInfo* rtti = this->nameTable[className];
    n_assert(0 != rtti);
	GObject* newObject = rtti->Create();
    return newObject;
}