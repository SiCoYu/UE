#pragma once

#include <string>
#include <unordered_map>

class GObject;
class MClassInfo;

//------------------------------------------------------------------------------
class MClassFactory
{
public:
    /// get pointer to singleton instance (cannot use singleton.h!)
    static MClassFactory* Instance();
    /// static instance destruction method
    static void Destroy();

    /// register a RTTI object with the factory (with class name and class fourcc code)
    void Register(const MClassInfo* rtti, const std::string& className);
    /// register a RTTI object with the factory (without fourcc code)
    void Register(const MClassInfo* rtti, const std::string& className);
    /// check if a class exists by class name
    bool ClassExists(const std::string& className) const;
    /// get class rtti object by name
    const MClassInfo* GetClassRtti(const std::string& className) const;
    /// create an object by class name
	GObject* Create(const std::string& className) const;

private:
    /// constructor is private
	MClassFactory();
    /// destructor is private
    ~MClassFactory();

    static MClassFactory* Singleton;
    std::unordered_map<std::string, const MClassInfo*> nameTable;     // for fast lookup by class name
};