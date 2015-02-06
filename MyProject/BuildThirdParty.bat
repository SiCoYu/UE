:: echo on
@echo off
set base_dir=%~dp0
%base_dir:~0,2%

if exist %base_dir%ThirdParty\Src\build rd /s /q %base_dir%ThirdParty\Src\build
mkdir %base_dir%ThirdParty\Src\build

cd %base_dir%ThirdParty\Src\build

if exist %base_dir%BatPath.bat call %base_dir%BatPath.bat
if defined CMAKEPATH (
	%CMAKEPATH% -G "Visual Studio 12 2013" -DCMAKE_BUILD_TYPE:STRING=RelWithDebInfo %base_dir%ThirdParty\Src
) else (
	echo set CMAKEPATH="D:\Program Files (x86)\cmake-3.1.0-win32-x86\bin\cmake.exe" > %base_dir%BatPath.bat
	echo Error CMAKEPATH not define
)

cd %base_dir%

if exist %base_dir%ThirdParty\Src\build\ThirdParty.sln (
	start "" %base_dir%ThirdParty\Src\build\ThirdParty.sln
) else (
	echo Error %base_dir%ThirdParty\Src\build\ThirdParty.sln not exist
)

pause