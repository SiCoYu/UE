::echo off
echo on

set BASE_DIR=%~dp0
set DRIVER=%BASE_DIR:~0,2%

echo "BASE_DIR="%BASE_DIR%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

rem UNITY Path
set BuildParam=""

:: UE4 start
set UE4_PLATFORM="Win64"
set UE4_BUILD_CONFIGURATION="Debug"

set UE4_CODE_ROOT_PATH="H:\Self\Self\unreal\UnrealEngine-git\UnrealEngine"
echo "UE4_CODE_ROOT_PATH="%UE4_CODE_ROOT_PATH%

set UE4_BIN_FULL_PATH=%UE4_CODE_ROOT_PATH%\Engine\Binaries\%UE4_PLATFORM%
echo "UE4_BIN_FULL_PATH="%UE4_BIN_FULL_PATH%

set UE4_BIN_APP_FULL_PATH=%UE4_BIN_FULL_PATH%\UE4Editor-%UE4_PLATFORM%-%UE4_BUILD_CONFIGURATION%.exe
echo "UE4_BIN_APP_FULL_PATH="%UE4_BIN_APP_FULL_PATH%

set UE4_BIN_APP_CMD_FULL_PATH=%UE4_BIN_FULL_PATH%\UE4Editor-%UE4_PLATFORM%-%UE4_BUILD_CONFIGURATION%-Cmd.exe
echo "UE4_BIN_APP_CMD_FULL_PATH="%UE4_BIN_APP_CMD_FULL_PATH%

set UE4_FRONTEND_APP_FULL_PATH=%UE4_BIN_FULL_PATH%\UnrealFrontend-%UE4_PLATFORM%-%UE4_BUILD_CONFIGURATION%.exe
echo "UE4_FRONTEND_APP_FULL_PATH="%UE4_FRONTEND_APP_FULL_PATH%

set UE4_BATCH_FILES_FULL_PATH=%UE4_CODE_ROOT_PATH%"\Engine\Build\BatchFiles"
echo "UE4_BATCH_FILES_FULL_PATH="%UE4_BATCH_FILES_FULL_PATH%

set RUNUAT_APP_FULL_PATH=%UE4_BATCH_FILES_FULL_PATH%"\RunUAT.bat"
echo "RUNUAT_APP_FULL_PATH="%RUNUAT_APP_FULL_PATH%

set UNREALPAK_APP_FULL_PATH=%UE4_BIN_FULL_PATH%"\UnrealPak.exe"
echo "UNREALPAK_APP_FULL_PATH="%UNREALPAK_APP_FULL_PATH%

:: My App start
set MYPROJECT_ROOT_FULL_PATH="H:\Self\Self\unreal\UE-GIT\UE-BP\Client"
echo "MYPROJECT_ROOT_FULL_PATH="%MYPROJECT_ROOT_FULL_PATH%

set MYPROJECT_CONFIG_FULL_PATH=%MYPROJECT_ROOT_FULL_PATH%"\InventoryUIwithUMG.uproject"
echo "MYPROJECT_CONFIG_FULL_PATH="%MYPROJECT_CONFIG_FULL_PATH%

set OUTPUT_ROOT_PATH=%MYPROJECT_ROOT_FULL_PATH%"\OutPut"
echo "OUTPUT_ROOT_PATH="%OUTPUT_ROOT_PATH%

set BIN_OUT_FULL_PATH=%OUTPUT_ROOT_PATH%"\Bin"
echo "BIN_OUT_FULL_PATH="%BIN_OUT_FULL_PATH%

set BIN_PLATFORM_OUT_FULL_PATH=%BIN_OUT_FULL_PATH%"\Android"
echo "BIN_PLATFORM_OUT_FULL_PATH="%BIN_PLATFORM_OUT_FULL_PATH%

set BIN_APP_ORIG_FULL_PATH=%BIN_PLATFORM_OUT_FULL_PATH%"\test.apk"
echo "BIN_APP_ORIG_FULL_PATH="%BIN_APP_ORIG_FULL_PATH%

set Bin_APP_FULL_PATH=%BIN_PLATFORM_OUT_FULL_PATH%"\Plane.apk"
echo "Bin_APP_FULL_PATH="%Bin_APP_FULL_PATH%

set BIN_APP_PLATFORM="Android"
echo "BIN_APP_PLATFORM="%BIN_APP_PLATFORM%

set BIN_APP_START_MAP=%MYPROJECT_ROOT_FULL_PATH%\"Content\Maps\Example_Map.umap"
echo "BIN_APP_START_MAP="%BIN_APP_START_MAP%