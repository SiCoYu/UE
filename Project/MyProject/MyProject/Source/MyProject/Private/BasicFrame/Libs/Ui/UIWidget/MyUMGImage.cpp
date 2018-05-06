#include "MyProject.h"
#include "MyUMGImage.h"

//LOCTEXT
#define LOCTEXT_NAMESPACE "UMG"

/////////////////////////////////////////////////////
// UJoySoftEdgeImage

UMyUMGImage::UMyUMGImage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ColorAndOpacity(FLinearColor(0, 0, 1, 0.0333))
	, Thickness(24)
{
	//Default Values Set Here, see above
}

//Rebuild using custom Slate Widget 
//		-Rama
TSharedRef<SWidget> UMyUMGImage::RebuildWidget()
{
	MyImage = SNew(SMySlateImage);
	return MyImage.ToSharedRef();
}

//Set Thickness
void UMyUMGImage::SetThickness(float InThickness)
{
	Thickness = InThickness;
	if (MyImage.IsValid())
	{
		MyImage->SetThickness(InThickness);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//This is where the SSoftEdgeImage slate widget gets updated 
//		when the UPROPERTY() is changed in the Editor
//		-Rama
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void UMyUMGImage::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	//Thickness Delegate Version
	//TAttribute<float> ThickBind = OPTIONAL_BINDING(float, Thickness);
	//MyImage->SetThickness(ThickBind.Get());   

	//Thickness non-delegate version
	MyImage->SetThickness(Thickness);

	// ue4 4.17 warning C4996: OPTIONAL_BINDING macro is deprecated.  Please use PROPERTY_BINDING in place and you'll need to define a PROPERTY_BINDING_IMPLEMENTATION in your header instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//Color and Opacity
	//TAttribute<FSlateColor> ColorAndOpacityBinding = OPTIONAL_BINDING(FSlateColor, ColorAndOpacity);
	TAttribute<FSlateColor> ColorAndOpacityBinding = PROPERTY_BINDING(FSlateColor, ColorAndOpacity);
	MyImage->SetColorAndOpacity(ColorAndOpacityBinding);

	//Image
	TAttribute<const FSlateBrush*> ImageBinding = OPTIONAL_BINDING_CONVERT(FSlateBrush, Brush, const FSlateBrush*, ConvertImage);
	MyImage->SetImage(ImageBinding);

	//Mouse
	MyImage->SetOnMouseButtonDown(BIND_UOBJECT_DELEGATE(FPointerEventHandler, HandleMouseButtonDown));
}


//~~~ Rest is copied from UMG Image.h ~~~

void UMyUMGImage::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyImage.Reset();
}

void UMyUMGImage::SetColorAndOpacity(FLinearColor InColorAndOpacity)
{
	ColorAndOpacity = InColorAndOpacity;
	if (MyImage.IsValid())
	{
		MyImage->SetColorAndOpacity(ColorAndOpacity);
	}
}

void UMyUMGImage::SetOpacity(float InOpacity)
{
	ColorAndOpacity.A = InOpacity;
	if (MyImage.IsValid())
	{
		MyImage->SetColorAndOpacity(ColorAndOpacity);
	}
}

const FSlateBrush* UMyUMGImage::ConvertImage(TAttribute<FSlateBrush> InImageAsset) const
{
	UMyUMGImage* MutableThis = const_cast<UMyUMGImage*>(this);
	MutableThis->Brush = InImageAsset.Get();

	return &Brush;
}

void UMyUMGImage::SetBrushFromAsset(USlateBrushAsset* Asset)
{
	Brush = Asset ? Asset->Brush : FSlateBrush();

	if (MyImage.IsValid())
	{
		MyImage->SetImage(&Brush);
	}
}

void UMyUMGImage::SetBrushFromTexture(UTexture2D* Texture)
{
	Brush.SetResourceObject(Texture);

	if (MyImage.IsValid())
	{
		MyImage->SetImage(&Brush);
	}
}

void UMyUMGImage::SetBrushFromMaterial(UMaterialInterface* Material)
{
	Brush.SetResourceObject(Material);

	//TODO UMG Check if the material can be used with the UI

	if (MyImage.IsValid())
	{
		MyImage->SetImage(&Brush);
	}
}

UMaterialInstanceDynamic* UMyUMGImage::GetDynamicMaterial()
{
	UMaterialInterface* Material = NULL;

	UObject* Resource = Brush.GetResourceObject();
	Material = Cast<UMaterialInterface>(Resource);

	if (Material)
	{
		UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);

		if (!DynamicMaterial)
		{
			DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
			Brush.SetResourceObject(DynamicMaterial);

			if (MyImage.IsValid())
			{
				MyImage->SetImage(&Brush);
			}
		}

		return DynamicMaterial;
	}

	//TODO UMG can we do something for textures?  General purpose dynamic material for them?

	return NULL;
}

FReply UMyUMGImage::HandleMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& MouseEvent)
{
	if (OnMouseButtonDownEvent.IsBound())
	{
		return OnMouseButtonDownEvent.Execute(Geometry, MouseEvent).NativeReply;
	}

	return FReply::Unhandled();
}

#if WITH_EDITOR

//const FSlateBrush* UMyUMGImage::GetEditorIcon()
//{
//	return FUMGStyle::Get().GetBrush("Widget.Image");
//}

const FText UMyUMGImage::GetPaletteCategory()
{
	return LOCTEXT("Common", "Common");
}

#endif


/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE