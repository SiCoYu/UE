#include <MyProject.h>
#include "LuaFileUtil.h"
#include <string.h>
#include "UtilStr.h"
#include "UtilFileIO.h"
#include "MyLuaLoader.h"
#include "UtilFileIO.h"
#include "Containers/UnrealString.h"		// FString

MY_BEGIN_NAMESPACE(MyNS)

LuaFileUtil::LuaFileUtil()
{
	this->mBufferSize = 0;
	this->mBuffer = nullptr;
}

void LuaFileUtil::init()
{
	FString contentPath = UtilFileIO::GameContentDir();
	std::string path = UtilStr::ConvFString2StdStr(contentPath);
	std::string searchPath = "";

	searchPath = path + "MyAsset/Lua/";
	this->mSearchPathList.add(searchPath);

	searchPath = path + "MyAsset/Lua/Socket/";
	this->mSearchPathList.add(searchPath);

	searchPath = path + "MyAsset/Lua/ZeroBraneStudio/";
	this->mSearchPathList.add(searchPath);
}

void LuaFileUtil::dispose()
{
	this->mSearchPathList.clear();
}

void LuaFileUtil::_mallocBuffer(size_t size)
{
	if (this->mBufferSize >= size)
	{
		memset(this->mBuffer, 0, this->mBufferSize);
	}
	else
	{
		if (this->mBuffer)
		{
			delete[] this->mBuffer;
		}

		this->mBufferSize = 2 * size;
		this->mBuffer = new char[this->mBufferSize];
		memset(this->mBuffer, 0, this->mBufferSize);
	}
}

std::string LuaFileUtil::_getLuaPath(std::string luaPackage)
{
	std::string fullPath = UtilStr::msDefaultStr;

	if (UtilStr::IsNullOrEmpty(luaPackage))
	{
		fullPath = UtilStr::msDefaultStr;
	}
	else
	{
		std::string old_value = ".";
		std::string new_value = "/";

		std::string replace = UtilStr::replaceAllDistinct(luaPackage, old_value, new_value);

		for (auto searchPath : this->mSearchPathList.getList())
		{
			fullPath = searchPath + replace + ".lua";

			if (UtilFileIO::FileExists(fullPath))
			{
				break;
			}
			else
			{
				fullPath = "";
			}
		}
	}

	return fullPath;
}

bool LuaFileUtil::AddSearchPath(std::string path, bool front)
{
	int index = this->mSearchPathList.indexOf(path);

	if (index >= 0)
	{
		return false;
	}

	if (front)
	{
		this->mSearchPathList.insert(0, path);
	}
	else
	{
		this->mSearchPathList.add(path);
	}

	return true;
}

bool LuaFileUtil::RemoveSearchPath(std::string path)
{
	int index = this->mSearchPathList.indexOf(path);

	if (index >= 0)
	{
		this->mSearchPathList.removeAt(index);
		return true;
	}

	return false;
}

std::string LuaFileUtil::FindFile(std::string fileName)
{
	return this->_getLuaPath(fileName);
}

const char* LuaFileUtil::ReadFile(std::string fileName, int& outSize)
{
	fileName = this->_getLuaPath(fileName);

	if (0 == fileName.length())
	{
		return nullptr;
	}
	else
	{
		int retCode = 0;

		const char* fullPath = fileName.c_str();
		FILE* hFile = nullptr;

		/**
		* @url http://www.cplusplus.com/reference/cstdio/fopen/
		* In order to open a file as a binary file, a "b" character has to be included in the mode string.
		*/
		hFile = fopen(fullPath, "rb");
		int error = 0;
		int size = 0;

		if (nullptr != hFile)
		{
			fseek(hFile, 0, SEEK_END);
			error = ferror(hFile);
			size = ftell(hFile);
			error = ferror(hFile);
			fseek(hFile, 0, SEEK_SET);
			error = ferror(hFile);

			this->_mallocBuffer(size + 1);

			size_t retSize = fread(this->mBuffer, size, 1, hFile);
			error = ferror(hFile);

			size = MyLuaLoader::removeZeroAndEof(this->mBuffer, size);
			outSize = size;

			fclose(hFile);

			return this->mBuffer;
		}
		else
		{
			return nullptr;
		}
	}
}

std::string LuaFileUtil::FindFileError(std::string fileName)
{
	return fileName;
}

MY_END_NAMESPACE