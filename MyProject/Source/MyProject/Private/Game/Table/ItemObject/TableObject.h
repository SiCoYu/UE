#ifndef __TableItemBase_H_
#define __TableItemBase_H_

class TableObjectItemBody : TableItemBodyBase
{
    public string m_name;
    public int m_maxNum;
    public int m_type;
    public int m_color;
    public string m_prefab;

	override public void parseBodyByteArray(ByteArray bytes, uint offset);
	public string path;
};

#endif