#pragma once

//#include "Templates/SharedPointer.h"	// TSharedPtr
//#include <memory>	// shared_ptr

//#define MySharedPtr std::shared_ptr
#define MySharedPtr MyNS::SharedPtr
#define MyWeakPtr std::weak_ptr

#include "MThreadSafeCounter.h"

namespace MyNS
{
	struct SharedPtrInfo 
	{
		inline SharedPtrInfo()
			: mRefCount(1)
		{}

		virtual ~SharedPtrInfo() {}

		MThreadSafeCounter mRefCount;
	};

	template<class T> 
	class SharedPtr
	{
		template<typename Y>
		friend class SharedPtr;

	protected:
		T*             mRefPtr;
		SharedPtrInfo* mRefInfo;

	public:
		SharedPtr(T* rep) 
			: mRefPtr(rep), mRefInfo(new SharedPtrInfo)
		{

		}

	public:
		SharedPtr() 
			: mRefPtr(0), mRefInfo(0)
		{}

	public:
		template< class Y>
		explicit SharedPtr(Y* rep)
			: mRefPtr(rep)
		{

		}

		SharedPtr(const SharedPtr& r)
			: mRefPtr(r.mRefPtr)
			, mRefInfo(r.mRefInfo)
		{
			if (mRefPtr)
			{
				mRefInfo->mRefCount.Increment();
			}
		}

		SharedPtr& operator=(const SharedPtr& r)
		{
			if (mRefInfo == r.mRefInfo)
			{
				return *this;
			}

			SharedPtr<T> tmp(r);
			swap(tmp);
			return *this;
		}

	#if __cplusplus >= 201103L && !defined( __APPLE__ )
		template<class Y,
		class = typename std::enable_if<std::is_convertible<Y*, T*>::value>::type>
	#else
		template<class Y>
	#endif
		SharedPtr(const SharedPtr<Y>& r)
			: mRefPtr(r.mRefPtr)
			, mRefInfo(r.mRefInfo)
		{
			if (mRefPtr)
			{
				mRefInfo->mRefCount.Increment();
			}
		}


	#if __cplusplus >= 201103L && !defined( __APPLE__ )
		template<class Y,
		class = typename std::enable_if<std::is_assignable<T*, Y*>::value>::type>
	#else
		template<class Y>
	#endif
		SharedPtr& operator=(const SharedPtr<Y>& r)
		{
			if (mRefInfo == r.mRefInfo)
			{
				return *this;
			}

			SharedPtr<T> tmp(r);
			swap(tmp);
			return *this;
		}

		~SharedPtr() 
		{
			release();
		}

		template<typename Y>
		SharedPtr<Y> staticCast() const
		{
			if (mRefPtr) 
			{
				mRefInfo->mRefCount.Increment();
				return SharedPtr<Y>(static_cast<Y*>(mRefPtr), mRefInfo);
			}
			else
			{
				return SharedPtr<Y>();
			}
		}

		template<typename Y>
		SharedPtr<Y> dynamicCast() const
		{
			Y* rep = dynamic_cast<Y*>(mRefPtr);
			if (rep) 
			{
				mRefInfo->mRefCount.Increment();
				return SharedPtr<Y>(rep, mRefInfo);
			}
			else
			{
				return SharedPtr<Y>();
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
			mRefInfo = new SharedPtrInfo;
			mRefPtr = rep;
		}

		inline bool unique() const 
		{ 
			assert(mRefInfo && mRefInfo->mRefCount.get()); return mRefInfo->mRefCount.get() == 1; 
		}

		unsigned int getRefCount() const
		{ 
			assert(mRefInfo && mRefInfo->mRefCount.GetValue()); return mRefInfo->mRefCount.GetValue();
		}

		void setUseCount(unsigned value)
		{ 
			assert(mRefInfo); mRefInfo->mRefCount.GetValue() = value; 
		}

		T* getPointer() const 
		{ 
			return mRefPtr; 
		}

		static void unspecified_bool(SharedPtr***)
		{
		}

		typedef void(*unspecified_bool_type)(SharedPtr***);

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
			SharedPtr(rep).swap(*this);
		}

	protected:
		inline void release(void)
		{
			if (mRefPtr)
			{
				assert(mRefInfo);
				if (mRefInfo->mRefCount.Decrement() == 0)
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
			delete mRefInfo;
		}

		inline void swap(SharedPtr<T> &other)
		{
			std::swap(mRefPtr, other.mRefPtr);
			std::swap(mRefInfo, other.mRefInfo);
		}
	};

	template<class T, class U> inline bool operator==(SharedPtr<T> const& a, SharedPtr<U> const& b)
	{
		return a.get() == b.get();
	}

	template<class T, class U> inline bool operator!=(SharedPtr<T> const& a, SharedPtr<U> const& b)
	{
		return a.get() != b.get();
	}

	template<class T, class U> inline bool operator<(SharedPtr<T> const& a, SharedPtr<U> const& b)
	{
		return std::less<const void*>()(a.get(), b.get());
	}

	template<class T, class U>
	inline SharedPtr<T> static_pointer_cast(SharedPtr<U> const & r)
	{
		return r.template staticCast<T>();
	}

	template<class T, class U>
	inline SharedPtr<T> dynamic_pointer_cast(SharedPtr<U> const & r)
	{
		return r.template dynamicCast<T>();
	}
}