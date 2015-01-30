#ifndef __FORMATTRSYSTEM_H
#define __FORMATTRSYSTEM_H

#include <map>
#include "FormAttrItem.h"

class FormAttrSystem
{
protected:
	std::map<FormID, FormAttrItem*> m_id2FormAttrItemDic;

public:
	FormAttrSystem();
};

#endif				// __FORMATTRSYSTEM_H