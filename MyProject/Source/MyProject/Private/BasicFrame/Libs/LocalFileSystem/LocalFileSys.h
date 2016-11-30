#ifndef __LocalFileSys_H
#define __LocalFileSys_H

#include <string>

class LoadParam;

/**
    * @brief 本地文件系统
    */
class LocalFileSys
{
protected:
	std::string m_persistentDataPath;

public:
	LocalFileSys();
    // 获取本地可以读取的目录，但是不能写
	std::string getLocalReadDir();
    // 获取本地可以写的目录
	std::string getLocalWriteDir();
	// 获取真正的加载参数
	static void modifyLoadParam(std::string resPath, LoadParam* param);
};

#endif