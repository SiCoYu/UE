#include "MyProject.h"
#include "Window.h"
#include "UILayer.h"

UWindow::UWindow(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	mIsDraggable = true;
	mHitYMax = 30;
	mAlignVertial = 0;
	mAlignHorizontal = 0;
	mIsResReady = false;

	mGuiWin = new GuiWin();
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

UILayer* UWindow::getUiLayer()
{
	return mUiLayer;
}

void UWindow::setUiLayer(UILayer* layer)
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

GuiWin* UWindow::getGuiWin()
{
	return mGuiWin;
}

bool UWindow::getIsReady()
{
	return true;
}