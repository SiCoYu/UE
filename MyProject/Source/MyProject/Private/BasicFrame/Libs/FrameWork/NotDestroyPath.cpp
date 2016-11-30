﻿#include "MyProject.h"
#include "NotDestroyPath.h"

std::string NotDestroyPath::ND_CV_Root = "NoDestroy";

std::string NotDestroyPath::ND_CV_App = "App";       // 注意这个地方不是 "App" ，实例化的一定要加 (Clone)，目前将名字改成了 App 了，直接 App 就能获取，目前在 Start 模块直接修改成 App 了，因此使用 App 
std::string NotDestroyPath::ND_CV_Game = "Game";

std::string NotDestroyPath::ND_CV_UICanvas_50 = "UICanvas_50";            // 这个是 UI ，需要屏幕自适应的
std::string NotDestroyPath::ND_CV_UICanvas_100 = "UICanvas_100";          // 这个是 UI ，需要屏幕自适应的
std::string NotDestroyPath::ND_CV_UICamera = "UICamera";

// 界面层，层越小越在最后面显示
std::string NotDestroyPath::ND_CV_UIBtmLayer_Canvas_50 = "UICanvas_50/UIBtmLayer";         // 界面最底层
std::string NotDestroyPath::ND_CV_UIFirstLayer_Canvas_50 = "UICanvas_50/UIFirstLayer";     // 界面第一层
std::string NotDestroyPath::ND_CV_UISecondLayer_Canvas_50 = "UICanvas_50/UISecondLayer";   // 界面第二层
std::string NotDestroyPath::ND_CV_UIThirdLayer_Canvas_50 = "UICanvas_50/UIThirdLayer";     // 界面第三层
std::string NotDestroyPath::ND_CV_UIForthLayer_Canvas_50 = "UICanvas_50/UIForthLayer";     // 界面第四层
std::string NotDestroyPath::ND_CV_UITopLayer_Canvas_50 = "UICanvas_50/UITopLayer";         // 界面最顶层

std::string NotDestroyPath::ND_CV_UIBtmLayer_Canvas_100 = "UICanvas_100/UIBtmLayer";         // 界面最底层
std::string NotDestroyPath::ND_CV_UIFirstLayer_Canvas_100 = "UICanvas_100/UIFirstLayer";     // 界面第一层
std::string NotDestroyPath::ND_CV_UISecondLayer_Canvas_100 = "UICanvas_100/UISecondLayer";   // 界面第二层
std::string NotDestroyPath::ND_CV_UIThirdLayer_Canvas_100 = "UICanvas_100/UIThirdLayer";     // 界面第三层
std::string NotDestroyPath::ND_CV_UIForthLayer_Canvas_100 = "UICanvas_100/UIForthLayer";     // 界面第四层
std::string NotDestroyPath::ND_CV_UITopLayer_Canvas_100 = "UICanvas_100/UITopLayer";         // 界面最顶层

std::string NotDestroyPath::ND_CV_EventSystem = "EventSystem";

std::string NotDestroyPath::ND_CV_UIModel = "UIModel";
std::string NotDestroyPath::ND_CV_UILight = "UIModel/DirectionalLight";