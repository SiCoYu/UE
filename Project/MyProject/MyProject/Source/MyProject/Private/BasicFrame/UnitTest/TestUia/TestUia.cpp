#include "MyProject.h"
#include "Common.h"
#include "UiFormId.h"
#include "UiTestUMG.h"
#include "TestUi.h"

void TestUi::run()
{
	GUiMgr->loadAndShow<UUiTestUMG>(NSFormId::eUiTestUMG);
}