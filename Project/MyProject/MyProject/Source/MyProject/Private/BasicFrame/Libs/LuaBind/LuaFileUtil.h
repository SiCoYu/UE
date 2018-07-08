#pragma once

#pragma once

#include <string>
#include "GObject.h"
#include "MList.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class LuaFileUtil : public GObject
{
protected:
	MList<std::string> mSearchPathList;

	int mBufferSize;
	char* mBuffer;

public:
	LuaFileUtil();

	void init();
	void dispose();

	bool AddSearchPath(std::string path, bool front = false);
	bool RemoveSearchPath(std::string path);
	const char* ReadFile(std::string fileName, int& outSize);
	std::string FindFileError(std::string fileName);

protected:
	void _mallocBuffer(size_t size);
	std::string _getLuaPath(std::string luaPackage);
};

MY_END_NAMESPACE