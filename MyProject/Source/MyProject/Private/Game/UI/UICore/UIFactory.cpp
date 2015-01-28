#include "MyProject.h"
#include "UIFactory.h"

#include "FormBase.h"
#include "UIPack.h"

FormBase* UIFactory::createForm(FormID formID)
{
	switch (formID)
	{
		case eUIPack:
		{
			return new UIPack();
		}
		default:
		{
			break;
		}
	}
}
