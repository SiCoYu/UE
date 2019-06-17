#pragma once

#include "PlatformDefine.h"

#define M_DECLARE_CLASS(type, baseType) \
	typedef baseType Super; \
public: \
	/* \
    void* operator new(size_t size) \
    { \
        return CLASS_INFO.AllocInstanceMemory(); \
    }; \
    void operator delete(void* p) \
    { \
        CLASS_INFO.FreeInstanceMemory(p); \
    }; \
	*/ \
    static MClassInfo CLASS_INFO; \
	/* \
    static GObject* FactoryCreator(); \
    static type* Create(); \
	*/ \
    static bool RegisterWithFactory(); \
    virtual MClassInfo* GetMyClassInfo() const; \
private:


#define M_DECLARE_ROOT_CLASS(type) \
public: \
	/* \
	void* operator new(size_t size) \
	{ \
		return CLASS_INFO.AllocInstanceMemory(); \
	}; \
	void operator delete(void* p) \
	{ \
		CLASS_INFO.FreeInstanceMemory(p); \
	}; \
	*/ \
    static MClassInfo CLASS_INFO; \
	/* \
	static GObject* FactoryCreator(); \
	static type* Create(); \
	*/ \
    static bool RegisterWithFactory(); \
    virtual MClassInfo* GetMyClassInfo() const; \
private:


#define M_DECLARE_ABSTRACT_CLASS(class_name) \
public: \
    static MClassInfo CLASS_INFO; \
    virtual MClassInfo* GetMyClassInfo() const; \
private:


#define M_REGISTER_CLASS(type) \
    static const bool type##_registered = type::RegisterWithFactory(); \


//  warning C4668: 'MY_DEBUG' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
#ifdef MY_DEBUG_MODE
#define M_IMPLEMENT_CLASS(type, baseType) \
	/* \
    MClassInfo type::CLASS_INFO(#type, type::FactoryCreator, &baseType::CLASS_INFO, sizeof(type)); \
	*/ \
	MClassInfo type::CLASS_INFO(#type, &baseType::CLASS_INFO, sizeof(type)); \
    MClassInfo* type::GetMyClassInfo() const { return &this->CLASS_INFO; } \
	/* \
    GObject* type::FactoryCreator() { return type::Create(); } \
    type* type::Create() \
    { \
        MClassInfo::mCriticalSection.Lock(); \
        MClassInfo::mIsInCreate = true; \
        type* newObject = my_new(type); \
        MClassInfo::mIsInCreate = false; \
        MClassInfo::mCriticalSection.Unlock(); \
        return newObject; \
    }\
	*/ \
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
	/* \
    MClassInfo type::CLASS_INFO(#type, type::FactoryCreator, &baseType::CLASS_INFO, sizeof(type)); \
	*/ \
	MClassInfo type::CLASS_INFO(#type, &baseType::CLASS_INFO, sizeof(type)); \
    MClassInfo* type::GetMyClassInfo() const { return &this->CLASS_INFO; } \
	/* \
    GObject* type::FactoryCreator() { return type::Create(); } \
    type* type::Create() \
    { \
        return my_new(type); \
    }\
	*/ \
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
	/* \
    MClassInfo type::CLASS_INFO(#type, 0, &baseType::CLASS_INFO, 0); \
	*/ \
	MClassInfo type::CLASS_INFO(#type, &baseType::CLASS_INFO, 0); \
    MClassInfo* type::GetMyClassInfo() const { return &this->CLASS_INFO; }


// warning C4668: 'MY_DEBUG' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
#ifdef MY_DEBUG
#define M_IMPLEMENT_ROOT_CLASS(type) \
	/* \
    MClassInfo type::CLASS_INFO(#type, type::FactoryCreator, 0, sizeof(type)); \
	*/ \
	MClassInfo type::CLASS_INFO(#type, 0, sizeof(type)); \
    MClassInfo* type::GetMyClassInfo() const { return &this->CLASS_INFO; } \
	/* \
    GObject* type::FactoryCreator() { return type::Create(); } \
    type* type::Create() \
    { \
        MClassInfo::mCriticalSection.Lock(); \
        MClassInfo::mIsInCreate = true; \
        type* newObject = my_new(type); \
        MClassInfo::mIsInCreate = false; \
        MClassInfo::mCriticalSection.Unlock(); \
        return newObject; \
    }\
	*/ \
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
	/* \
    MClassInfo type::CLASS_INFO(#type, type::FactoryCreator, 0, sizeof(type)); \
	*/ \
	MClassInfo type::CLASS_INFO(#type, 0, sizeof(type)); \
    MClassInfo* type::GetMyClassInfo() const { return &this->CLASS_INFO; } \
	/* \
    GObject* type::FactoryCreator() { return type::Create(); } \
    type* type::Create() \
    { \
        return my_new(type); \
    }\
	*/ \
    bool type::RegisterWithFactory() \
    { \
        if (!MClassFactory::Instance()->ClassExists(#type)) \
        { \
            MClassFactory::Instance()->Register(&type::CLASS_INFO, #type); \
        } \
        return true; \
    }
#endif


#define M_IMPLEMENT_AND_REGISTER_CLASS(type, baseType) \
	M_IMPLEMENT_CLASS(type, baseType) \
	M_REGISTER_CLASS(type)


#define M_IMPLEMENT_AND_REGISTER_ABSTRACT_CLASS(type, baseType) \
	M_IMPLEMENT_ABSTRACT_CLASS(type, baseType) \
	M_REGISTER_CLASS(type)


#define M_IMPLEMENT_AND_REGISTER_ROOT_CLASS(type) \
	M_IMPLEMENT_ROOT_CLASS(type) \
	M_REGISTER_CLASS(type)
