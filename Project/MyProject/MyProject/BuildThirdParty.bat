::echo on
rem @echo off
@echo off
set BASE_DIR=%~dp0
%BASE_DIR:~0,2%

set GENERATOR="Visual Studio 14 2015 Win64"
set DEVENV="C:\ProgramFiles (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv.exe"

if exist %BASE_DIR%ThirdParty\Src\build rd /s /q %BASE_DIR%ThirdParty\Src\build
mkdir %BASE_DIR%ThirdParty\Src\build

cd %BASE_DIR%ThirdParty\Src\build

if exist %BASE_DIR%BatPath.bat call %BASE_DIR%BatPath.bat
if defined CMAKEPATH (
	%CMAKEPATH% -G%GENERATOR% -DCMAKE_BUILD_TYPE:STRING=RelWithDebInfo -DCMAKE_INSTALL_PREFIX:PATH=%BASE_DIR%ThirdParty\Src\build %BASE_DIR%ThirdParty\Src
) else (
	echo set CMAKEPATH="F:\ProgramFiles\cmake-3.7.0-win64-x64\bin\cmake.exe" > %BASE_DIR%BatPath.bat
	echo set DEVENV="D:\programfiles(x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv.exe" >> %BASE_DIR%BatPath.bat
	echo Error CMAKEPATH not define
)

cd %BASE_DIR%

::if exist %BASE_DIR%ThirdParty\Src\build\ThirdParty.sln (
::	start "" %BASE_DIR%ThirdParty\Src\build\ThirdParty.sln
::) else (
::	echo Error %BASE_DIR%ThirdParty\Src\build\ThirdParty.sln not exist
::)

::%DEVENV% %BASE_DIR%ThirdParty\Src\build\ThirdParty.sln /build "RelWithDebInfo" /project "INSTALL"
%DEVENV% %BASE_DIR%ThirdParty\Src\build\ThirdParty.sln /build "Debug" /project "INSTALL"

pause