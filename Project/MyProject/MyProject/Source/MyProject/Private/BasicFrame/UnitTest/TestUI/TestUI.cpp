#include "MyProject.h"
#include "Common.h"
#include "UIFormId.h"
#include "UITestUMG.h"
#include "TestUI.h"

void TestUI::run()
{
	GUiMgr->loadAndShow<UUITestUMG>(NSFormId::eUITestUMG);
}