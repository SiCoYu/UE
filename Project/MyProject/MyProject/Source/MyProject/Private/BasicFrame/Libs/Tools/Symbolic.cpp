#include "MyProject.h"
#include "Symbolic.h"

MY_BEGIN_NAMESPACE(MyNS)

char Symbolic::CR = '\r';  // 13
char Symbolic::LF = '\n';  // 10

std::string CR_LF = "\n";       // �س����У� Mac ���漴ʹд�� "\r\n"����ȡ������Ҳֻ�� "\n"��������� Windows ��Ҳֻд�� "\n"�������� "\r\n"
std::string SEPARATOR = "=";    // �ָ���

MY_END_NAMESPACE