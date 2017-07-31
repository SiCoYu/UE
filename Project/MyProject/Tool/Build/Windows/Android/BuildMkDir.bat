::echo off
echo on

set BASE_DIR=%~dp0
set DRIVER=%BASE_DIR:~0,2%

echo "BASE_DIR="%BASE_DIR%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

SETLOCAL ENABLEEXTENSIONS
if not defined BuildParam (
	if exist BuildParam.bat (
		call BuildParam.bat
	)
)

set CUR_PATH=%OUTPUT_PATH%
if not exist %CUR_PATH% (
	echo "%CUR_PATH% is not exist"
	md %CUR_PATH%
) else (
	echo "%CUR_PATH% is exist"
)

set CUR_PATH="%OUTPUT_PATH%\Bin"
if not exist %CUR_PATH% (
	echo "%CUR_PATH% is not exist"
	md %CUR_PATH%
) else (
	echo "%CUR_PATH% is exist"
)

set CUR_PATH="%OUTPUT_PATH%\Bin\Android"
if not exist %CUR_PATH% (
	echo "%CUR_PATH% is not exist"
	md %CUR_PATH%
) else (
	echo "%CUR_PATH% is exist"
)