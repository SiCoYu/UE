#ifndef __TableItemBase_H_
#define __TableItemBase_H_

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
    std::string m_prefab;      // 预制

    int32 m_chaoFeng;      // 嘲讽
    int32 m_chongFeng;     // 冲锋
    int32 m_fengNu;        // 风怒
    int32 m_qianXing;      // 潜行
    int32 m_shengDun;      // 圣盾

    int32 m_mpAdded;       // 魔法伤害增加
    int32 m_guoZai;        // 过载

    int32 m_faShu;         // 法术
    int32 m_zhanHou;       // 战吼
    int32 m_wangYu;        // 亡语
    int32 m_jiNu;          // 激怒
    uint8 m_bNeedFaShuTarget;     // 是否需要法术目标

	virtual void parseBodyByteArray(ByteBuffer* bytes, uint32 offset);
};

#endif