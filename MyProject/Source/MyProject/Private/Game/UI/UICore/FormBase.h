#pragma once

#include "UIFormID.h"
#include "FormBase.generated.h"

UCLASS(abstract, config = Game)
class UFormBase : public UObject
{
	GENERATED_BODY()

protected:
	UIFormID m_formId;
public:
	virtual void onReady();
	UIFormID getFormId();
};