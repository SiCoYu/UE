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
* @brief ��ϵͳ string �ķ�װ
*/
class MString : public GObject
{
public:
	typedef std::string String;
	typedef String StringRef;
	typedef MString& MStringRef;

protected:
	std::string mString;
	int mUniqueId;       // Ψһ Id ������ʹ��

public:
	MString();
	~MString();

	StringRef getString();
	int getUniqueId();
	void setUniqueId(int value);
};

MY_END_NAMESPACE

#endif