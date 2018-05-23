#include "MyProject.h"
#include "MyMemoryTracker.h"

#include <iostream>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WINRT
#   include <windows.h>
#   define Ogre_OutputCString(str) ::OutputDebugStringA(str)
#   define Ogre_OutputWString(str) ::OutputDebugStringW(str)
#else
#   define Ogre_OutputCString(str) std::cerr << str
#   define Ogre_OutputWString(str) std::cerr << str
#endif

MyMemoryTracker& MyMemoryTracker::get()
{
	static MyMemoryTracker GMemoryTracker;
	return GMemoryTracker;
}

void MemoryTracker::_recordAlloc(void* ptr, size_t sz, unsigned int pool,
	const char* file, size_t ln, const char* func)
{
	if (mRecordEnable)
	{
		OGRE_LOCK_AUTO_MUTEX;

		assert(mAllocations.find(ptr) == mAllocations.end() && "Double allocation with same address - "
			"this probably means you have a mismatched allocation / deallocation style, "
			"check if you're are using OGRE_ALLOC_T / OGRE_FREE and OGRE_NEW_T / OGRE_DELETE_T consistently");

		mAllocations[ptr] = Alloc(sz, pool, file, ln, func);
		if (pool >= mAllocationsByPool.size())
			mAllocationsByPool.resize(pool + 1, 0);
		mAllocationsByPool[pool] += sz;
		mTotalAllocations += sz;
	}

}

void MemoryTracker::_recordDealloc(void* ptr)
{
	if (mRecordEnable)
	{
		// deal cleanly with null pointers
		if (!ptr)
			return;

		OGRE_LOCK_AUTO_MUTEX;

		AllocationMap::iterator i = mAllocations.find(ptr);
		assert(i != mAllocations.end() && "Unable to locate allocation unit - "
			"this probably means you have a mismatched allocation / deallocation style, "
			"check if you're are using OGRE_ALLOC_T / OGRE_FREE and OGRE_NEW_T / OGRE_DELETE_T consistently");
		// update category stats
		mAllocationsByPool[i->second.pool] -= i->second.bytes;
		// global stats
		mTotalAllocations -= i->second.bytes;
		mAllocations.erase(i);
	}
}

size_t MemoryTracker::getTotalMemoryAllocated() const
{
	return mTotalAllocations;
}

size_t MemoryTracker::getMemoryAllocatedForPool(unsigned int pool) const
{
	return mAllocationsByPool[pool];
}

void MemoryTracker::reportLeaks()
{
	if (mRecordEnable)
	{
		StringStream os;

		if (mAllocations.empty())
		{
			os << "Ogre Memory: No memory leaks" << std::endl;
		}
		else
		{
			os << "Ogre Memory: Detected memory leaks !!! " << std::endl;
			os << "Ogre Memory: (" << mAllocations.size() << ") Allocation(s) with total " << mTotalAllocations << " bytes." << std::endl;
			os << "Ogre Memory: Dumping allocations -> " << std::endl;


			for (AllocationMap::const_iterator i = mAllocations.begin(); i != mAllocations.end(); ++i)
			{
				const Alloc& alloc = i->second;
				if (!alloc.filename.empty())
					os << alloc.filename;
				else
					os << "(unknown source):";

				os << "(" << alloc.line << ") : {" << alloc.bytes << " bytes}" << " function: " << alloc.function << std::endl;

			}
			os << std::endl;
		}

		if (mDumpToStdOut)
			Ogre_OutputCString(os.str().c_str());

		std::ofstream of;
		of.open(mLeakFileName.c_str());
		of << os.str();
		of.close();
	}
}