#pragma once

#include "MyProject.h"
#include "UIFormId.h"
#include "GuiWin.h"
#include "Blueprint/UserWidget.h"	// UUserWidget
#include "Window.generated.h"

using namespace NSFormId;

class UILayer;

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
	UIFormId mId;
public:
	GuiWin* mGuiWin;      // 控件数据
protected:
	bool mIsDraggable;

	int mHitYMax;	// 可点击范围 Y 的最大值
	int mAlignVertial;
	int mAlignHorizontal;

	int mMarginLeft;
	int mMarginTop;
	int mMarginRight;
	int mMarginBottom;

	int mWidth;
	int mHeight;
	UILayer* mUiLayer;
	bool mIsResReady;            // 资源是否已经加载并初始化

public:
	UWindow(const FObjectInitializer& ObjectInitializer);

	virtual int getPosX();
	virtual void setPosX(int posX);
	virtual int getPosY();
	virtual void setPosY(int posY);
	UILayer* getUiLayer();
	void setUiLayer(UILayer* layer);
	bool IsVisible();
	bool getIsResReady();
	void setIsResReady(bool value);
	GuiWin* getGuiWin();

	virtual bool getIsReady();
};