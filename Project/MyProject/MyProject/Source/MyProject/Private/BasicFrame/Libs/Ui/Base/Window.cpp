#include "MyProject.h"
#include "Window.h"
#include "UiLayer.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

UWindow::UWindow(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	this->mIsDraggable = true;
	this->mHitYMax = 30;
	this->mAlignVertial = 0;
	this->mAlignHorizontal = 0;
	this->mWinRender = nullptr;		// UObject ������ DefaultObject������� new һ������ռ�ÿռ䣬����ں����ʼ��
}

void UWindow::onInit()
{
	this->mWinRender = MY_NEW WinRender();
}

void UWindow::onExit()
{
	if (nullptr != this->mWinRender)
	{
		MY_DELETE this->mWinRender;
		this->mWinRender = nullptr;
	}
}

int UWindow::getPosX()
{
	return 0;
}

void UWindow::setPosX(int posX)
{

}

int UWindow::getPosY()
{
	return 0;
}

void UWindow::setPosY(int posY)
{

}

UiLayer* UWindow::getUiLayer()
{
	return this->mUiLayer;
}

void UWindow::setUiLayer(UiLayer* layer)
{
	this->mUiLayer = layer;
}

bool UWindow::IsVisible()
{
	return false;
}

WinRender* UWindow::getWinRender()
{
	return this->mWinRender;
}