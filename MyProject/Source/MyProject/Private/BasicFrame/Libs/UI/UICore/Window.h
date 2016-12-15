#pragma once

#include "MyProject.h"
#include "UIFormID.h"
#include "GUIWin.h"
#include "Blueprint/UserWidget.h"	// UUserWidget
#include "Window.generated.h"

class UILayer;

/**
 * @brief https://wiki.unrealengine.com/UMG,_How_to_extend_a_UUserWidget::_for_UMG_in_C%2B%2B.
 * Set the Widget Parent
 * Open up the new Widget you just created and go to the Graph of the Widget Blueprint. Press on the UMG2.PNG button on the top of the window.
 */

//UCLASS(abstract, config = Game)
UCLASS(config = Game)
//class UWindow : public UObject
class UWindow : public UUserWidget
{
	GENERATED_BODY()

protected:
	UIFormID m_id;
public:
	GUIWin* m_GUIWin;      // 控件数据
protected:
	bool m_draggable;

	int m_hitYMax;	// 可点击范围 Y 的最大值
	int m_alignVertial;
	int m_alignHorizontal;

	int m_marginLeft;
	int m_marginTop;
	int m_marginRight;
	int m_marginBottom;

	int m_width;
	int m_height;
	UILayer* m_uiLayer;
	bool m_isResReady;            // 资源是否已经加载并初始化

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
	GUIWin* getGUIWin();

	virtual bool getIsReady();
};