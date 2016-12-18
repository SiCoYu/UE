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

	bool mIsExitMode;               // �ر��˳�ģʽ
	bool mIsHideOnCreate;         // �������Ƿ�����
	UIFormID mId;
	bool mIsLoadWidgetRes;                // �Ƿ�Ӧ�ü��ش�����Դ
	bool mIsReady;            // �Ƿ�׼������

	bool mIsBlurBg;       // �Ƿ�ģ������
	bool mIsHandleExitBtn;       // �Ƿ�����رհ�ť

	// LuaCSBridgeForm mLuaCSBridgeForm;
	std::string mFormName;            // ����� Lua �д��ı�ʶ�����ᴫ�� Lua ʹ�ã��ͻ����Լ�����
	//std::map<GameObject, GOExtraInfo> mGo2Path;

public:
	UForm(const FObjectInitializer& ObjectInitializer);

	void loadUWidget(const TCHAR* name);
	UIFormID getID();
	void setID(UIFormID value);
	bool getHideOnCreate();
	void setHideOnCreate(bool value);
	bool getExitMode();
	void setExitMode(bool value);
	bool getIsLoadWidgetRes();
	void setIsLoadWidgetRes(bool value);
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