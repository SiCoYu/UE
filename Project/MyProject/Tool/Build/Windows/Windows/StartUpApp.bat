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

:: brief game Tells the engine what GameInfo class to use (overriding default).
:: ref https://docs.unrealengine.com/latest/INT/Programming/Basics/CommandLineArguments/index.html
%UE4_BIN_APP_FULL_PATH% %MYPROJECT_CONFIG_FULL_PATH% %BIN_APP_START_MAP%?game=MyGameInfo -silent LOG=MyLog.txt -game

pause