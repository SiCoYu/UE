#pragma once

#include "UIFormID.h"
#include "GUIWin.h"
#include "FormBase.generated.h"

class UILayer;

UCLASS(abstract, config = Game)
class UFormBase : public UObject
{
	GENERATED_BODY()

protected:
	UIFormID m_formId;
	GUIWin m_GUIWin;      // �ؼ�����
	bool m_draggable;

	int m_hitYMax;	// �ɵ����Χ Y �����ֵ
	int m_alignVertial;
	int m_alignHorizontal;

	int m_marginLeft;
	int m_marginTop;
	int m_marginRight;
	int m_marginBottom;

	int m_width;
	int m_height;
	UILayer* m_uiLayer;
	bool m_isResReady;            // ��Դ�Ƿ��Ѿ����ز���ʼ��

public:
	UFormBase();

	virtual void onReady();
	UIFormID getFormId();
	UIFormID getFormId();
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
};