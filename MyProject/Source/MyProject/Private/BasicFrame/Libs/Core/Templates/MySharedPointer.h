#pragma once

//#include "Templates/SharedPointer.h"	// TSharedPtr
#include <memory>	// shared_ptr

#define MySharedPtr std::shared_ptr
#define MyWeakPtr std::weak_ptr

#include "MThreadSafeCounter.h"

namespace MyNS
{
	struct SharedPtrInfo 
	{
		inline SharedPtrInfo()
			: useCount(1)
		{}

		virtual ~SharedPtrInfo() {}

		MThreadSafeCounter  useCount;
	};

	template<class T> 
	class SharedPtr
	{
		template<typename Y>friend class SharedPtr;
	protected:
		T*             pRep;
		SharedPtrInfo pInfo;

		SharedPtr(T* rep, SharedPtrInfo* info) 
			: pRep(rep), pInfo(info)
		{
		}

	public:
		SharedPtr() 
			: pRep(0), pInfo(0)
		{}

	public:
		template< class Y>
		explicit SharedPtr(Y* rep)
			: pRep(rep)
		{
		}

		SharedPtr(const SharedPtr& r)
			: pRep(r.pRep)
			, pInfo(r.pInfo)
		{
			if (pRep)
			{
				++pInfo->useCount;
			}
		}

		SharedPtr& operator=(const SharedPtr& r)
		{
			assert(pRep != r.pRep || pInfo == r.pInfo || dynamic_cast<SharedPtrInfoNone*>(pInfo) || dynamic_cast<SharedPtrInfoNone*>(r.pInfo));
			if (pInfo == r.pInfo)
				return *this;

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
			: pRep(r.pRep)
			, pInfo(r.pInfo)
		{
			if (pRep)
			{
				++pInfo->useCount;
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
			assert(pRep != r.pRep || pInfo == r.pInfo || dynamic_cast<SharedPtrInfoNone*>(pInfo) || dynamic_cast<SharedPtrInfoNone*>(r.pInfo));
			if (pInfo == r.pInfo)
				return *this;

			SharedPtr<T> tmp(r);
			swap(tmp);
			return *this;
		}

		~SharedPtr() {
			release();
		}

		template<typename Y>
		SharedPtr<Y> staticCast() const
		{
			if (pRep) {
				++pInfo->useCount;
				return SharedPtr<Y>(static_cast<Y*>(pRep), pInfo);
			}
			else return SharedPtr<Y>();
		}

		template<typename Y>
		SharedPtr<Y> dynamicCast() const
		{
			Y* rep = dynamic_cast<Y*>(pRep);
			if (rep) {
				++pInfo->useCount;
				return SharedPtr<Y>(rep, pInfo);
			}
			else return SharedPtr<Y>();
		}

		inline T& operator*() const { assert(pRep); return *pRep; }
		inline T* operator->() const { assert(pRep); return pRep; }
		inline T* get() const { return pRep; }

		void bind(T* rep, SharedPtrFreeMethod inFreeMethod = SPFM_DELETE) {
			assert(!pRep && !pInfo);
			pInfo = createInfoForMethod(rep, inFreeMethod);
			pRep = rep;
		}

		inline bool unique() const { assert(pInfo && pInfo->useCount.get()); return pInfo->useCount.get() == 1; }

		unsigned int useCount() const { return use_count(); }

		unsigned int use_count() const { assert(pInfo && pInfo->useCount.get()); return pInfo->useCount.get(); }

		void setUseCount(unsigned value) { assert(pInfo); pInfo->useCount = value; }

		T* getPointer() const { return pRep; }

		static void unspecified_bool(SharedPtr***)
		{
		}

		typedef void(*unspecified_bool_type)(SharedPtr***);

		operator unspecified_bool_type() const
		{
			return pRep == 0 ? 0 : unspecified_bool;
		}

		bool isNull(void) const { return pRep == 0; }

		void setNull() { reset(); }

		void reset(void) {
			release();
		}

		void reset(T* rep) {
			SharedPtr(rep).swap(*this);
		}

	protected:

		inline void release(void)
		{
			if (pRep)
			{
				assert(pInfo);
				if (--pInfo->useCount == 0)
					destroy();
			}

			pRep = 0;
			pInfo = 0;
		}

		inline void destroy(void)
		{
			assert(pRep && pInfo);
			OGRE_DELETE_T(pInfo, SharedPtrInfo, MEMCATEGORY_GENERAL);
		}

		inline void swap(SharedPtr<T> &other)
		{
			std::swap(pRep, other.pRep);
			std::swap(pInfo, other.pInfo);
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