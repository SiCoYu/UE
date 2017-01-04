#include "MyProject.h"
#include "TestLuaBind.h"

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
}