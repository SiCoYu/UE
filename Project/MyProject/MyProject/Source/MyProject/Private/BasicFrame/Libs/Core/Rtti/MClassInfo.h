#pragma once

#include "TypeDef.h"
#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class GObject;

class MClassInfo
{
public:
	//typedef GObject* (*Creator)();

	//MClassInfo(const char* className, Creator creatorFunc, const MClassInfo* parentClass, SizeT instSize);
	MClassInfo(const char* className, const MClassInfo* parentClass, SizeT instSize);
	bool operator==(const MClassInfo& rhs) const;
	bool operator!=(const MClassInfo& rhs) const;
	const std::string& GetName() const;
	const MClassInfo* GetParent() const;
	SizeT GetInstanceSize() const;
	GObject* Create() const;
	bool IsDerivedFrom(const MClassInfo& other) const;
	bool IsDerivedFrom(const std::string& otherClassName) const;
	//void* AllocInstanceMemory();
	//void FreeInstanceMemory(void* ptr);

private:
	//void Construct(const char* className, Creator creatorFunc, const MClassInfo* parentClass, SizeT instSize);
	void Construct(const char* className, const MClassInfo* parentClass, SizeT instSize);

	std::string mName;
	const MClassInfo* mParent;
	//Creator mCreator;
	SizeT mInstanceSize;
};

inline bool MClassInfo::operator==(const MClassInfo& rhs) const
{
	return this == &rhs;
}

inline bool MClassInfo::operator!=(const MClassInfo& rhs) const
{
	return this != &rhs;
}

inline const std::string& MClassInfo::GetName() const
{
	return this->mName;
}

inline const MClassInfo* MClassInfo::GetParent() const
{
	return this->mParent;
}

inline SizeT MClassInfo::GetInstanceSize() const
{
	return this->mInstanceSize;
}

//#include "MClassMacros.h"

MY_END_NAMESPACE