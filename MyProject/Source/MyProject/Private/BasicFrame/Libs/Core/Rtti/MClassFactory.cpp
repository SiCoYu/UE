#include "MyProject.h"
#include "MClassFactory.h"
#include "GObject.h"
#include "MClassInfo.h"

MClassFactory* MClassFactory::Singleton = 0;

MClassFactory* MClassFactory::Instance()
{
    if (0 == Singleton)
    {
        Singleton = n_new(MClassFactory);
        n_assert(0 != Singleton);
    }
    return Singleton;
}

void MClassFactory::Destroy()
{
    if (0 != Singleton)
    {
        n_delete(Singleton);
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
    this->fourccTable.Clear();
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
    this->fourccTable.Add(classFourCC, rtti);
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

bool MClassFactory::ClassExists(const String& className) const
{
    n_assert(className.IsValid());
    return this->nameTable.Contains(className);
}

bool MClassFactory::ClassExists(const FourCC fourCC) const
{
    n_assert(fourCC.IsValid());
    return this->fourccTable.Contains(fourCC);
}

const Rtti* MClassFactory::GetClassRtti(const String& className) const
{
    n_assert(className.IsValid());
    n_assert(this->ClassExists(className));
    return this->nameTable[className];
}

const Rtti* MClassFactory::GetClassRtti(const FourCC& classFourCC) const
{
    n_assert(classFourCC.IsValid());
    n_assert(this->ClassExists(classFourCC));
    return this->fourccTable[classFourCC];
}

RefCounted* MClassFactory::Create(const String& className) const
{
    n_assert(className.IsValid());
    
    // check if class exists, otherwise give a meaningful error
    if (!this->ClassExists(className))
    {
        return 0;
    }

    // lookup RTTI object of class through hash table and create new object
    const Rtti* rtti = this->nameTable[className];
    n_assert(0 != rtti);
    RefCounted* newObject = rtti->Create();
    return newObject;
}