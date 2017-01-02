#pragma once

#include "TypeDef.h"
#include <string>

class GObject;
class MClassInfo;

class MClassInfo
{
public:
	/// define a creation callback function prototype
	typedef GObject* (*Creator)();

	/// constructor
	MClassInfo(const char* className, Creator creatorFunc, const MClassInfo* parentClass, SizeT instSize);
	/// legacy constructor without FourCC for Mangalore compatibility
	MClassInfo(const char* className, Creator creatorFunc, const MClassInfo* parentClass, SizeT instSize);
	/// equality operator
	bool operator==(const MClassInfo& rhs) const;
	/// inequality operator
	bool operator!=(const MClassInfo& rhs) const;
	/// get class name
	const std::string& GetName() const;
	/// get pointer to parent class
	const MClassInfo* GetParent() const;
	/// get instance size in bytes
	SizeT GetInstanceSize() const;
	/// create an object of this class
	GObject* Create() const;
	/// return true if this rtti is equal or derived from to other rtti
	bool IsDerivedFrom(const MClassInfo& other) const;
	/// return true if this MClassInfo is equal or derived from to other rtti, by string
	bool IsDerivedFrom(const std::string& otherClassName) const;
	/// allocate instance memory block (called by class new operator)
	void* AllocInstanceMemory();
	/// free instance memory block (called by class delete operator)
	void FreeInstanceMemory(void* ptr);

private:
	/// constructor method, called from the various constructors
	void Construct(const char* className, Creator creatorFunc, const MClassInfo* parentClass, SizeT instSize);

	std::string name;
	const MClassInfo* parent;
	Creator creator;
	SizeT instanceSize;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
MClassInfo::operator==(const MClassInfo& rhs) const
{
	return this == &rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
MClassInfo::operator!=(const MClassInfo& rhs) const
{
	return this != &rhs;
}

//------------------------------------------------------------------------------
/**
*/
inline const std::string&
MClassInfo::GetName() const
{
	return this->name;
}

//------------------------------------------------------------------------------
/**
*/
inline const Core::MClassInfo*
MClassInfo::GetParent() const
{
	return this->parent;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
MClassInfo::GetInstanceSize() const
{
	return this->instanceSize;
}

#include "MClassMacros.h"