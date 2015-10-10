#ifndef __MsgCV_H
#define __MsgCV_H

namespace MsgCV
{
	//enum MsgCV
	enum
	{
		PACKET_ZIP_MIN = 32,
		PACKET_ZIP = 0x40000000,
		HEADER_SIZE = 4,   // 包长度占据几个字节
	};
}

#endif