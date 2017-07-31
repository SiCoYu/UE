::echo off
echo on

if not defined BuildParam (
	if exist BuildParam.bat (
		call BuildParam.bat
	)
)

set BASE_DIR=%~dp0
echo "BASE_DIR="%BASE_DIR%

set DRIVER=%BASE_DIR:~0,2%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

set CUR_PATH=%OUTPUT_ROOT_PATH%
if exist %CUR_PATH% (
	echo "%CUR_PATH% is exist"
	del /f /s /q %CUR_PATH%
) else (
	echo "%CUR_PATH% is not exist"
)

rem pause