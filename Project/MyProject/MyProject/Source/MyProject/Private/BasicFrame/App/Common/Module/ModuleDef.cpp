#include "MyProject.h"
#include "ModuleDef.h"
#include "LayerPath.h"

MY_BEGIN_NAMESPACE(MyNS)

std::string ModulePath::LOGINMN = "RootLayer/Login";
std::string ModulePath::GAMEMN = LayerPath::ND_CV_Game;
std::string ModulePath::AUTOUPDATEMN = "RootLayer/AutoUpdate";

std::string ModuleName::LOGINMN = "Login";
std::string ModuleName::GAMEMN = "Game";
std::string ModuleName::AUTOUPDATEMN = "AutoUpdate";

MY_END_NAMESPACE