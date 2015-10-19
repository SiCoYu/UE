#pragma once

#include "MyProject.h"
#include "FormBase.h"
#include "UMGForm.generated.h"

#include <string>

class UUserWidget;

UCLASS(abstract, config = Game)
class UUMGForm : public UFormBase
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

protected:
	void loadUWidget(const TCHAR* name);

public:
	virtual bool getIsReady() override;
};