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

::@ref Build Configurations Reference
::@url https://docs.unrealengine.com/latest/INT/Programming/Development/BuildConfigurations/index.html
::%RUNUAT_APP_FULL_PATH% BuildCookRun -project=%MYPROJECT_CONFIG_FULL_PATH% -noP4 -platform=%BIN_APP_PLATFORM% -clientconfig=Debug -serverconfig=Debug -cook -allmaps -build -stage -pak -archive -archivedirectory=%BIN_PLATFORM_OUT_FULL_PATH%

::%RUNUAT_APP_FULL_PATH% BuildCookRun -project=%MYPROJECT_CONFIG_FULL_PATH% -noP4 -platform=%BIN_APP_PLATFORM% -cook -allmaps -build -stage -pak -archive -archivedirectory=%BIN_PLATFORM_OUT_FULL_PATH%

::RunUAT.bat -list
::RunUAT.bat -help BuildCookRun
::%RUNUAT_APP_FULL_PATH% BuildCookRun -project=%MYPROJECT_CONFIG_FULL_PATH% -noP4 -platform=%BIN_APP_PLATFORM% -clientconfig=Debug -serverconfig=Debug -cook -map=%BIN_APP_START_MAP% -build -stage -pak -package -CookAll -SkipCookingEditorContent -archive -archivedirectory=%BIN_PLATFORM_OUT_FULL_PATH%

::BuildCookRun -targetplatform=Android+Win64 -NoP4 -UTF8Output -cook -build -stage -pak -package -project=F:\File\opensource\UnrealEngine-4.0\UE-git\UE-BP\Client\InventoryUIwithUMG.uproject -cookdir=F:\File\opensource\UnrealEngine-4.0\UE-git\UE-BP -archive -archivedirectory=F:\File\opensource\UnrealEngine-4.0\UE-git\UE-BP -ue4exe=UE4Editor-Win64-Debug.exe -clientconfig=Debug -NoCompileEditor

::BuildCookRun -targetplatform=Android -NoP4 -UTF8Output -cook -build -stage -pak -package -project=H:\Self\Self\unreal\UE-GIT\UE-BP\Client\InventoryUIwithUMG.uproject -cookdir=H:\Self\Self\unreal\UE-GIT\UE-BP\Client -archive -archivedirectory=H:\Self\Self\unreal\UE-GIT\UE-BP\Client -ue4exe=UE4Editor-Win64-Debug.exe -clientconfig=Debug -NoCompileEditor -deploy

::BuildCookRun -targetplatform=Android -NoP4 -UTF8Output -cook -build -stage -pak -package -project=F:\File\opensource\UnrealEngine-4.0\UE-git\UE-BP\Client\InventoryUIwithUMG.uproject -cookdir=F:\File\opensource\UnrealEngine-4.0\UE-git\UE-BP\Client -archive -archivedirectory=F:\File\opensource\UnrealEngine-4.0\UE-git\UE-BP\Client -ue4exe=UE4Editor-Win64-Debug.exe -clientconfig=Debug -NoCompileEditor -deploy

::%RUNUAT_APP_FULL_PATH% BuildCookRun -targetplatform=Android -NoP4 -UTF8Output -cook -build -stage -pak -package -project=%MYPROJECT_CONFIG_FULL_PATH% -cookdir=%BIN_PLATFORM_OUT_FULL_PATH% -archive -archivedirectory=%BIN_PLATFORM_OUT_FULL_PATH% -ue4exe=UE4Editor-Win64-Debug.exe -clientconfig=Debug -NoCompileEditor -deploy

::%RUNUAT_APP_FULL_PATH% BuildCookRun -targetplatform=Android -NoP4 -UTF8Output -cook -build -stage -pak -package -project=%MYPROJECT_CONFIG_FULL_PATH% -cookdir=%BIN_PLATFORM_OUT_FULL_PATH% -archive -archivedirectory=%BIN_PLATFORM_OUT_FULL_PATH% -ue4exe=UE4Editor-Win64-Debug.exe -clientconfig=Development -NoCompileEditor -deploy

%RUNUAT_APP_FULL_PATH% BuildCookRun -targetplatform=Android -NoP4 -UTF8Output -cook -build -stage -pak -package -project=%MYPROJECT_CONFIG_FULL_PATH% -cookdir=%BIN_PLATFORM_OUT_FULL_PATH% -archive -archivedirectory=%BIN_PLATFORM_OUT_FULL_PATH% -ue4exe=UE4Editor.exe -clientconfig=Development -NoCompileEditor -deploy -Architectures=-armv7 -GPUArchitectures=-es2

cd %BASE_DIR%

if not exist %Bin_APP_ORIG_FULL_PATH% (
	echo "%Bin_APP_ORIG_FULL_PATH% is not exist"
) else (
	REM delete APP
	if exist %Bin_APP_ORIG_FULL_PATH% (
		echo "delete apk %Bin_APP_ORIG_FULL_PATH%"
		del %Bin_APP_ORIG_FULL_PATH%
	) else (
		echo "apk output path=%Bin_APP_ORIG_FULL_PATH%"
	)
	
	echo "%Bin_APP_ORIG_FULL_PATH% is exist"
	ren %Bin_APP_ORIG_FULL_PATH% Plane.apk
)

pause