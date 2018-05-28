#pragma once

#include "MyProject.h"
#include "Window.h"
#include <string>
#include "UiFormId.h"
#include "PointF.h"
#include "AuxMUiClassLoader.h"

#include "Form.generated.h"

using namespace NSFormId;
using namespace MyNS;

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
	UiFormId mId;
	bool mIsLoadWidgetRes;                // �Ƿ�Ӧ�ü��ش�����Դ
	bool mIsReady;            // �Ƿ�׼������

	bool mIsBlurBg;       // �Ƿ�ģ������
	bool mIsHandleExitBtn;       // �Ƿ�����رհ�ť

	// LuaCSBridgeForm mLuaCSBridgeForm;
	std::string mFormName;            // ����� Lua �д��ı�ʶ�����ᴫ�� Lua ʹ�ã��ͻ����Լ�����
	bool mIsVisible;
	AuxMUiClassLoader* mAuxMUIClassLoader;

public:
	UForm(const FObjectInitializer& ObjectInitializer);

	void loadUWidget(const TCHAR* name);
	UiFormId getId();
	void setId(UiFormId value);
	bool getHideOnCreate();
	void setHideOnCreate(bool value);
	bool getExitMode();
	void setExitMode(bool value);
	bool getIsLoadWidgetRes();
	void setIsLoadWidgetRes(bool value);
	bool getIsReady();
	std::string getFormName();
	void setFormName(std::string value);
	//LuaCSBridgeForm* UUMGForm::getLuaCSBridgeForm();
	//void UUMGForm::getLuaCSBridgeForm(LuaCSBridgeForm* value);
	virtual void init();
	virtual void show();
	//private void UUMGForm::hide();
	virtual void exit();
	// ������봴����͵���
	virtual void onInit();
	// ��һ����ʾ֮ǰ�����һ��
	virtual void onReady();
	// ÿһ����ʾ�������һ��
	virtual void onShow();
	// ÿһ�����ض������һ��
	virtual void onHide();
	// ÿһ�ιرն������һ��
	virtual void onExit();

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
	AuxMUiClassLoader* getAuxMUIClassLoader();
	void setAuxMUIClassLoader(AuxMUiClassLoader* value);
};