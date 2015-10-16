#include "MyProject.h"
#include "LocalFileSys.h"

LocalFileSys::LocalFileSys()
{
	
}

// 获取本地可以读取的目录，但是不能写
std::string LocalFileSys::getLocalReadDir()
{
	return "";
}

// 获取本地可以写的目录
std::string LocalFileSys::getLocalWriteDir()
{
	return m_persistentDataPath;
}