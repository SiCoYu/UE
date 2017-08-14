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

:: @brief Building Derived Data
:: @ref https://docs.unrealengine.com/latest/INT/Engine/Basics/DerivedDataCache/index.html
:: UE4\Engine\Binaries\Win64\UE4Editor.exe MyGame -run=DerivedDataCache -fill
%UE4_BIN_APP_CMD_FULL_PATH%  MyGame -run=DerivedDataCache -fill

:: @brief Distributing with a DDC
:: @ref https://docs.unrealengine.com/latest/INT/Engine/Basics/DerivedDataCache/index.html
UE4Editor.exe [GameName] -run=DerivedDataCache -fill -DDC=CreatePak

pause