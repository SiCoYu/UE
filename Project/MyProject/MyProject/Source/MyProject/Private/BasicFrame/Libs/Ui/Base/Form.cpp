#include "MyProject.h"
#include "UMGForm.h"
#include "Prequisites.h"
#include "UtilEngineWrap.h"
#include "PointF.h"
#include "MyGameInstanceBase.h"	// UMyGameInstanceBase
#include "UMGWidget.h"		// UUMGWidget
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
		//mWinRender->mUiRoot = NewObject<UUserWidget>(UtilEngineWrap::getGameInstance(), widgetClass);
		this->mWinRender->mUiRoot = NewObject<UUMGWidget>(UtilEngineWrap::GetGameInstance(), widgetClass);
	}
}

UForm::UForm(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	this->mIsExitMode = true;
	this->mIsHideOnCreate = false;
	this->mIsLoadWidgetRes = false;
	this->mIsReady = false;
	this->mIsBlurBg = false;
	this->mIsHandleExitBtn = false;
	this->mAlignVertial = (int)CENTER;
	this->mAlignHorizontal = (int)CENTER;
	this->mIsVisible = false;
}

UiFormId UForm::getId()
{
	return this->mId;
}

void UForm::setId(UiFormId value)
{
	this->mId = value;
}

bool UForm::getHideOnCreate()
{
	return this->mIsHideOnCreate;
}

void UForm::setHideOnCreate(bool value)
{
	this->mIsHideOnCreate = value;
}

bool UForm::getExitMode()
{
	return this->mIsExitMode;
}

void UForm::setExitMode(bool value)
{
	this->mIsExitMode = value;
}

bool UForm::getIsLoadWidgetRes()
{
	return this->mIsLoadWidgetRes;
}

void UForm::setIsLoadWidgetRes(bool value)
{
	this->mIsLoadWidgetRes = true;
}

bool UForm::getIsReady()
{
	return this->mIsReady;
}

std::string UForm::getFormName()
{
	return this->mFormName;
}

void UForm::setFormName(std::string value)
{
	this->mFormName = value;
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
	this->onInit();
}

void UForm::show()
{
	GUiMgr->showForm(mId);
}

//private void UForm::hide()
//{
//    GUiMgr->hideForm(mId);
//}

void UForm::exit()
{
	GUiMgr->exitForm(mId);
}

// 界面代码创建后就调用
void UForm::onInit()
{
	//if (m_luaCSBridgeForm != null)
	//{
	//	m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_INIT);
	//}
	if (!this->mIsLoadWidgetRes)
	{
		// 默认会继续加载资源
		GUiMgr->loadWidgetRes(this->getId());
	}
}

// 第一次显示之前会调用一次
void UForm::onReady()
{
	//if (m_luaCSBridgeForm != null)
	//{
	//	m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_READY);
	//}

	this->mIsReady = true;

	if (this->mIsHandleExitBtn)
	{
		//UtilSysLibWrap.addEventHandle(mWinRender.mUiRoot, "BtnClose", onExitBtnClick); // 关闭事件
	}
}

// 每一次显示都会调用一次
void UForm::onShow()
{
	this->mIsVisible = true;

	//if (m_luaCSBridgeForm != null)
	//{
	//	m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_SHOW);
	//}

	if (this->mIsBlurBg)
	{
		//GUiMgr->showForm(eUIBlurBg);        // 显示模糊背景界面
	}
	//adjustPosWithAlign();
}

// 每一次隐藏都会调用一次
void UForm::onHide()
{
	this->mIsVisible = false;

	//if (m_luaCSBridgeForm != null)
	//{
	//	m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_HIDE);
	//}

	//if (mIsBlurBg)
	//{
	//	GUiMgr->exitForm(UiFormId.eUIBlurBg);
	//}
}

// 每一次关闭都会调用一次
void UForm::onExit()
{
	this->mIsVisible = false;
	this->mIsReady = false;

	//if (m_luaCSBridgeForm != null)
	//{
	//	m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_EXIT);
	//}

	//if (mIsBlurBg)
	//{
	//	GUiMgr->exitForm(UiFormId.eUIBlurBg);
	//}
}

bool UForm::isVisible()
{
	//return mWinRender->mUiRoot->activeSelf;        // 仅仅是自己是否可见
	return this->mIsVisible;
}

/*
* stage的大小发生变化后，这个函数会被调用。子类可重载这个函数
*/
void UForm::onStageReSize()
{
	this->adjustPosWithAlign();
}

void UForm::adjustPosWithAlign()
{
	PointF* pos = this->computeAdjustPosWithAlign();
	this->setPosX(pos->getX());
	this->setPosY(pos->getY());
}

PointF* UForm::computeAdjustPosWithAlign()
{
	PointF* ret = MY_NEW PointF(0, 0);
	//int widthStage = 0;
	//int heightStage = 0;
	//if (mAlignVertial == (int)CENTER)
	//{
	//	ret->setX((heightStage - this->m_height) / 2);
	//}
	//else if (mAlignVertial == (int)TOP)
	//{
	//	ret->setY(this->m_marginTop);
	//}
	//else
	//{
	//	ret->setY(heightStage - this->m_height - this->m_marginBottom);
	//}

	//if (mAlignHorizontal == (int)CENTER)
	//{
	//	ret->setX((widthStage - this->m_width) / 2);
	//}
	//else if (mAlignHorizontal == (int)LEFT)
	//{
	//	ret->setX(m_marginLeft);
	//}
	//else
	//{
	//	ret->setX(widthStage - this->m_width - mMarginRight);
	//}
	return ret;
}

// 按钮点击关闭
void UForm::onExitBtnClick()
{
	this->exit();
}

//void UForm::registerBtnClickEventByList(string[] btnList)
//{
//	foreach(var path in btnList)
//	{
//		addClick(mWinRender.mUiRoot, path);
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
//		addClick(mWinRender.mUiRoot, path);
//	}
//}

//void UForm::onBtnClk(GameObject go_)
//{
//	if (m_luaCSBridgeForm != null)
//	{
//		if (m_go2Path.ContainsKey(go_))
//		{
//			m_luaCSBridgeForm.handleUIEvent("onBtnClk", mFormName, m_go2Path[go_].mPath);
//		}
//	}
//
//	// 测试全局分发事件
//	// Ctx.m_instance.m_globalEventMgr.eventDispatchGroup.dispatchEvent((int)eGlobalEventType.eGlobalTest, null);
//}

//void UForm::addClick(GameObject go, string path)
//{
//	UtilSysLibWrap.addEventHandle(go, path, onBtnClk);
//	GameObject btnGo = UtilSysLibWrap.TransFindChildByPObjAndPath(go, path);
//	if (btnGo = null)
//	{
//		if (!m_go2Path.ContainsKey(btnGo))
//		{
//			m_go2Path[btnGo] = new ActorExtraInfo();
//			m_go2Path[btnGo].mPath = path;
//		}
//	}
//}

//void UForm::removeClick(GameObject go, string path)
//{
//	UtilSysLibWrap.removeEventHandle(go, path);
//	GameObject btnGo = UtilSysLibWrap.TransFindChildByPObjAndPath(go, path);
//	if (btnGo != null)
//	{
//		if (m_go2Path.ContainsKey(btnGo))
//		{
//			m_go2Path.Remove(btnGo);
//		}
//	}
//}

AuxMUiClassLoader* UForm::getAuxMUIClassLoader()
{
	return this->mAuxMUIClassLoader;
}

void UForm::setAuxMUIClassLoader(AuxMUiClassLoader* value)
{
	this->mAuxMUIClassLoader = value;
}