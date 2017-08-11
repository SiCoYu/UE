::@ref https://docs.unrealengine.com/latest/INT/Engine/Deployment/Cooking/index.html

::echo on

echo off

if not defined BuildParam (
	if exist BuildParam.bat (
		call BuildParam.bat
	)
)

if exist BuildMkDir.bat (
	call BuildMkDir.bat
)

set BASE_DIR=%~dp0
echo "BASE_DIR="%BASE_DIR%

set DRIVER=%BASE_DIR:~0,2%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

%UE4_BIN_APP_CMD_FULL_PATH% %UPROJECT_FULL_PATH% -run=cook -targetplatform=%BIN_APP_PLATFORM% -iterate -CookAll -Compressed

rem pause