#pragma once

#define __DeclareClass(type) \
public: \
    void* operator new(size_t size) \
    { \
        return RTTI.AllocInstanceMemory(); \
    }; \
    void operator delete(void* p) \
    { \
        RTTI.FreeInstanceMemory(p); \
    }; \
    static MClassInfo RTTI; \
    static GObject* FactoryCreator(); \
    static type* Create(); \
    static bool RegisterWithFactory(); \
    virtual MClassInfo* GetRtti() const; \
private:


#define __DeclareAbstractClass(class_name) \
public: \
    static MClassInfo RTTI; \
    virtual MClassInfo* GetRtti() const; \
private:


#define __RegisterClass(type) \
    static const bool type##_registered = type::RegisterWithFactory(); \


#if MY_DEBUG
#define __ImplementClass(type, baseType) \
    MClassInfo type::RTTI(#type, type::FactoryCreator, &baseType::RTTI, sizeof(type)); \
    MClassInfo* type::GetRtti() const { return &this->RTTI; } \
    GObject* type::FactoryCreator() { return type::Create(); } \
    type* type::Create() \
    { \
        MClassInfo::criticalSection.Lock(); \
        MClassInfo::isInCreate = true; \
        type* newObject = my_new(type); \
        MClassInfo::isInCreate = false; \
        MClassInfo::criticalSection.Unlock(); \
        return newObject; \
    }\
    bool type::RegisterWithFactory() \
    { \
        if (!MClassFactory::Instance()->ClassExists(#type)) \
        { \
            MClassFactory::Instance()->Register(&type::RTTI, #type); \
        } \
        return true; \
    }
#else
#define __ImplementClass(type, baseType) \
    MClassInfo type::RTTI(#type, type::FactoryCreator, &baseType::RTTI, sizeof(type)); \
    MClassInfo* type::GetRtti() const { return &this->RTTI; } \
    GObject* type::FactoryCreator() { return type::Create(); } \
    type* type::Create() \
    { \
        return my_new(type); \
    }\
    bool type::RegisterWithFactory() \
    { \
        if (!MClassFactory::Instance()->ClassExists(#type)) \
        { \
            MClassFactory::Instance()->Register(&type::RTTI, #type); \
        } \
        return true; \
    }
#endif


#define __ImplementAbstractClass(type, baseType) \
    MClassInfo type::RTTI(#type, 0, &baseType::RTTI, 0); \
    MClassInfo* type::GetRtti() const { return &this->RTTI; }


#if MY_DEBUG
#define __ImplementRootClass(type) \
    MClassInfo type::RTTI(#type, type::FactoryCreator, 0, sizeof(type)); \
    MClassInfo* type::GetRtti() const { return &this->RTTI; } \
    GObject* type::FactoryCreator() { return type::Create(); } \
    type* type::Create() \
    { \
        MClassInfo::criticalSection.Lock(); \
        MClassInfo::isInCreate = true; \
        type* newObject = my_new(type); \
        MClassInfo::isInCreate = false; \
        MClassInfo::criticalSection.Unlock(); \
        return newObject; \
    }\
    bool type::RegisterWithFactory() \
    { \
        if (!MClassFactory::Instance()->ClassExists(#type)) \
        { \
            MClassFactory::Instance()->Register(&type::RTTI, #type); \
        } \
        return true; \
    }
#else
#define __ImplementRootClass(type) \
    MClassInfo type::RTTI(#type, type::FactoryCreator, 0, sizeof(type)); \
    MClassInfo* type::GetRtti() const { return &this->RTTI; } \
    GObject* type::FactoryCreator() { return type::Create(); } \
    type* type::Create() \
    { \
        return my_new(type); \
    }\
    bool type::RegisterWithFactory() \
    { \
        if (!MClassFactory::Instance()->ClassExists(#type)) \
        { \
            MClassFactory::Instance()->Register(&type::RTTI, #type); \
        } \
        return true; \
    }
#endif