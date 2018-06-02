#ifndef __MyWeakPointer_H
#define __MyWeakPointer_H

//#include <memory>	// weak_ptr

//#define MyWeakPtr std::weak_ptr
#define MyWeakPtr std::weak_ptr

#include "MyPtrRefInfo.h"
#include "TypeDef.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

template<class T> 
class WeakPtr
{
	template<typename Y>
	friend class WeakPtr;

protected:
	T*             mRefPtr;
	PtrRefInfo* mRefInfo;

public:
	WeakPtr(T* rep) 
		: mRefPtr(rep), mRefInfo(MY_NEW PtrRefInfo)
	{

	}

public:
	WeakPtr() 
		: mRefPtr(0), mRefInfo(0)
	{}

public:
	template< class Y>
	explicit WeakPtr(Y* rep)
		: mRefPtr(rep)
	{

	}

	WeakPtr(const WeakPtr& r)
		: mRefPtr(r.mRefPtr)
		, mRefInfo(r.mRefInfo)
	{
		if (this->mRefPtr)
		{
			this->mRefInfo->mWeakRefCount.Increment();
		}
	}

	WeakPtr& operator=(const WeakPtr& r)
	{
		if (this->mRefInfo == r.mRefInfo)
		{
			return *this;
		}

		WeakPtr<T> tmp(r);
		swap(tmp);
		return *this;
	}

#if __cplusplus >= 201103L && !defined( __APPLE__ )
	template<class Y,
	class = typename std::enable_if<std::is_convertible<Y*, T*>::value>::type>
#else
	template<class Y>
#endif
	WeakPtr(const WeakPtr<Y>& r)
		: mRefPtr(r.mRefPtr)
		, mRefInfo(r.mRefInfo)
	{
		if (this->mRefPtr)
		{
			this->mRefInfo->mWeakRefCount.Increment();
		}
	}


#if __cplusplus >= 201103L && !defined( __APPLE__ )
	template<class Y,
	class = typename std::enable_if<std::is_assignable<T*, Y*>::value>::type>
#else
	template<class Y>
#endif
	WeakPtr& operator=(const WeakPtr<Y>& r)
	{
		if (this->mRefInfo == r.mRefInfo)
		{
			return *this;
		}

		WeakPtr<T> tmp(r);
		swap(tmp);
		return *this;
	}

	~WeakPtr() 
	{
		release();
	}

	template<typename Y>
	WeakPtr<Y> staticCast() const
	{
		if (this->mRefPtr)
		{
			this->mRefInfo->mWeakRefCount.Increment();
			return WeakPtr<Y>(static_cast<Y*>(this->mRefPtr), this->mRefInfo);
		}
		else
		{
			return WeakPtr<Y>();
		}
	}

	template<typename Y>
	WeakPtr<Y> dynamicCast() const
	{
		Y* rep = dynamic_cast<Y*>(this->mRefPtr);
		if (rep) 
		{
			this->mRefInfo->mWeakRefCount.Increment();
			return WeakPtr<Y>(rep, this->mRefInfo);
		}
		else
		{
			return WeakPtr<Y>();
		}
	}

	inline T& operator*() const 
	{ 
		my_assert(this->mRefPtr);
		return *this->mRefPtr;
	}

	inline T* operator->() const 
	{ 
		my_assert(this->mRefPtr);
		return this->mRefPtr;
	}

	inline T* get() const 
	{ 
		return this->mRefPtr;
	}

	void bind(T* rep) 
	{
		my_assert(!this->mRefPtr && !this->mRefInfo);
		this->mRefInfo = MY_NEW SharedPtrInfo;
		this->mRefPtr = rep;
	}

	inline bool unique() const 
	{ 
		my_assert(this->mRefInfo && this->mRefInfo->mWeakRefCount.get()); return this->mRefInfo->mWeakRefCount.get() == 1;
	}

	unsigned int getRefCount() const
	{ 
		my_assert(this->mRefInfo && this->mRefInfo->mWeakRefCount.GetValue()); return this->mRefInfo->mWeakRefCount.GetValue();
	}

	void setUseCount(unsigned value)
	{ 
		my_assert(this->mRefInfo); this->mRefInfo->mWeakRefCount.GetValue() = value;
	}

	T* getPointer() const 
	{ 
		return this->mRefPtr;
	}

	static void unspecified_bool(WeakPtr***)
	{
	}

	typedef void(*unspecified_bool_type)(WeakPtr***);

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
		WeakPtr(rep).swap(*this);
	}

protected:
	inline void release(void)
	{
		if (this->mRefPtr)
		{
			my_assert(mRefInfo);

			if (this->mRefInfo->mWeakRefCount.Decrement() == 0)
			{
				this->destroy();
			}
		}

		this->mRefPtr = 0;
		this->mRefInfo = 0;
	}

	inline void destroy(void)
	{
		my_assert(this->mRefPtr && this->mRefInfo);
		MY_DELETE this->mRefInfo;
	}

	inline void swap(WeakPtr<T> &other)
	{
		std::swap(this->mRefPtr, other.mRefPtr);
		std::swap(this->mRefInfo, other.mRefInfo);
	}
};

template<class T, class U> inline bool operator==(WeakPtr<T> const& a, WeakPtr<U> const& b)
{
	return a.get() == b.get();
}

template<class T, class U> inline bool operator!=(WeakPtr<T> const& a, WeakPtr<U> const& b)
{
	return a.get() != b.get();
}

template<class T, class U> inline bool operator<(WeakPtr<T> const& a, WeakPtr<U> const& b)
{
	return std::less<const void*>()(a.get(), b.get());
}

template<class T, class U>
inline WeakPtr<T> static_pointer_cast(WeakPtr<U> const & r)
{
	return r.template staticCast<T>();
}

template<class T, class U>
inline WeakPtr<T> dynamic_pointer_cast(WeakPtr<U> const & r)
{
	return r.template dynamicCast<T>();
}

MY_END_NAMESPACE

#include "MySharedPointer.inl"

#endif