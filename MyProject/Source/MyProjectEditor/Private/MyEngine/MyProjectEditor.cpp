#include "MyProjectEditor.h"
#include "GAAttributePin.h"
#include "GAGlobalTypes.h"
#include "GAAttributePanelGraphPinFactory.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, MyProjectEditor, "MyProjectEditor" );

void MyProjectEditor::StartupModule()
{
	this->StartupModule_GAAttribute();
}

void MyProjectEditor::ShutdownModule()
{

}

void MyProjectEditor::StartupModule_GAAttribute()
{
	//create your factory and shared pointer to it.
	TSharedPtr<FGAAttributePanelGraphPinFactory> GAAttributePanelGraphPinFactory = MakeShareable(new FGAAttributePanelGraphPinFactory());
	//and now register it.
	FEdGraphUtilities::RegisterVisualPinFactory(GAAttributePanelGraphPinFactory);
}

void MyProjectEditor::ShutdownModule_GAAttribute()
{

}