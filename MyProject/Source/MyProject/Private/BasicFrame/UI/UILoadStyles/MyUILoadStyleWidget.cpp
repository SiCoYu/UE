#include "MyProject.h"
#include "SlateGameResources.h"
#include "MyUILoadStyleWidget.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/*SMyUIWidget*//*SMyUIWidget*//*SMyUIWidget*//*SMyUIWidget*//*SMyUIWidget*//*SMyUIWidget*/
																		   ////////////////////////////////////////////////////////////////////////////////////////////////////

void SMyUILoadStyleWidget::Construct(const FArguments& InArgs)
{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Get handle on game resources from GameModule
	MyUIResources = FModuleManager::GetModuleChecked<FMyProject>(FName("MyProject")).GetSlateGameResources();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Get handle on spell_heal Slate Brush
	/////name: member_icon
	const FSlateBrush *m_icon = MyUIResources->GetBrush(FName("/spells/spell_heal"));

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Set owner HUD to whatever HUD called system to create this widget
	/////Consider type if using multiple HUDs/types, see declaration in header
	OwnerHUD = InArgs._OwnerHUD;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Create the child widgets

	//No need to add a new slot, ChildSlot is one, 
	ChildSlot.VAlign(VAlign_Bottom).HAlign(HAlign_Center)
		[//start adding contents
			SNew(SOverlay)
			/* + operator adds a new slot */
		+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		[/* [ operator begins adding things to our new slot's contents */
			SNew(SHorizontalBox).Visibility(EVisibility::Visible)
			//Add slots to HorizontalBox, these will hold images
		+ SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Bottom)
		[   //
			SNew(SImage).Image(m_icon)
		]
	+ SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Bottom)
		[
			SNew(SImage).Image(m_icon)
		]
	+ SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Bottom)
		[
			SNew(SImage).Image(m_icon)
		]
	+ SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Bottom)
		[
			SNew(SImage).Image(m_icon)
		]
		]//End slotting of SOverlay
		];//End slotting ChildSlot
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*FMyUIResources*//*FMyUIResources*//*FMyUIResources*//*FMyUIResources*//*FMyUIResources*/
																		////////////////////////////////////////////////////////////////////////////////////////////////////

void FMyUIResources::Initialize()
{
	if (!MyUIResources.IsValid())
	{
		MyUIResources = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*MyUIResources);
	}
}

TSharedPtr<FSlateGameResources> FMyUIResources::GetSlateGameResources()
{
	return MyUIResources;
}

TSharedRef<class FSlateGameResources> FMyUIResources::Create()
{
	return FSlateGameResources::New(FName("MyUIResources"), m_Path, m_Path);
}

/*Unregister resources/styles with Slate, cleanup, free memory*/
void FMyUIResources::Shutdown()
{
	//Unregister *MyUIResources with Slate
	FSlateStyleRegistry::UnRegisterSlateStyle(*MyUIResources);

	//Debugging
	ensure(MyUIResources.IsUnique());

	//Removes reference to resources, decrements refcount, destroys resources if refcount=0
	//Do this to all SharedPtrs on Shutdown() or SomethingSimilar() to avoid memory leak
	MyUIResources.Reset();
}