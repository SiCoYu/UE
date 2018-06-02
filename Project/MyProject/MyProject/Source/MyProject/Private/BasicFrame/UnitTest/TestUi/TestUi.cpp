#include "MyProject.h"
#include "Prequisites.h"
#include "UiFormId.h"
#include "UiTestUMG.h"
#include "TestUi.h"

MY_BEGIN_NAMESPACE(MyNS)

void TestUi::run()
{
	GUiMgr->loadAndShow<UUiTestUMG>(UiFormId::eUiTestUMG);
}

MY_END_NAMESPACE