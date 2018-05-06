#include "MyProject.h"
#include "Window.h"
#include "UiLayer.h"

UWindow::UWindow(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	mIsDraggable = true;
	mHitYMax = 30;
	mAlignVertial = 0;
	mAlignHorizontal = 0;
	mIsResReady = false;

	mWinRender = new WinRender();
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
	return mUiLayer;
}

void UWindow::setUiLayer(UiLayer* layer)
{
	mUiLayer = layer;
}

bool UWindow::IsVisible()
{
	return false;
}

bool UWindow::getIsResReady()
{
	return mIsResReady;
}

void UWindow::setIsResReady(bool value)
{
	mIsResReady = value;
}

WinRender* UWindow::getGuiWin()
{
	return mWinRender;
}

bool UWindow::getIsReady()
{
	return true;
}