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

	bool m_exitMode;               // 关闭退出模式
	bool m_bHideOnCreate;         // 创建后是否隐藏
	UIFormID m_id;
	bool m_bLoadWidgetRes;                // 是否应该加载窗口资源
	bool m_bReady;            // 是否准备就绪

	bool m_bBlurBg;       // 是否模糊背景
	bool m_bHandleExitBtn;       // 是否关联关闭按钮

	// LuaCSBridgeForm m_luaCSBridgeForm;
	std::string m_formName;            // 这个是 Lua 中传的标识符，会传给 Lua 使用，客户端自己不用
	//std::map<GameObject, GOExtraInfo> m_go2Path;

protected:
	void loadUWidget(const TCHAR* name);

public:
	virtual bool getIsReady() override;
};