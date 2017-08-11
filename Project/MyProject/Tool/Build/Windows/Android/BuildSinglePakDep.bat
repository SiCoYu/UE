::@ref https://docs.unrealengine.com/latest/INT/Engine/Deployment/Cooking/index.html

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

::set INPUT_FULL_PATH="F:\File\opensource\UnrealEngine-4.0\UE-git\UE-BP\Client\Content\Character\HeroFPP.uasset"
::set OUTPUT_FULL_PATH="F:\File\opensource\UnrealEngine-4.0\UE-git\OutPak.Pak"

set INPUT_FULL_PATH="H:\Self\Self\unreal\UE-GIT\UE-BP\Client\Content\Character\HeroFPP.uasset"
set OUTPUT_FULL_PATH="H:\Self\Self\unreal\UE-GIT\UE-BP\Client\OutPak.Pak"

%UNREALPAK_APP_FULL_PATH% %OUTPUT_FULL_PATH% -ExportDependencies=%OUTPUT_DEP_FILE_FULL_PATH% -NoAssetRegistryCache -ForceDependsGathering

pause