#ifndef __MString_H
#define __MString_H

#include <string>
#include "Ctx.h"
#include "LogSys.h"
#include "UtilStr.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
* @brief 对系统 string 的封装
*/
class MString : public GObject
{
public:
	typedef std::string String;
	typedef String StringRef;
	typedef MString& MStringRef;

protected:
	std::string mString;
	int mUniqueId;       // 唯一 Id ，调试使用

public:
	MString();
	~MString();

	StringRef getString();
	int getUniqueId();
	void setUniqueId(int value);
};

MY_END_NAMESPACE

#endif