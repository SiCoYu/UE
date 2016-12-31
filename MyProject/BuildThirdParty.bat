:: echo on
@echo off
set base_dir=%~dp0
%base_dir:~0,2%

set GENERATOR="Visual Studio 14 2015 Win64"
set DEVENV="D:\programfiles(x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv.exe"

if exist %base_dir%ThirdParty\Src\build rd /s /q %base_dir%ThirdParty\Src\build
mkdir %base_dir%ThirdParty\Src\build

cd %base_dir%ThirdParty\Src\build

if exist %base_dir%BatPath.bat call %base_dir%BatPath.bat
if defined CMAKEPATH (
	%CMAKEPATH% -G%GENERATOR% -DCMAKE_BUILD_TYPE:STRING=RelWithDebInfo -DCMAKE_INSTALL_PREFIX:PATH=%base_dir%ThirdParty\Src\build %base_dir%ThirdParty\Src
) else (
	echo set CMAKEPATH="F:\ProgramFiles\cmake-3.7.0-win64-x64\bin\cmake.exe" > %base_dir%BatPath.bat
	echo set DEVENV="D:\programfiles(x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv.exe" >> %base_dir%BatPath.bat
	echo Error CMAKEPATH not define
)

cd %base_dir%

::if exist %base_dir%ThirdParty\Src\build\ThirdParty.sln (
::	start "" %base_dir%ThirdParty\Src\build\ThirdParty.sln
::) else (
::	echo Error %base_dir%ThirdParty\Src\build\ThirdParty.sln not exist
::)

::%DEVENV% %base_dir%ThirdParty\Src\build\ThirdParty.sln /build "RelWithDebInfo" /project "INSTALL"
%DEVENV% %base_dir%ThirdParty\Src\build\ThirdParty.sln /build "Debug" /project "INSTALL"

pause