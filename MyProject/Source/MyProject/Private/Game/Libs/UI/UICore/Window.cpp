#include "MyProject.h"
#include "Window.h"
#include "UILayer.h"

UWindow::UWindow()
{
	m_draggable = true;
	m_hitYMax = 30;
	m_alignVertial = 0;
	m_alignHorizontal = 0;
	m_isResReady = false;
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

}

void UWindow::setPosY(int posY)
{

}

UILayer* UWindow::getUiLayer()
{
	return m_uiLayer;
}

void UWindow::setUiLayer(UILayer* layer)
{
	m_uiLayer = layer;
}

bool UWindow::IsVisible()
{
	return false;
}

bool UWindow::getIsResReady()
{
	return m_isResReady;
}

void UWindow::setIsResReady(bool value)
{
	m_isResReady = value;
}

GUIWin* UWindow::getGUIWin()
{
	return m_GUIWin;
}

bool UWindow::getIsReady()
{
	return true;
}