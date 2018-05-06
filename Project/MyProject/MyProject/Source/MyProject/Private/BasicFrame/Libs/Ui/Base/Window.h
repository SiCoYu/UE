#pragma once

#include "MyProject.h"
#include "UiFormId.h"
#include "WinRender.h"
#include "Blueprint/UserWidget.h"	// UUserWidget
#include "Window.generated.h"

using namespace NSFormId;

class UiLayer;

/**
 * @brief https://wiki.unrealengine.com/UMG,_How_to_extend_a_UUserWidget::_for_UMG_in_C%2B%2B.
 * Set the Widget Parent
 * Open up the new Widget you just created and go to the Graph of the Widget Blueprint. Press on the UMG2.PNG button on the top of the window.
 */

//UCLASS(abstract, config = Game)
UCLASS(config = Game)
class UWindow : public UObject
//class UWindow : public UUserWidget
{
	GENERATED_BODY()

protected:
	UiFormId mId;
public:
	WinRender* mGuiWin;      // �ؼ�����
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
	bool mIsResReady;            // ��Դ�Ƿ��Ѿ����ز���ʼ��

public:
	UWindow(const FObjectInitializer& ObjectInitializer);

	virtual int getPosX();
	virtual void setPosX(int posX);
	virtual int getPosY();
	virtual void setPosY(int posY);
	UiLayer* getUiLayer();
	void setUiLayer(UiLayer* layer);
	bool IsVisible();
	bool getIsResReady();
	void setIsResReady(bool value);
	WinRender* getGuiWin();

	virtual bool getIsReady();
};