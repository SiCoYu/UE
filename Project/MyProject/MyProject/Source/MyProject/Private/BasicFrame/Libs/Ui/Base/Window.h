#pragma once

#include "MyProject.h"
#include "UiFormId.h"
#include "WinRender.h"
#include "Blueprint/UserWidget.h"	// UUserWidget
#include "MyUEObject.h"
#include "PlatformDefine.h"
#include "Window.generated.h"

// ��������Ͷ���һ��Ҫһ�������� namespace
namespace MyNS
{
	class UiLayer;
}

// ����ʹ�ú궨�壬����뱨��
//MY_USING_NAMESPACE(MyNS)

// ���ʹ�ÿ���ʹ namespace::class ,���� using namespace name
using namespace MyNS;

/**
 * @brief https://wiki.unrealengine.com/UMG,_How_to_extend_a_UUserWidget::_for_UMG_in_C%2B%2B.
 * Set the Widget Parent
 * Open up the new Widget you just created and go to the Graph of the Widget Blueprint. Press on the UMG2.PNG button on the top of the window.
 */

//UCLASS(abstract, config = Game)
UCLASS(config = Game)
class UWindow : public UMyUEObject
//class UWindow : public UUserWidget
{
	GENERATED_BODY()

protected:
	UiFormId mId;
public:
	WinRender* mWinRender;      // �ؼ�����
protected:
	bool mIsDraggable;

	int mHitYMax;	// �ɵ����Χ Y �����ֵ
	int mAlignVertial;
	int mAlignHorizontal;

	int mMarginLeft;
	int mMarginTop;
	int mMarginRight;
	int mMarginBottom;

	int mWidth;
	int mHeight;
	UiLayer* mUiLayer;

public:
	UWindow(const FObjectInitializer& ObjectInitializer);

	virtual int getPosX();
	virtual void setPosX(int posX);
	virtual int getPosY();
	virtual void setPosY(int posY);
	UiLayer* getUiLayer();
	void setUiLayer(UiLayer* layer);
	bool IsVisible();
	WinRender* getWinRender();
};