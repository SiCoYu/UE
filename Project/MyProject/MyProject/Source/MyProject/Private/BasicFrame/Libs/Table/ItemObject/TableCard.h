#ifndef __TableCard_H
#define __TableCard_H

#include <string>

/**
 * @brief 卡表中的属性名字
 */

class TableCardAttrName
{
public:
    const std::string ChaoFeng = "嘲讽";
	const std::string ChongFeng = "冲锋";
	const std::string FengNu = "风怒";
	const std::string QianXing = "潜行";
	const std::string ShengDun = "圣盾";

	const std::string MoFaXiaoHao = "魔法消耗";
	const std::string GongJiLi = "攻击力";
	const std::string Xueliang = "血量";
	const std::string NaiJiu = "耐久";
	const std::string FaShuShangHai = "法术伤害增加";
	const std::string GuoZai = "过载";
};

#include "MyProject.h"
#include "TableItemBodyBase.h"

class MByteBuffer;

/**
    * @brief 卡牌基本表
    */
class TableCardItemBody : TableItemBodyBase
{
public:
	std::string mName;        // 名称
	int32 mType;           // 类型
	int32 mCareer;         // 职业
	int32 mRace;           // 种族
	int32 mQuality;        // 品质

	int32 mMagicConsume;   // 魔法消耗
	int32 mAttack;         // 攻击力
	int32 mHp;             // 血量
	int32 mDurable;        // 耐久

	int32 mChaoFeng;      // 嘲讽
	int32 mChongFeng;     // 冲锋
	int32 mFengNu;        // 风怒
	int32 mQianXing;      // 潜行
	int32 mShengDun;      // 圣盾

	int32 mMpAdded;       // 魔法伤害增加
	int32 mGuoZai;        // 过载

	int32 mFaShu;         // 法术
	int32 mZhanHou;       // 战吼
	uint8 mIsNeedFaShuTarget;     // 是否需要法术目标，这个是出牌后是否需要选择目个技能是否需要在目标位置释放，需要看技能表
	int32 mIsNeedZhanHouTarget;    // 战吼需要目标
	std::string mCardDesc;           // 卡牌描述
	std::string mCardHeader;         // 卡牌头像贴图路径，卡牌模型中头像

	std::string mCardSetCardHeader;    // 卡牌头像贴图路径，卡组中卡牌资源
	std::string mDzCardHeader;         // 卡牌头像贴图路径，对战中卡牌图像
	uint32 mSkillPrepareEffect;     // 技能攻击准备特效

	TableCardItemBody();
	virtual ~TableCardItemBody();

	virtual void parseBodyByteBuffer(MByteBuffer* bytes, uint32 offset);
};

#endif