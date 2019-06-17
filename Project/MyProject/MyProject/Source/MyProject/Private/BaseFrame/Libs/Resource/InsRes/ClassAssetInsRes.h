#ifndef __ClassAssetInsRes_H
#define __ClassAssetInsRes_H

#include "ObjectAssetInsResBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ClassAssetInsRes : public ObjectAssetInsResBase
{
	M_DECLARE_CLASS(ClassAssetInsRes, ObjectAssetInsResBase)

public:
	ClassAssetInsRes();
	// warning C4265: 'ClassAssetInsRes': class has virtual functions, but destructor is not virtual instances of this class may not be destructed correctly
	virtual ~ClassAssetInsRes();
};

MY_END_NAMESPACE

#endif