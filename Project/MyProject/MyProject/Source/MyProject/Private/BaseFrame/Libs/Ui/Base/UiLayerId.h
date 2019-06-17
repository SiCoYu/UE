#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class UiLayerId
{
	eBtmLayer,                   // 最低层啊，一般不放东西，以备不时之需，目前放模糊的界面
	eFirstLayer,                 // 第一层，聊天之类的主界面窗口
	eSecondLayer,                // 第二层，主要是功能性的界面，弹出需要关闭的界面
	eThirdLayer,                 // 第三层，新手引导层
	eForthLayer,                 // 第四层，提示窗口层
	eTopLayer,                   // 最顶层，一般不放东西，以备不时之需

	eMaxLayer
};

MY_END_NAMESPACE