#include "MyProject.h"
#include "UMGForm.h"
#include "Prequisites.h"
#include "UtilEngineWrap.h"
#include "PointF.h"
#include "MyGameInstanceBase.h"	// UMyGameInstanceBase
#include "UMGWidget.h"		// UUMGWidget
#include "WindowAnchor.h"
#include "SafePointer.h"

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
	this->mIsReady = false;
	this->mIsBlurBg = false;
	this->mIsHandleExitBtn = false;
	this->mAlignVertial = (int)WindowAnchor::eCENTER;
	this->mAlignHorizontal = (int)WindowAnchor::eCENTER;
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

bool UForm::isReady()
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
	//if (m_luaCSBridgeForm != nullptr)
	//{
	//	m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_INIT);
	//}

	Super::onInit();
}

// 第一次显示之前会调用一次
void UForm::onReady()
{
	//if (m_luaCSBridgeForm != nullptr)
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

	//if (m_luaCSBridgeForm != nullptr)
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

	//if (m_luaCSBridgeForm != nullptr)
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

	//if (m_luaCSBridgeForm != nullptr)
	//{
	//	m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_EXIT);
	//}

	//if (mIsBlurBg)
	//{
	//	GUiMgr->exitForm(UiFormId.eUIBlurBg);
	//}

	this->mAuxMUIClassLoader->unload();
	MY_SAFE_DISPOSE(this->mAuxMUIClassLoader);

	Super::onExit();
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

AuxMUiClassLoader* UForm::getAuxMUIClassLoader()
{
	return this->mAuxMUIClassLoader;
}

void UForm::setAuxMUIClassLoader(AuxMUiClassLoader* value)
{
	this->mAuxMUIClassLoader = value;
}