#include "MyProject.h"
#include "MyMemoryTracker.h"

//#include <iostream>
#include <fstream>	// ofstream
#include <sstream>
#include <assert.h>

#if MY_PLATFORM == MY_PLATFORM_WIN32 || MY_PLATFORM == MY_PLATFORM_WINRT
#   include <windows.h>
#   define My_OutputCString(str) ::OutputDebugStringA(str)
#   define My_OutputWString(str) ::OutputDebugStringW(str)
#else
#   define My_OutputCString(str) std::cerr << str
#   define My_OutputWString(str) std::cerr << str
#endif

MyMemoryTracker& MyMemoryTracker::get()
{
	static MyMemoryTracker GMemoryTracker;
	return GMemoryTracker;
}

MyMemoryTracker::MyMemoryTracker()
	: mLeakFileName("MyLeaks.log"), mDumpToStdOut(true),
	mTotalAllocations(0), mRecordEnable(true)
{
}

MyMemoryTracker::~MyMemoryTracker()
{
	reportLeaks();

	mRecordEnable = false;
}

void MyMemoryTracker::setReportFileName(const std::string& name)
{
	mLeakFileName = name;
}

const std::string& MyMemoryTracker::getReportFileName() const
{
	return mLeakFileName;
}

void MyMemoryTracker::setReportToStdOut(bool rep)
{
	mDumpToStdOut = rep;
}

bool MyMemoryTracker::getReportToStdOut() const
{
	return mDumpToStdOut;
}

void MyMemoryTracker::setRecordEnable(bool recordEnable)
{
	mRecordEnable = recordEnable;
}

bool MyMemoryTracker::getRecordEnable() const
{
	return mRecordEnable;
}

void MyMemoryTracker::_recordAlloc(
	void* ptr, 
	size_t sz,
	const char* file,
	size_t ln, 
	const char* func
)
{
	if (mRecordEnable)
	{
		assert(mAllocations.find(ptr) == mAllocations.end() && "Double allocation with same address - ");

		mAllocations[ptr] = MyAllocRecordItem(
			sz, 
			file, 
			ln, 
			func
		);

		mTotalAllocations += sz;
	}
}

void MyMemoryTracker::_recordDealloc(void* ptr)
{
	if (mRecordEnable)
	{
		if (!ptr)
			return;

		AllocationMap::iterator i = mAllocations.find(ptr);
		assert(i != mAllocations.end() && "Unable to locate allocation unit - ");

		mTotalAllocations -= i->second.mBytes;
		mAllocations.erase(i);
	}
}

size_t MyMemoryTracker::getTotalMemoryAllocated() const
{
	return mTotalAllocations;
}

void MyMemoryTracker::reportLeaks()
{
	if (mRecordEnable)
	{
		std::stringstream os;

		if (mAllocations.empty())
		{
			os << "My Memory: No memory leaks" << std::endl;
		}
		else
		{
			os << "My Memory: Detected memory leaks !!! " << std::endl;
			os << "My Memory: (" << mAllocations.size() << ") Allocation(s) with total " << mTotalAllocations << " bytes." << std::endl;
			os << "My Memory: Dumping allocations -> " << std::endl;

			for (AllocationMap::const_iterator i = mAllocations.begin(); i != mAllocations.end(); ++i)
			{
				const MyAllocRecordItem& alloc = i->second;
				if (!alloc.mFileName.empty())
					os << alloc.mFileName;
				else
					os << "(unknown source):";

				os << "(" << alloc.mLine << ") : {" << alloc.mBytes << " bytes}" << " function: " << alloc.mFunction << std::endl;

			}
			os << std::endl;
		}

		if (mDumpToStdOut)
			My_OutputCString(os.str().c_str());

		std::ofstream of;
		of.open(mLeakFileName.c_str());
		of << os.str();
		of.close();
	}
}