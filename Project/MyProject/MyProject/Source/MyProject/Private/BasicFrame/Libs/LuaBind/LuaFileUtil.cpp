#include <MyProject.h>
#include "LuaFileUtil.h"
#include <string.h>
#include "UtilStr.h"
#include "UtilPath.h"
#include "MyLuaLoader.h"

MY_BEGIN_NAMESPACE(MyNS)

LuaFileUtil::LuaFileUtil()
{
	this->mBufferSize = 0;
	this->mBuffer = nullptr;
}

void LuaFileUtil::init()
{

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
	}
}

std::string LuaFileUtil::_getLuaPath(std::string luaPackage)
{
	std::string fullPath = UtilStr.msDefaultStr;

	if (UtilStr::IsNullOrEmpty(fileName))
	{
		fullPath = UtilStr.msDefaultStr;
	}
	else
	{
		std::string old_value = ".";
		std::string new_value = "/";

		std::string replace = UtilStr::replaceAllDistinct(luaPackage, old_value, new_value);

		for (auto searchPath : this->mSearchPathList.getList())
		{
			fullPath = searchPath + replace + ".lua";

			if (UtilPath::FileExists(fullPath))
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

bool LuaFileUtil::AddSearchPath(std::string path, bool front = false)
{
	int index = this->mSearchPathList.IndexOf(path);

	if (index >= 0)
	{
		return false;
	}

	if (front)
	{
		this->mSearchPathList.Insert(0, path);
	}
	else
	{
		this->mSearchPathList.Add(path);
	}

	return true;
}

bool LuaFileUtil::RemoveSearchPath(std::string path)
{
	int index = this->mSearchPathList.IndexOf(path);

	if (index >= 0)
	{
		this->mSearchPathList.RemoveAt(index);
		return true;
	}

	return false;
}

std::string LuaFileUtil::FindFile(std::string fileName)
{
	return this->_getLuaPath();
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
		char* buffer = nullptr;

		if (nullptr != hFile)
		{
			fseek(hFile, 0, SEEK_END);
			error = ferror(hFile);
			size = ftell(hFile);
			error = ferror(hFile);
			fseek(hFile, 0, SEEK_SET);
			error = ferror(hFile);

			this->_mallocBuffer();

			size_t retSize = fread(this->mBuffer, size, 1, hFile);
			error = ferror(hFile);

			size = MyLuaLoader::removeZeroAndEof(buffer, size);
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