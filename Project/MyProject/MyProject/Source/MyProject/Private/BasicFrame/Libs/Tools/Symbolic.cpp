#include "MyProject.h"
#include "Symbolic.h"

MY_BEGIN_NAMESPACE(MyNS)

char Symbolic::CR = '\r';  // 13
char Symbolic::LF = '\n';  // 10

std::string Symbolic::CR_LF = "\n";       // 回车换行， Mac 下面即使写入 "\r\n"，读取出来后，也只有 "\n"，因此这里 Windows 下也只写入 "\n"，而不是 "\r\n"
std::string Symbolic::SEPARATOR = "=";    // 分隔符

MY_END_NAMESPACE