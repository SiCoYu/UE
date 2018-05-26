#pragma once

//#include "Templates/SharedPointer.h"	// TSharedPtr
//#include <memory>	// shared_ptr

//#define MySharedPtr std::shared_ptr
#define MySharedPtr MyNS::SharedPtr

#include "MyPtrRefInfo.h"
#include "TypeDef.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

namespace MyNS
{
	/**
	 * @error SharedPtr = nnullptr, 这样赋值是错误的，直接将 this->mRefPtr 设置为 nullptr ，导致内存泄漏，置空要是用 setNull 接口
	 * @error UE4 Object 一定不能使用 SharedPtr ，因为 UE4 有自己一套内存分配策略
	 */
	template<class T> 
	class SharedPtr
	{
		template<typename Y>
		friend class SharedPtr;

	protected:
		T*          mRefPtr;
		PtrRefInfo* mRefInfo;

	public:
		SharedPtr(T* rep) 
			: mRefPtr(rep), 
			  mRefInfo(MY_NEW PtrRefInfo)
		{

		}

	public:
		SharedPtr() 
			: mRefPtr(0), 
			  mRefInfo(0)
		{}

	public:
		//template< class Y>
		//explicit SharedPtr(Y* rep)
		//	: mRefPtr(rep)
		//{

		//}

		SharedPtr(const SharedPtr& r)
			: mRefPtr(r.mRefPtr)
			, mRefInfo(r.mRefInfo)
		{
			if (this->mRefPtr)
			{
				this->mRefInfo->mRefCount.Increment();
			}
		}

		SharedPtr& operator=(const SharedPtr& r)
		{
			if (this->mRefInfo == r.mRefInfo)
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
			if (this->mRefPtr)
			{
				this->mRefInfo->mRefCount.Increment();
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
			if (this->mRefInfo == r.mRefInfo)
			{
				return *this;
			}

			SharedPtr<T> tmp(r);
			swap(tmp);
			return *this;
		}

		~SharedPtr() 
		{
			this->release();
		}

		template<typename Y>
		SharedPtr<Y> staticCast() const
		{
			if (this->mRefPtr)
			{
				this->mRefInfo->mRefCount.Increment();
				return SharedPtr<Y>(static_cast<Y*>(this->mRefPtr), this->mRefInfo);
			}
			else
			{
				return SharedPtr<Y>();
			}
		}

		template<typename Y>
		SharedPtr<Y> dynamicCast() const
		{
			Y* rep = dynamic_cast<Y*>(this->mRefPtr);
			if (rep) 
			{
				this->mRefInfo->mRefCount.Increment();
				return SharedPtr<Y>(rep, this->mRefInfo);
			}
			else
			{
				return SharedPtr<Y>();
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
			my_assert(this->mRefInfo && this->mRefInfo->mRefCount.get());
			return this->mRefInfo->mRefCount.get() == 1;
		}

		unsigned int getRefCount() const
		{ 
			my_assert(this->mRefInfo && this->mRefInfo->mRefCount.GetValue());
			return this->mRefInfo->mRefCount.GetValue();
		}

		void setUseCount(unsigned value)
		{ 
			my_assert(this->mRefInfo);
			this->mRefInfo->mRefCount.GetValue() = value;
		}

		T* getPointer() const 
		{ 
			return this->mRefPtr;
		}

		static void unspecified_bool(SharedPtr***)
		{
		}

		typedef void(*unspecified_bool_type)(SharedPtr***);

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
			SharedPtr(rep).swap(*this);
		}

	protected:
		inline void release(void)
		{
			if (this->mRefPtr)
			{
				my_assert(this->mRefInfo);

				if (this->mRefInfo->mRefCount.Decrement() == 0)
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
			MY_DELETE this->mRefPtr;
			MY_DELETE this->mRefInfo;
		}

		inline void swap(SharedPtr<T> &other)
		{
			std::swap(this->mRefPtr, other.mRefPtr);
			std::swap(this->mRefInfo, other.mRefInfo);
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