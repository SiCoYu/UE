set BASE_DIR=%~dp0
set DRIVER=%BASE_DIR:~0,2%

echo "BASE_DIR="%BASE_DIR%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

rem UNITY Path
set BuildParam=""

set UE4_PATH=D:\ProgramFiles\Unity\Editor\Unity.exe
echo "UE4_PATH="%UE4_PATH%

set PROJECT_PATH=%BASE_DIR%..\..\..\..
echo "PROJECT_PATH="%PROJECT_PATH%

set OUTPUT_PATH=%PROJECT_PATH%\OutPut
echo "OUTPUT_PATH="%OUTPUT_PATH%

set APK_FULL_PATH="%OUTPUT_PATH%\Bin\Android\Plane.apk"
echo "APK_FULL_PATH="%APK_FULL_PATH%