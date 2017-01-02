#pragma once

#define M_DECLARE_CLASS(type) \
public: \
    void* operator new(size_t size) \
    { \
        return CLASS_INFO.AllocInstanceMemory(); \
    }; \
    void operator delete(void* p) \
    { \
        CLASS_INFO.FreeInstanceMemory(p); \
    }; \
    static MClassInfo CLASS_INFO; \
    static GObject* FactoryCreator(); \
    static type* Create(); \
    static bool RegisterWithFactory(); \
    virtual MClassInfo* GetClassInfo() const; \
private:


#define M_DECLARE_ABSTRACT_CLASS(class_name) \
public: \
    static MClassInfo CLASS_INFO; \
    virtual MClassInfo* GetClassInfo() const; \
private:


#define M_REGISTER_CLASS(type) \
    static const bool type##_registered = type::RegisterWithFactory(); \


#if MY_DEBUG
#define M_IMPLEMENT_CLASS(type, baseType) \
    MClassInfo type::CLASS_INFO(#type, type::FactoryCreator, &baseType::CLASS_INFO, sizeof(type)); \
    MClassInfo* type::GetClassInfo() const { return &this->CLASS_INFO; } \
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
            MClassFactory::Instance()->Register(&type::CLASS_INFO, #type); \
        } \
        return true; \
    }
#else
#define M_IMPLEMENT_CLASS(type, baseType) \
    MClassInfo type::CLASS_INFO(#type, type::FactoryCreator, &baseType::CLASS_INFO, sizeof(type)); \
    MClassInfo* type::GetClassInfo() const { return &this->CLASS_INFO; } \
    GObject* type::FactoryCreator() { return type::Create(); } \
    type* type::Create() \
    { \
        return my_new(type); \
    }\
    bool type::RegisterWithFactory() \
    { \
        if (!MClassFactory::Instance()->ClassExists(#type)) \
        { \
            MClassFactory::Instance()->Register(&type::CLASS_INFO, #type); \
        } \
        return true; \
    }
#endif


#define M_IMPLEMENT_ABSTRACT_CLASS(type, baseType) \
    MClassInfo type::CLASS_INFO(#type, 0, &baseType::CLASS_INFO, 0); \
    MClassInfo* type::GetClassInfo() const { return &this->CLASS_INFO; }


#if MY_DEBUG
#define M_IMPLEMENT_ROOT_CLASS(type) \
    MClassInfo type::CLASS_INFO(#type, type::FactoryCreator, 0, sizeof(type)); \
    MClassInfo* type::GetClassInfo() const { return &this->CLASS_INFO; } \
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
            MClassFactory::Instance()->Register(&type::CLASS_INFO, #type); \
        } \
        return true; \
    }
#else
#define M_IMPLEMENT_ROOT_CLASS(type) \
    MClassInfo type::CLASS_INFO(#type, type::FactoryCreator, 0, sizeof(type)); \
    MClassInfo* type::GetClassInfo() const { return &this->CLASS_INFO; } \
    GObject* type::FactoryCreator() { return type::Create(); } \
    type* type::Create() \
    { \
        return my_new(type); \
    }\
    bool type::RegisterWithFactory() \
    { \
        if (!MClassFactory::Instance()->ClassExists(#type)) \
        { \
            MClassFactory::Instance()->Register(&type::CLASS_INFO, #type); \
        } \
        return true; \
    }
#endif