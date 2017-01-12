#include "MyProjectEditor.h"
//#include "GAAttributePin.h"
//#include "GAAttributePanelGraphPinFactory.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, MyProjectEditor, "MyProjectEditor" );

void FMyProjectEditor::StartupModule()
{
	this->StartupModule_GAAttribute();
}

void FMyProjectEditor::ShutdownModule()
{

}

void FMyProjectEditor::StartupModule_GAAttribute()
{
	////create your factory and shared pointer to it.
	//TSharedPtr<FGAAttributePanelGraphPinFactory> GAAttributePanelGraphPinFactory = MakeShareable(new FGAAttributePanelGraphPinFactory());
	////and now register it.
	//FEdGraphUtilities::RegisterVisualPinFactory(GAAttributePanelGraphPinFactory);
}

void FMyProjectEditor::ShutdownModule_GAAttribute()
{

}