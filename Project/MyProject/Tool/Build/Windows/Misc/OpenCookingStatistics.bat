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

cd %UE4_CODE_ROOT_PATH%

:: @brief : Cooking Statistics
:: @ref : https://docs.unrealengine.com/en-us/Engine/Performance/CookingStats
%UE4_CODE_ROOT_PATH%\Saved\Stats\<datetime>Stats.csv

pause