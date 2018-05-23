#pragma once

#include "MyAllocRecordItem.h"

/**
 * @brief 检查并且记录内存使用，主要调试内存泄漏
 */
class MyMemoryTracker
{
protected:
	std::string mLeakFileName;
	bool mDumpToStdOut;
	typedef unordered_map<void*, Alloc>::type AllocationMap;
	AllocationMap mAllocations;

	size_t mTotalAllocations;
	typedef std::vector<size_t> AllocationsByPool;
	AllocationsByPool mAllocationsByPool;
	bool mRecordEnable;

	void reportLeaks();

	// protected ctor
	MemoryTracker()
		: mLeakFileName("OgreLeaks.log"), mDumpToStdOut(true),
		mTotalAllocations(0), mRecordEnable(true)
	{
	}
public:

	/** Set the name of the report file that will be produced on exit. */
	void setReportFileName(const std::string& name)
	{
		mLeakFileName = name;
	}
	/// Return the name of the file which will contain the report at exit
	const std::string& getReportFileName() const
	{
		return mLeakFileName;
	}
	/// Sets whether the memory report should be sent to stdout
	void setReportToStdOut(bool rep)
	{
		mDumpToStdOut = rep;
	}
	/// Gets whether the memory report should be sent to stdout
	bool getReportToStdOut() const
	{
		return mDumpToStdOut;
	}



	/// Get the total amount of memory allocated currently.
	size_t getTotalMemoryAllocated() const;
	/// Get the amount of memory allocated in a given pool
	size_t getMemoryAllocatedForPool(unsigned int pool) const;


	/** Record an allocation that has been made. Only to be called by
	the memory management subsystem.
	@param ptr The pointer to the memory
	@param sz The size of the memory in bytes
	@param pool The memory pool this allocation is occurring from
	@param file The file in which the allocation is being made
	@param ln The line on which the allocation is being made
	@param func The function in which the allocation is being made
	*/
	void _recordAlloc(void* ptr, size_t sz, unsigned int pool = 0,
		const char* file = 0, size_t ln = 0, const char* func = 0);
	/** Record the deallocation of memory. */
	void _recordDealloc(void* ptr);

	/// Sets whether the record alloc/dealloc enabled.
	void setRecordEnable(bool recordEnable)
	{
		mRecordEnable = recordEnable;
	}

	/// Gets whether the record alloc/dealloc enabled.
	bool getRecordEnable() const
	{
		return mRecordEnable;
	}

	~MemoryTracker()
	{
		reportLeaks();

		// Disable recording so we don't try to record our own deallocation.
		mRecordEnable = false;
	}

	/// Static utility method to get the memory tracker instance
	static MemoryTracker& get();
};