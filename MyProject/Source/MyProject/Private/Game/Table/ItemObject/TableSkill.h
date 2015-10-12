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
	uint32 m_skillAttackEffect;    // 技能攻击特效
	float m_effectMoveTime;      // 移动
	int32 m_bNeedMove;             // 是否弹道特效, 0 不需要 1 需要

	virtual void TableSkillItemBody::parseBodyByteBuffer(ByteBuffer* bytes, uint32 offset);
};

#endif