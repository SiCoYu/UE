#include "MyProject.h"
#include "WinRender.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(WinRender, GObject)

WinRender::WinRender()
{
	this->mUiRoot_S = NULL;
	this->mUiRoot = NULL;
}

void WinRender::init()
{

}

void WinRender::clear()
{
	this->mUiRoot_S = NULL;
	this->mUiRoot = NULL;
}

void WinRender::dispose()
{
	this->clear();
}

MY_END_NAMESPACE