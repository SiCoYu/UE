#pragma once

//#include <memory>	// weak_ptr

//#define MyWeakPtr std::weak_ptr
#define MyWeakPtr std::weak_ptr

#include "MyPtrRefInfo.h"
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
		if (mRefPtr)
		{
			mRefInfo->mWeakRefCount.Increment();
		}
	}

	WeakPtr& operator=(const WeakPtr& r)
	{
		if (mRefInfo == r.mRefInfo)
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
		if (mRefPtr)
		{
			mRefInfo->mWeakRefCount.Increment();
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
		if (mRefInfo == r.mRefInfo)
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
		if (mRefPtr) 
		{
			mRefInfo->mWeakRefCount.Increment();
			return WeakPtr<Y>(static_cast<Y*>(mRefPtr), mRefInfo);
		}
		else
		{
			return WeakPtr<Y>();
		}
	}

	template<typename Y>
	WeakPtr<Y> dynamicCast() const
	{
		Y* rep = dynamic_cast<Y*>(mRefPtr);
		if (rep) 
		{
			mRefInfo->mWeakRefCount.Increment();
			return WeakPtr<Y>(rep, mRefInfo);
		}
		else
		{
			return WeakPtr<Y>();
		}
	}

	inline T& operator*() const 
	{ 
		assert(mRefPtr); 
		return *mRefPtr; 
	}

	inline T* operator->() const 
	{ 
		assert(mRefPtr); 
		return mRefPtr; 
	}

	inline T* get() const 
	{ 
		return mRefPtr; 
	}

	void bind(T* rep) 
	{
		assert(!mRefPtr && !mRefInfo);
		mRefInfo = MY_NEW SharedPtrInfo;
		mRefPtr = rep;
	}

	inline bool unique() const 
	{ 
		assert(mRefInfo && mRefInfo->mWeakRefCount.get()); return mRefInfo->mWeakRefCount.get() == 1; 
	}

	unsigned int getRefCount() const
	{ 
		assert(mRefInfo && mRefInfo->mWeakRefCount.GetValue()); return mRefInfo->mWeakRefCount.GetValue();
	}

	void setUseCount(unsigned value)
	{ 
		assert(mRefInfo); mRefInfo->mWeakRefCount.GetValue() = value; 
	}

	T* getPointer() const 
	{ 
		return mRefPtr; 
	}

	static void unspecified_bool(WeakPtr***)
	{
	}

	typedef void(*unspecified_bool_type)(WeakPtr***);

	operator unspecified_bool_type() const
	{
		return mRefPtr == 0 ? 0 : unspecified_bool;
	}

	bool isNull(void) const 
	{ 
		return mRefPtr == 0; 
	}

	void setNull() 
	{ 
		reset(); 
	}

	void reset(void) 
	{
		release();
	}

	void reset(T* rep) 
	{
		WeakPtr(rep).swap(*this);
	}

protected:
	inline void release(void)
	{
		if (mRefPtr)
		{
			assert(mRefInfo);
			if (mRefInfo->mWeakRefCount.Decrement() == 0)
			{
				destroy();
			}
		}

		mRefPtr = 0;
		mRefInfo = 0;
	}

	inline void destroy(void)
	{
		assert(mRefPtr && mRefInfo);
		MY_DELETE mRefInfo;
	}

	inline void swap(WeakPtr<T> &other)
	{
		std::swap(mRefPtr, other.mRefPtr);
		std::swap(mRefInfo, other.mRefInfo);
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