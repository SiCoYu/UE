#pragma once

//Slate Core
#include "SlateCore.h"

/**
* @author JoySoftEdgeImage by Rama
* @brief UMG, Custom Widget Components And Render Code, Usable In UMG Designer
* @url https://wiki.unrealengine.com/UMG,_Custom_Widget_Components_And_Render_Code,_Usable_In_UMG_Designer
*/

class SMySlateImage : public SImage
{
public:
	SLATE_BEGIN_ARGS(SMySlateImage)
		: _Image(FCoreStyle::Get().GetDefaultBrush())
		, _ColorAndOpacity(FLinearColor(0, 0, 1, 0.02333))
		, _Thickness(24)
		, _OnMouseButtonDown()
	{}

	/** Image resource */
	SLATE_ATTRIBUTE(const FSlateBrush*, Image)

	/** Color and opacity */
	SLATE_ATTRIBUTE(FSlateColor, ColorAndOpacity)

	/** Thickness */
	SLATE_ATTRIBUTE(float, Thickness)

	/** Invoked when the mouse is pressed in the widget. */
	SLATE_EVENT(FPointerEventHandler, OnMouseButtonDown)

	SLATE_END_ARGS()

	/**
	* Construct this widget
	*
	* @param	InArgs	The declaration data for this widget
	*/
	void Construct(const FArguments& InArgs);

	//~~~~~~~~
	//Thickness
	//~~~~~~~~
public:
	void SetThickness(float InThickness);

	/** How many times the image is repeated to give a softness to the edge */
	float Thickness;

public:

	// SWidget overrides

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
};