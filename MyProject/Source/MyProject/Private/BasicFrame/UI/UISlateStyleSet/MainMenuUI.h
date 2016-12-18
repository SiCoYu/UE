#pragma once

#include "SlateBasics.h"

/**
 * @url https://wiki.unrealengine.com/Slate_Style_Sets_Part_2
 */

class SMainMenuUI : public SCompoundWidget
{

public:
	SLATE_BEGIN_ARGS(SMainMenuUI)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AMainMenuHUD>, MainMenuHUD)
		SLATE_END_ARGS()

		void Construct(const FArguments& InArgs);

	/**
	* Click handler for the Play Game! button ¨C Calls MenuHUD¡¯s PlayGameClicked() event.
	*/
	FReply PlayGameClicked();
	/**
	* Click handler for the Quit Game button ¨C Calls MenuHUD¡¯s QuitGameClicked() event.
	*/
	FReply QuitGameClicked();

	TWeakObjectPtr<class AMainMenuHUD> MainMenuHUD;

	const struct FGlobalStyle* MenuStyle;

};