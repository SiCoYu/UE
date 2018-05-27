#pragma once

#include <unordered_map>
#include <string>
#include "MyAllocRecordItem.h"

class FLowLevelMemTracker;

/**
 * @brief 检查并且记录内存使用，主要调试内存泄漏
 */
class MyMemoryTracker
{
	typedef std::unordered_map<void*, MyAllocRecordItem> AllocationMap;

protected:
	std::string mLeakFileName;
	bool mDumpToStdOut;
	AllocationMap mAllocations;

	size_t mTotalAllocations;
	bool mRecordEnable;

protected:
	MyMemoryTracker();

public:
	~MyMemoryTracker();

	void clear();
	void setReportFileName(const std::string& name);
	const std::string& getReportFileName() const;
	void setReportToStdOut(bool rep);

	bool getReportToStdOut() const;
	size_t getTotalMemoryAllocated() const;
	size_t getMemoryAllocatedForPool(unsigned int pool) const;
	void recordAlloc(
		void* ptr, 
		size_t sz,
		const char* file = 0, 
		size_t ln = 0, 
		const char* func = 0
	);

	void recordDealloc(void* ptr);
	void setRecordEnable(bool recordEnable);
	bool getRecordEnable() const;
	void reportLeaks();

	FLowLevelMemTracker& getNativeMemTracker();

	static MyMemoryTracker& get();
};