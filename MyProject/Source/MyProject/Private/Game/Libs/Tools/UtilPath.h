#ifndef __UtilPath_H_
#define __UtilPath_H_

#include <string>

class UtilPath
{
public:
	// 结合路径到完整的目录，目前只支持两个，需要的继续添加
	template<class T0, class T1>
	static std::string Combine(T0 param0, T1 param1);
};

#endif