#include "MyProject.h"
#include "UMGForm.h"
#include "Common.h"
#include "EngineApi.h"
#include "PointF.h"
#include "WindowAnchor.h"

void UForm::loadUWidget(const TCHAR* name)
{
	UClass* widgetClass = StaticLoadClass(UUserWidget::StaticClass(), NULL, name);
	if (widgetClass != NULL)
	{
		//m_umgWidget = Cast<UUserWidget>(StaticConstructObject(widgetClass, GEngine->GameViewport->GetWorld()->GetGameInstance()));
		//m_umgWidget = Cast<UUserWidget>(StaticConstructObject(widgetClass, MyCtx::getSingletonPtr()->getGameInstance()));

		// warning C4996: 'StaticConstructObject': StaticConstructObject is deprecated, please use NewObject instead. For internal CoreUObject module usage, please use StaticConstructObject_Internal. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
		//m_umgWidget = Cast<UUserWidget>(StaticConstructObject(widgetClass, Ctx::getSingletonPtr()->getEngineApi()->getGameInstance()));
		// 直接构造一个抽象类是报错误的
		// NewObject<UUserWidget>();
		// 构造一个类的子类，最新的 api 如下就可以了
		m_GUIWin->m_uiRoot = NewObject<UUserWidget>(g_pEngineApi->getGameInstance(), widgetClass);
	}
}

UForm::UForm()
	:UWindow()
{
	m_exitMode = true;
	m_bHideOnCreate = false;
	m_bLoadWidgetRes = false;
	m_bReady = false;
	m_bBlurBg = false;
	m_bHandleExitBtn = false;
	m_alignVertial = (int)CENTER;
	m_alignHorizontal = (int)CENTER;
}

UIFormID UForm::getID()
{
	return m_id;
}

void UForm::setID(UIFormID value)
{
	m_id = value;
}

bool UForm::getHideOnCreate()
{
	return m_bHideOnCreate;
}

void UForm::setHideOnCreate(bool value)
{
	m_bHideOnCreate = value;
}

bool UForm::getExitMode()
{
	return m_exitMode;
}

void UForm::setExitMode(bool value)
{
	m_exitMode = value;
}

bool UForm::getLoadWidgetRes()
{
	return m_bLoadWidgetRes;
}

void UForm::setBLoadWidgetRes(bool value)
{
	m_bLoadWidgetRes = true;
}

bool UForm::getBReady()
{
	return m_bReady;
}

std::string UForm::getFormName()
{
	return m_formName;
}

void UForm::setFormName(std::string value)
{
	m_formName = value;
}

//LuaCSBridgeForm* UForm::getLuaCSBridgeForm()
//{
//	return m_luaCSBridgeForm;
//}

//void UForm::getLuaCSBridgeForm(LuaCSBridgeForm* value)
//{
//	m_luaCSBridgeForm = value;
//}

void UForm::init()
{
	onInit();
}

void UForm::show()
{
	g_pUIMgr->showForm(m_id);
}

//private void UForm::hide()
//{
//    g_pUIMgr->hideForm(m_id);
//}

void UForm::exit()
{
	g_pUIMgr->exitForm(m_id);
}

// 界面代码创建后就调用
void UForm::onInit()
{
	//if (m_luaCSBridgeForm != null)
	//{
	//	m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_INIT);
	//}
	//if (m_bLoadWidgetRes)
	//{
	// 默认会继续加载资源
	g_pUIMgr->loadWidgetRes(this->getID());
	//}
}

// 第一次显示之前会调用一次
void UForm::onReady()
{
	//if (m_luaCSBridgeForm != null)
	//{
	//	m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_READY);
	//}

	m_bReady = true;
	if (m_bHandleExitBtn)
	{
		//UtilApi.addEventHandle(m_GUIWin.m_uiRoot, "BtnClose", onExitBtnClick); // 关闭事件
	}
}

// 每一次显示都会调用一次
void UForm::onShow()
{
	//if (m_luaCSBridgeForm != null)
	//{
	//	m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_SHOW);
	//}

	if (m_bBlurBg)
	{
		//g_pUIMgr->showForm(eUIBlurBg);        // 显示模糊背景界面
	}
	//adjustPosWithAlign();
}

