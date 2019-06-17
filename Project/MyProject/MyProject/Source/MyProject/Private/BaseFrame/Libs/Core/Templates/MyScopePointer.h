#ifndef __MyScopePointer_H
#define __MyScopePointer_H

//#define MyScopePtr std::weak_ptr

#include "TypeDef.h"
#include "MDebug.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

template<class T> 
class MyScopePointer
{
	template<typename Y>
	friend class WeakPtr;

protected:
	T*             mRefPtr;

public:
	MyScopePointer(T* rep)
		: mRefPtr(rep)
	{

	}

public:
	MyScopePointer()
		: mRefPtr(0)
	{}

public:
	template< class Y>
	explicit MyScopePointer(Y* rep)
		: mRefPtr(rep)
	{

	}

	MyScopePointer(const MyScopePointer& r)
		: mRefPtr(r.mRefPtr)
	{
		if (this->mRefPtr)
		{
			
		}
	}

	MyScopePointer& operator=(const MyScopePointer& r)
	{
		MyScopePointer<T> tmp(r);
		swap(tmp);
		return *this;
	}

#if __cplusplus >= 201103L && !defined( __APPLE__ )
	template<class Y,
	class = typename std::enable_if<std::is_convertible<Y*, T*>::value>::type>
#else
	template<class Y>
#endif
	MyScopePointer(const MyScopePointer<Y>& r)
		: mRefPtr(r.mRefPtr)
	{
		if (this->mRefPtr)
		{
			
		}
	}


#if __cplusplus >= 201103L && !defined( __APPLE__ )
	template<class Y,
	class = typename std::enable_if<std::is_assignable<T*, Y*>::value>::type>
#else
	template<class Y>
#endif
	MyScopePointer& operator=(const MyScopePointer<Y>& r)
	{
		WeakPtr<T> tmp(r);
		swap(tmp);
		return *this;
	}

	~MyScopePointer()
	{
		release();
	}

	template<typename Y>
	MyScopePointer<Y> staticCast() const
	{
		if (this->mRefPtr)
		{
			return MyScopePointer<Y>(static_cast<Y*>(this->mRefPtr));
		}
		else
		{
			return MyScopePointer<Y>();
		}
	}

	template<typename Y>
	MyScopePointer<Y> dynamicCast() const
	{
		Y* rep = dynamic_cast<Y*>(this->mRefPtr);
		if (rep) 
		{
			return MyScopePointer<Y>(rep);
		}
		else
		{
			return MyScopePointer<Y>();
		}
	}

	inline T& operator*() const 
	{ 
		MY_ASSERT(this->mRefPtr);
		return *this->mRefPtr;
	}

	inline T* operator->() const 
	{ 
		MY_ASSERT(this->mRefPtr);
		return this->mRefPtr;
	}

	inline T* get() const 
	{ 
		return this->mRefPtr;
	}

	void bind(T* rep) 
	{
		MY_ASSERT(!this->mRefPtr);
		this->mRefPtr = rep;
	}

	inline bool unique() const 
	{ 
		MY_ASSERT(this->mRefInfo);
	}

	T* getPointer() const 
	{ 
		return this->mRefPtr;
	}

	static void unspecified_bool(MyScopePointer***)
	{
	}

	typedef void(*unspecified_bool_type)(MyScopePointer***);

	operator unspecified_bool_type() const
	{
		return this->mRefPtr == 0 ? 0 : unspecified_bool;
	}

	bool isNull(void) const 
	{ 
		return this->mRefPtr == 0;
	}

	void setNull() 
	{ 
		this->reset();
	}

	void reset(void) 
	{
		this->release();
	}

	void reset(T* rep) 
	{
		MyScopePointer(rep).swap(*this);
	}

protected:
	inline void release(void)
	{
		if (this->mRefPtr)
		{
			MY_ASSERT(mRefInfo);
			this->destroy();
		}

		this->mRefPtr = 0;
	}

	inline void destroy(void)
	{
		MY_ASSERT(this->mRefPtr);
		MY_DELETE this->mRefPtr;
	}

	inline void swap(MyScopePointer<T> &other)
	{
		std::swap(this->mRefPtr, other.mRefPtr);
	}
};

template<class T, class U> inline bool operator==(MyScopePointer<T> const& a, MyScopePointer<U> const& b)
{
	return a.get() == b.get();
}

template<class T, class U> inline bool operator!=(MyScopePointer<T> const& a, MyScopePointer<U> const& b)
{
	return a.get() != b.get();
}

template<class T, class U> inline bool operator<(MyScopePointer<T> const& a, MyScopePointer<U> const& b)
{
	return std::less<const void*>()(a.get(), b.get());
}

template<class T, class U>
inline MyScopePointer<T> static_pointer_cast(MyScopePointer<U> const & r)
{
	return r.template staticCast<T>();
}

template<class T, class U>
inline MyScopePointer<T> dynamic_pointer_cast(MyScopePointer<U> const & r)
{
	return r.template dynamicCast<T>();
}

MY_END_NAMESPACE

#include "MyScopePointer.inl"

#endif