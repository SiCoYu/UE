#include "MyProjectEditor.h"
#include "../Public/GameAttributesEditor.h"
#include "GAAttributePin.h"
#include "GAGlobalTypes.h"
#include "GAAttributePanelGraphPinFactory.h"


#include "GameAttributesEditorPrivatePCH.h"


class FGameAttributesEditor : public IGameAttributesEditor
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{
		//create your factory and shared pointer to it.
		TSharedPtr<FGAAttributePanelGraphPinFactory> GAAttributePanelGraphPinFactory = MakeShareable(new FGAAttributePanelGraphPinFactory());
		//and now register it.
		FEdGraphUtilities::RegisterVisualPinFactory(GAAttributePanelGraphPinFactory);
	}
	virtual void ShutdownModule() override
	{

	}
};

IMPLEMENT_MODULE(FGameAttributesEditor, GameAttributesEditor)