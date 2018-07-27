#ifndef __TableSkill_H
#define __TableSkill_H

#include <string>
#include "HAL/Platform.h"
#include "TableItemBodyBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
    * @brief 技能基本表
    * // 添加一个表的步骤一
    */
class TableSkillItemBody : public TableItemBodyBase
{
public:
	std::string mName;               // 名称
	std::string mEffect;             // 效果
	uint32 mSkillAttackEffect;    // 技能攻击特效
	float mEffectMoveTime;      // 移动
	int32 mIsNeedMove;             // 是否弹道特效, 0 不需要 1 需要

	TableSkillItemBody();
	virtual ~TableSkillItemBody();

	virtual void parseBodyByteBuffer(MByteBuffer* bytes, uint32 offset);
};

MY_END_NAMESPACE

#endif