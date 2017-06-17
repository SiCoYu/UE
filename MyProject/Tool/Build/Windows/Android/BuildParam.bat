echo off

set BASE_DIR=%~dp0
set DRIVER=%BASE_DIR:~0,2%

echo "BASE_DIR="%BASE_DIR%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

rem UNITY Path
set BuildParam=""

set UE4_ROOT_PATH="F:\File\opensource\UnrealEngine-4.0\UnrealEngine-git"
echo "UE4_ROOT_PATH="%UE4_ROOT_PATH%

set UE4_PATH="%UE4_ROOT_PATH%\Engine\Binaries\Win64\UnrealFrontend-Win64-Debug.exe"
echo "UE4_PATH="%UE4_PATH%

set RUNUAT_PATH_NO_FILE_NAME="%UE4_ROOT_PATH%\Engine\Build\BatchFiles"
echo "RUNUAT_PATH_NO_FILE_NAME="%RUNUAT_PATH_NO_FILE_NAME%

set RUNUAT_PATH="%UE4_ROOT_PATH%\Engine\Build\BatchFiles\RunUAT.bat"
echo "RUNUAT_PATH="%RUNUAT_PATH%

set PROJECT_PATH="%BASE_DIR%..\..\..\.."
echo "PROJECT_PATH="%PROJECT_PATH%

set PROJECT_CONFIG_PATH="%PROJECT_PATH%\MyProject.uproject"
echo "PROJECT_CONFIG_PATH="%PROJECT_CONFIG_PATH%

set OUTPUT_PATH="%PROJECT_PATH%\OutPut"
echo "OUTPUT_PATH="%OUTPUT_PATH%

set APK_FULL_PATH_NO_FILE_NAME="%OUTPUT_PATH%\Bin\Android"
echo "APK_FULL_PATH_NO_FILE_NAME="%APK_FULL_PATH_NO_FILE_NAME%

set APK_ORIG_FULL_PATH="%OUTPUT_PATH%\Bin\Android\test.apk"
echo "APK_ORIG_FULL_PATH="%APK_ORIG_FULL_PATH%

set APK_FULL_PATH="%OUTPUT_PATH%\Bin\Android\Plane.apk"
echo "APK_FULL_PATH="%APK_FULL_PATH%