#ifndef __TableItemBase_H_
#define __TableItemBase_H_

/**
    * @brief 技能基本表
    * // 添加一个表的步骤一
    */
class TableSkillItemBody : TableItemBodyBase
{
    public string m_name;               // 名称
    public string m_effect;             // 效果
    public string m_desc;               // 说明

	override public void TableSkillItemBody::parseBodyByteArray(ByteArray bytes, uint offset);
};

#endif