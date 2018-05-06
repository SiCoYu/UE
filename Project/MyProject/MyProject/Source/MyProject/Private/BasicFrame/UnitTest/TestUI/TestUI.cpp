#include "MyProject.h"
#include "Common.h"
#include "UiFormId.h"
#include "UiTestUMG.h"
#include "TestUI.h"

void TestUI::run()
{
	GUiMgr->loadAndShow<UUiTestUMG>(NSFormId::eUITestUMG);
}