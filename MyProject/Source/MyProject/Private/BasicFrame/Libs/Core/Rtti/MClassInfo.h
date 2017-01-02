#pragma once

#include "TypeDef.h"
#include <string>

class GObject;
class MClassInfo;

class MClassInfo
{
public:
	typedef GObject* (*Creator)();

	MClassInfo(const char* className, Creator creatorFunc, const MClassInfo* parentClass, SizeT instSize);
	bool operator==(const MClassInfo& rhs) const;
	bool operator!=(const MClassInfo& rhs) const;
	const std::string& GetName() const;
	const MClassInfo* GetParent() const;
	SizeT GetInstanceSize() const;
	GObject* Create() const;
	bool IsDerivedFrom(const MClassInfo& other) const;
	bool IsDerivedFrom(const std::string& otherClassName) const;
	void* AllocInstanceMemory();
	void FreeInstanceMemory(void* ptr);

private:
	void Construct(const char* className, Creator creatorFunc, const MClassInfo* parentClass, SizeT instSize);

	std::string name;
	const MClassInfo* parent;
	Creator creator;
	SizeT instanceSize;
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
	return this->name;
}

inline const MClassInfo* MClassInfo::GetParent() const
{
	return this->parent;
}

inline SizeT MClassInfo::GetInstanceSize() const
{
	return this->instanceSize;
}

#include "MClassMacros.h"