// 每一次隐藏都会调用一次
void UForm::onHide()
{
	//if (m_luaCSBridgeForm != null)
	//{
	//	m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_HIDE);
	//}

	//if (m_bBlurBg)
	//{
	//	g_pUIMgr->exitForm(UIFormID.eUIBlurBg);
	//}
}

// 每一次关闭都会调用一次
void UForm::onExit()
{
	//if (m_luaCSBridgeForm != null)
	//{
	//	m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_EXIT);
	//}

	//if (m_bBlurBg)
	//{
	//	g_pUIMgr->exitForm(UIFormID.eUIBlurBg);
	//}
}

bool UForm::isVisible()
{
	//return m_GUIWin->m_uiRoot->activeSelf;        // 仅仅是自己是否可见
	return true;
}

/*
* stage的大小发生变化后，这个函数会被调用。子类可重载这个函数
*/
void UForm::onStageReSize()
{
	adjustPosWithAlign();
}

void UForm::adjustPosWithAlign()
{
	PointF* pos = computeAdjustPosWithAlign();
	this->setPosX(pos->getX());
	this->setPosY(pos->getY());
}

PointF* UForm::computeAdjustPosWithAlign()
{
	PointF* ret = new PointF(0, 0);
	//int widthStage = 0;
	//int heightStage = 0;
	//if (m_alignVertial == (int)CENTER)
	//{
	//	ret->setX((heightStage - this->m_height) / 2);
	//}
	//else if (m_alignVertial == (int)TOP)
	//{
	//	ret->setY(this->m_marginTop);
	//}
	//else
	//{
	//	ret->setY(heightStage - this->m_height - this->m_marginBottom);
	//}

	//if (m_alignHorizontal == (int)CENTER)
	//{
	//	ret->setX((widthStage - this->m_width) / 2);
	//}
	//else if (m_alignHorizontal == (int)LEFT)
	//{
	//	ret->setX(m_marginLeft);
	//}
	//else
	//{
	//	ret->setX(widthStage - this->m_width - m_marginRight);
	//}
	return ret;
}

// 按钮点击关闭
void UForm::onExitBtnClick()
{
	exit();
}

//void UForm::registerBtnClickEventByList(string[] btnList)
//{
//	foreach(var path in btnList)
//	{
//		addClick(m_GUIWin.m_uiRoot, path);
//	}
//}
//
//void UForm::registerImageClickEventByList(string[] imageList)
//{
//
//}

//void UForm::registerWidgetEvent()
//{
//	string[] pathArr = m_luaCSBridgeForm.getTable2StrArray("BtnClickTable");
//	foreach(var path in pathArr)
//	{
//		addClick(m_GUIWin.m_uiRoot, path);
//	}
//}

//void UForm::onBtnClk(GameObject go_)
//{
//	if (m_luaCSBridgeForm != null)
//	{
//		if (m_go2Path.ContainsKey(go_))
//		{
//			m_luaCSBridgeForm.handleUIEvent("onBtnClk", m_formName, m_go2Path[go_].m_path);
//		}
//	}
//
//	// 测试全局分发事件
//	// Ctx.m_instance.m_globalEventMgr.eventDispatchGroup.dispatchEvent((int)eGlobalEventType.eGlobalTest, null);
//}

//void UForm::addClick(GameObject go, string path)
//{
//	UtilApi.addEventHandle(go, path, onBtnClk);
//	GameObject btnGo = UtilApi.TransFindChildByPObjAndPath(go, path);
//	if (btnGo = null)
//	{
//		if (!m_go2Path.ContainsKey(btnGo))
//		{
//			m_go2Path[btnGo] = new GOExtraInfo();
//			m_go2Path[btnGo].m_path = path;
//		}
//	}
//}

//void UForm::removeClick(GameObject go, string path)
//{
//	UtilApi.removeEventHandle(go, path);
//	GameObject btnGo = UtilApi.TransFindChildByPObjAndPath(go, path);
//	if (btnGo != null)
//	{
//		if (m_go2Path.ContainsKey(btnGo))
//		{
//			m_go2Path.Remove(btnGo);
//		}
//	}
//}

bool UForm::getIsReady()
{
	return m_bReady;
}