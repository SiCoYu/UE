#include "MyProject.h"
#include "UIFactory.h"

#include "FormBase.h"
#include "UIPack.h"

UFormBase* UIFactory::createForm(FormID formID)
{
	switch (formID)
	{
		case eUIPack:
		{
			//return new UUIPack();
			return Cast<UFormBase>(StaticConstructObject(UUIPack::StaticClass()));
		}
		default:
		{
			break;
		}
	}

	return nullptr;
}
