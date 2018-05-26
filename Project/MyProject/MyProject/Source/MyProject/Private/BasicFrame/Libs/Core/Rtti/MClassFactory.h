#pragma once

#include <string>
#include <unordered_map>

class GObject;
class MClassInfo;

class MClassFactory
{
	typedef std::unordered_map<std::string, const MClassInfo*> UMap;

public:
    static MClassFactory* Instance();
    static void Destroy();

    void Register(const MClassInfo* classInfo, const std::string& className);
    bool ClassExists(const std::string& className) const;
    const MClassInfo* GetClassInfo(const std::string& className) const;
	//GObject* Create(const std::string& className) const;

private:
	MClassFactory();
    ~MClassFactory();

    static MClassFactory* msSingleton;
	UMap mNameTable;
};