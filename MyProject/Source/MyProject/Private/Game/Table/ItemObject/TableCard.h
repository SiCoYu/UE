#ifndef __TableCard_H_
#define __TableCard_H_

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

class ByteBuffer;

/**
    * @brief 卡牌基本表
    */
class TableCardItemBody : TableItemBodyBase
{
public:
	std::string m_name;        // 名称
	int32 m_type;           // 类型
	int32 m_career;         // 职业
	int32 m_race;           // 种族
	int32 m_quality;        // 品质

	int32 m_magicConsume;   // 魔法消耗
	int32 m_attack;         // 攻击力
	int32 m_hp;             // 血量
	int32 m_Durable;        // 耐久

	int32 m_chaoFeng;      // 嘲讽
	int32 m_chongFeng;     // 冲锋
	int32 m_fengNu;        // 风怒
	int32 m_qianXing;      // 潜行
	int32 m_shengDun;      // 圣盾

	int32 m_mpAdded;       // 魔法伤害增加
	int32 m_guoZai;        // 过载

	int32 m_faShu;         // 法术
	int32 m_zhanHou;       // 战吼
	uint8 m_bNeedFaShuTarget;     // 是否需要法术目标，这个是出牌后是否需要选择目个技能是否需要在目标位置释放，需要看技能表
	int32 m_bNeedZhanHouTarget;    // 战吼需要目标
	std::string m_cardDesc;           // 卡牌描述
	std::string m_cardHeader;         // 卡牌头像贴图路径，卡牌模型中头像

	std::string m_cardSetCardHeader;    // 卡牌头像贴图路径，卡组中卡牌资源
	std::string m_dzCardHeader;         // 卡牌头像贴图路径，对战中卡牌图像
	uint32 m_skillPrepareEffect;     // 技能攻击准备特效

	virtual void parseBodyByteBuffer(ByteBuffer* bytes, uint32 offset);
};

#endif