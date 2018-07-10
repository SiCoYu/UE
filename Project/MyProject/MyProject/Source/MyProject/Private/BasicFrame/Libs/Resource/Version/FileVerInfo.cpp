#include "MyProject.h"
#include "FileVerInfo.h"

MY_BEGIN_NAMESPACE(MyNS)

bool FileVerInfo::isNoVerInfo()
{
	return this->mFileSize == 0;
}

MY_END_NAMESPACE