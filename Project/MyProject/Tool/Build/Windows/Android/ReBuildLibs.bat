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
::..\..\Build\BatchFiles\Rebuild.bat UE4Editor Win64 Debug -waitmutex
::%REBUILD_APP_FULL_PATH% UE4Game Android Shipping -waitmutex
::%REBUILD_APP_FULL_PATH% UE4Client Android Debug -waitmutex -log=ReBuildLibs-log.txt -project=F:\File\opensource\UnrealEngine-4.0\UE-git\UE-BP\Client\InventoryUIwithUMG.uproject -Clean -Deploy -cmakefile -progress -verbose -NoHotReload
::%REBUILD_APP_FULL_PATH% UE4Game Android Debug -waitmutex -log=ReBuildLibs-log.txt -Clean -Deploy -cmakefile -progress -verbose -NoHotReload
%REBUILD_APP_FULL_PATH% UE4Game Android Debug -waitmutex

pause