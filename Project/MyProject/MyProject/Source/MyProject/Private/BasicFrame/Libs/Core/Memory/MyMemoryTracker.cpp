#include "MyProject.h"
#include "MyMemoryTracker.h"
#include "PlatformDefine.h"

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
	: mLeakFileName("MyLeaks.log"), 
	 mDumpToStdOut(true),
	 mTotalAllocations(0), 
	 mRecordEnable(true)
{
}

MyMemoryTracker::~MyMemoryTracker()
{
	this->reportLeaks();

	this->mRecordEnable = false;
}

void MyMemoryTracker::setReportFileName(const std::string& name)
{
	this->mLeakFileName = name;
}

const std::string& MyMemoryTracker::getReportFileName() const
{
	return this->mLeakFileName;
}

void MyMemoryTracker::setReportToStdOut(bool rep)
{
	this->mDumpToStdOut = rep;
}

bool MyMemoryTracker::getReportToStdOut() const
{
	return this->mDumpToStdOut;
}

void MyMemoryTracker::setRecordEnable(bool recordEnable)
{
	this->mRecordEnable = recordEnable;
}

bool MyMemoryTracker::getRecordEnable() const
{
	return this->mRecordEnable;
}

void MyMemoryTracker::_recordAlloc(
	void* ptr, 
	size_t sz,
	const char* file,
	size_t ln, 
	const char* func
)
{
	if (this->mRecordEnable)
	{
		assert(this->mAllocations.find(ptr) == this->mAllocations.end() && "Double allocation with same address");

		this->mAllocations[ptr] = MyAllocRecordItem(
			sz, 
			file, 
			ln, 
			func
		);

		this->mTotalAllocations += sz;
	}
}

void MyMemoryTracker::_recordDealloc(void* ptr)
{
	if (this->mRecordEnable)
	{
		if (!ptr)
		{
			return;
		}

		AllocationMap::iterator i = this->mAllocations.find(ptr);
		assert(i != this->mAllocations.end() && "Unable to locate allocation unit - ");

		this->mTotalAllocations -= i->second.mBytes;
		this->mAllocations.erase(i);
	}
}

size_t MyMemoryTracker::getTotalMemoryAllocated() const
{
	return this->mTotalAllocations;
}

void MyMemoryTracker::reportLeaks()
{
	if (this->mRecordEnable)
	{
		std::stringstream os;

		if (this->mAllocations.empty())
		{
			os << "My Memory: No memory leaks" << std::endl;
		}
		else
		{
			os << "My Memory: Detected memory leaks !!! " << std::endl;
			os << "My Memory: (" << this->mAllocations.size() << ") Allocation(s) with total " << this->mTotalAllocations << " bytes." << std::endl;
			os << "My Memory: Dumping allocations -> " << std::endl;

			for (AllocationMap::const_iterator i = this->mAllocations.begin(); i != this->mAllocations.end(); ++i)
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

		if (this->mDumpToStdOut)
			My_OutputCString(os.str().c_str());

		std::ofstream of;
		of.open(this->mLeakFileName.c_str());
		of << os.str();
		of.close();
	}
}