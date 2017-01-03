#include "MyProject.h"
#include "TestLuaBind.h"

void TestLuaBind::run()
{
	char* str =
		"line = Line('  if ...')\n"
		"print(line:startWith('if', false))\n"
		"print(line:startWith('if', true))\n";

	str =
		"line = Line('  if ...')\n"
		"ok, off = line:startWith('if', true)\n"
		"print(ok, off)\n";
}