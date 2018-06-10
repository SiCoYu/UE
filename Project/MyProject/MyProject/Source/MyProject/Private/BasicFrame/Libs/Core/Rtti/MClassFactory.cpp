#include "MyProject.h"
#include "MClassFactory.h"
#include "GObject.h"
#include "MClassInfo.h"
#include "MyMemoryAlloc.h"
#include "TypeDef.h"
#include "MDebug.h"

#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

MClassFactory* MClassFactory::msSingleton = 0;

MClassFactory* MClassFactory::Instance()
{
    if (0 == MClassFactory::msSingleton)
    {
		MClassFactory::msSingleton = MY_NEW MClassFactory;
        MY_ASSERT(0 != MClassFactory::msSingleton);
    }

    return MClassFactory::msSingleton;
}

void MClassFactory::Destroy()
{
    if (0 != MClassFactory::msSingleton)
    {
		MY_DELETE MClassFactory::msSingleton;
		MClassFactory::msSingleton = 0;
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

void MClassFactory::Register(const MClassInfo* classInfo, const std::string& className)
{
    MY_ASSERT(0 != classInfo);

    if (this->ClassExists(className))
    {
        return;
    }

    this->mNameTable.insert(UMap::value_type(className, classInfo));
}

bool MClassFactory::ClassExists(const std::string& className) const
{
	MY_ASSERT(className.length() > 0);
    return this->mNameTable.find(className) != this->mNameTable.end();
}

const MClassInfo* MClassFactory::GetMyClassInfoFromFactory(const std::string& className) const
{
    MY_ASSERT(className.length() > 0);
	MY_ASSERT(this->ClassExists(className));
    //return this->mNameTable[className];
	return this->mNameTable.find(className)->second;
}

//GObject* MClassFactory::Create(const std::string& className) const
//{
//	MY_ASSERT(className.length() > 0);
//    
//    if (!this->ClassExists(className))
//    {
//        return 0;
//    }
//	//const MClassInfo* classInfo = this->mNameTable[className];
//    const MClassInfo* classInfo = this->mNameTable.find(className)->second;
//
//    MY_ASSERT(0 != classInfo);
//	GObject* newObject = classInfo->Create();
//    return newObject;
//}

MY_END_NAMESPACE