#ifndef __TableSkill_H_
#define __TableSkill_H_

#include <string>
#include "HAL/Platform.h"
#include "TableItemBodyBase.h"

/**
    * @brief 技能基本表
    * // 添加一个表的步骤一
    */
class TableSkillItemBody : TableItemBodyBase
{
public:
    std::string m_name;               // 名称
	std::string m_effect;             // 效果
	std::string m_desc;               // 说明

	virtual void TableSkillItemBody::parseBodyByteArray(ByteBuffer* bytes, uint32 offset);
};

#endif