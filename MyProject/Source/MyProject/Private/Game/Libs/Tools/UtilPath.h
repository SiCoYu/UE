#ifndef __UtilPath_H_
#define __UtilPath_H_

#include <string>

class UtilPath
{
public:
	// ���·����������Ŀ¼��Ŀǰֻ֧����������Ҫ�ļ������
	template<class T0, class T1>
	static std::string Combine(T0 param0, T1 param1);
};

#endif