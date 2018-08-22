#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>		// ifstream
#include <fstream>

int loadLuaFromFile(std::string fileName)
{
	if (0 == fileName.length())
	{
		return 1;
	}

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
		//rewind(hFile);
		error = ferror(hFile);

		buffer = new char[size];
		memset(buffer, 0, size);
		size_t retSize = fread(buffer, size, 1, hFile);
		error = ferror(hFile);

		//size = 800;
		//buffer = new char[size];

		//std::ifstream infile;
		//infile.open(fileName, std::ios::binary);
		//infile.read(buffer, size);

		delete[] buffer;
		fclose(hFile);
	}

	return retCode;
}

void main()
{
	loadLuaFromFile("G:/UE/Project/MyProject/MyProject/Content/MyAsset/Lua/MyLua/Module/Entry/MainEntry.lua");
	//loadLuaFromFile("G:/UE/Test/TestFile/Src/aaa.txt");
}