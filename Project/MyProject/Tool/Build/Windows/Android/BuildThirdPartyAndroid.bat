::echo off
echo on

set BASE_DIR=%~dp0
echo "BASE_DIR="%BASE_DIR%

set DRIVER=%BASE_DIR:~0,2%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

if not defined BuildParam (
	if exist ..\BuildParam.bat (
		call ..\BuildParam.bat
	)
)

%CMAKE_BIN% -DCMAKE_TOOLCHAIN_FILE=%NDK_TOOLCHAIN_FILE% \
    -DANDROID_ABI=whatever %THIRDPARTY_SRC%

rem pause