#ifndef __LuaStringConversion_H
#define __LuaStringConversion_H

#include <string>

std::wstring UTF8ToWStr(const std::string& utf8str);
std::string WStrToUTF8(const std::wstring& wstr);

#endif // LUASTRINGCONVERSION