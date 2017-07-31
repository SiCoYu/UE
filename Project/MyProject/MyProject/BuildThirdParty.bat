::echo on
rem @echo off
@echo off
set BaseDir=%~dp0
%BaseDir:~0,2%

set GENERATOR="Visual Studio 14 2015 Win64"
set DEVENV="D:\programfiles(x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv.exe"

if exist %BaseDir%ThirdParty\Src\build rd /s /q %BaseDir%ThirdParty\Src\build
mkdir %BaseDir%ThirdParty\Src\build

cd %BaseDir%ThirdParty\Src\build

if exist %BaseDir%BatPath.bat call %BaseDir%BatPath.bat
if defined CMAKEPATH (
	%CMAKEPATH% -G%GENERATOR% -DCMAKE_BUILD_TYPE:STRING=RelWithDebInfo -DCMAKE_INSTALL_PREFIX:PATH=%BaseDir%ThirdParty\Src\build %BaseDir%ThirdParty\Src
) else (
	echo set CMAKEPATH="F:\ProgramFiles\cmake-3.7.0-win64-x64\bin\cmake.exe" > %BaseDir%BatPath.bat
	echo set DEVENV="D:\programfiles(x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv.exe" >> %BaseDir%BatPath.bat
	echo Error CMAKEPATH not define
)

cd %BaseDir%

::if exist %BaseDir%ThirdParty\Src\build\ThirdParty.sln (
::	start "" %BaseDir%ThirdParty\Src\build\ThirdParty.sln
::) else (
::	echo Error %BaseDir%ThirdParty\Src\build\ThirdParty.sln not exist
::)

::%DEVENV% %BaseDir%ThirdParty\Src\build\ThirdParty.sln /build "RelWithDebInfo" /project "INSTALL"
%DEVENV% %BaseDir%ThirdParty\Src\build\ThirdParty.sln /build "Debug" /project "INSTALL"

pause