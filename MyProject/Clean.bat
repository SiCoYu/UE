set base_dir=%~dp0
pushd %base_dir%

if exist ThirdParty\Inc\Sockets rd /s /q ThirdParty\Inc\Sockets
if exist ThirdParty\Inc\TestStaticLib rd /s /q ThirdParty\Inc\TestStaticLib
if exist ThirdParty\Inc\gtest rd /s /q ThirdParty\Inc\gtest

if exist ThirdParty\Lib\Sockets rd /s /q ThirdParty\Lib\Sockets
if exist ThirdParty\Lib\TestStaticLib rd /s /q ThirdParty\Lib\TestStaticLib
if exist ThirdParty\Lib\gtest rd /s /q ThirdParty\Lib\gtest

if exist ThirdParty\build rd /s /q ThirdParty\build
if exist ThirdParty\Src\build rd /s /q ThirdParty\Src\build

popd