#pragma once

#include "MyProject.h"
#include "Window.h"
#include <string>
#include "UIFormID.h"
#include "PointF.h"

#include "Form.generated.h"

class UUserWidget;
class PointF;

UCLASS(config = Game)
class UForm : public UWindow
{
	GENERATED_BODY()

protected:
	//TSharedPtr<SWidget> m_outUserSlateWidget;
	//TSharedRef<SWidget> m_rootWidget;

	bool m_exitMode;               // �ر��˳�ģʽ
	bool m_bHideOnCreate;         // �������Ƿ�����
	UIFormID m_id;
	bool m_bLoadWidgetRes;                // �Ƿ�Ӧ�ü��ش�����Դ
	bool m_bReady;            // �Ƿ�׼������

	bool m_bBlurBg;       // �Ƿ�ģ������
	bool m_bHandleExitBtn;       // �Ƿ�����رհ�ť

	// LuaCSBridgeForm m_luaCSBridgeForm;
	std::string m_formName;            // ����� Lua �д��ı�ʶ�����ᴫ�� Lua ʹ�ã��ͻ����Լ�����
	//std::map<GameObject, GOExtraInfo> m_go2Path;

public:
	UForm();

	void loadUWidget(const TCHAR* name);
	UIFormID getID();
	void setID(UIFormID value);
	bool getHideOnCreate();
	void setHideOnCreate(bool value);
	bool getExitMode();
	void setExitMode(bool value);
	bool getLoadWidgetRes();
	void setBLoadWidgetRes(bool value);
	bool getBReady();
	std::string getFormName();
	void setFormName(std::string value);
	//LuaCSBridgeForm* UUMGForm::getLuaCSBridgeForm();
	//void UUMGForm::getLuaCSBridgeForm(LuaCSBridgeForm* value);
	void init();
	void show();
	//private void UUMGForm::hide();
	void exit();
	// ������봴����͵���
	void onInit();
	// ��һ����ʾ֮ǰ�����һ��
	void onReady();
	// ÿһ����ʾ�������һ��
	void onShow();
	// ÿһ�����ض������һ��
	void onHide();
	// ÿһ�ιرն������һ��
	void onExit();
	bool isVisible();
	/*
	* stage�Ĵ�С�����仯����������ᱻ���á�����������������
	*/
	void onStageReSize();
	void adjustPosWithAlign();
	PointF* computeAdjustPosWithAlign();
	// ��ť����ر�
	void onExitBtnClick();
	//void registerBtnClickEventByList(std::string[] btnList);
	//void registerImageClickEventByList(string[] imageList);
	//void registerWidgetEvent();
	//void onBtnClk(GameObject go_);
	//void addClick(GameObject go, string path);
	//void removeClick(GameObject go, string path);
	bool getIsReady();
};