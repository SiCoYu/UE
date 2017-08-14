::echo on

echo off

if not defined BuildParam (
	if exist BuildParam.bat (
		call BuildParam.bat
	)
)

if exist CreateDir.bat (
	call CreateDir.bat
)

set BASE_DIR=%~dp0
echo "BASE_DIR="%BASE_DIR%

set DRIVER=%BASE_DIR:~0,2%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

cd %UE4_BATCH_FILES_FULL_PATH%

:: ref VS IDE [Solution Configurations] -- Debug Editor, [Solution Platforms] -- Win64
:: UE4Editor : UE4 + Editor
%BUILD_APP_FULL_PATH% UE4Editor Android Debug -waitmutex

pause