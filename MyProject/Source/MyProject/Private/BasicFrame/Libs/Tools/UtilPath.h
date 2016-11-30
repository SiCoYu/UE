#ifndef __UtilPath_H_
#define __UtilPath_H_

#include <string>
#include <sstream>

class UtilPath
{
public:
	// ���·����������Ŀ¼��Ŀǰֻ֧����������Ҫ�ļ������
	template<class T0, class T1>
	static std::string Combine(T0 param0, T1 param1);

	static FString BaseDir();
	static FString RootDir();
	static FString GameDir();
	static FString GameContentDir();

	static FString GameSavedDir();
	static FString GameLogDir();
};

// ģ��ʵ��
#include "UtilPath.inl"

//template<class T0, class T1>
//static std::string UtilPath::Combine(T0 param0, T1 param1)
//{
//	std::stringstream strStream;
//	strStream << param0 << "/" << "param1";
//
//	return strStream.str();
//}

#endif