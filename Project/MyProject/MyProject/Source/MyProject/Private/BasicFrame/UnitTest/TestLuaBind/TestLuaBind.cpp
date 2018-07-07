#include "MyProject.h"
#include "TestLuaBind.h"
#include "Prequisites.h"

MY_BEGIN_NAMESPACE(MyNS)

void TestLuaBind::run()
{
	const char* str =
		"local testClass = TestClass('test')\n"
		"print(testClass:getLength())\n";

	str =
		"local testClass = TestClass('  if ...')\n"
		"print(testClass:startWith('if', false))\n"
		"print(testClass:startWith('if', true))\n";

	str =
		"local testClass = TestClass('  if ...')\n"
		"ok, off = testClass:startWith('if', true)\n"
		"print(ok, off)\n";

	str =
		"local testClass = TestClass('  else ...')\n"
		"ok, off = testClass:startWith(true, 'if', 'else')\n"
		"print(ok, off)\n";

	// 执行初始化代码
	//GLuaSystem->doString("require(\"MyLua.Module.Entry.MainEntry\")");
	//GLuaSystem->runLuaScript();
}

MY_END_NAMESPACE