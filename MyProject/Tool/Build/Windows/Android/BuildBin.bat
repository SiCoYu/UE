::echo on

echo off

set BASE_DIR=%~dp0
set DRIVER=%BASE_DIR:~0,2%

echo "BASE_DIR="%BASE_DIR%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

SETLOCAL ENABLEEXTENSIONS
if not defined BuildParam (
	if exist BuildParam.bat (
		call BuildParam.bat
	)
)

set EDITOR_LOG_PATH=%PROJECT_PATH%\OutPut\EditorLog-Android-BuildBin.txt
echo "EDITOR_LOG_PATH="%EDITOR_LOG_PATH%

set TASK_NAME="BuildBin"
echo "TASK_NAME="%TASK_NAME%

set PLATFORM="Android"
echo "PLATFORM="%PLATFORM%

set MAIN_ENTRY="EditorTool.CmdSys.cmdMain"
echo "MAIN_ENTRY="%MAIN_ENTRY%

if not exist %OUTPUT_PATH% (
	echo "%OUTPUT_PATH% is not exist"
	md %OUTPUT_PATH%
) else (
	echo "%OUTPUT_PATH% is exist"
)

%UNITY_PATH% -quit -batchmode -nographics -logFile "%EDITOR_LOG_PATH%" -projectPath "%PROJECT_PATH%" -executeMethod %MAIN_ENTRY% Platform=%PLATFORM% OutputPath=%OUTPUT_PATH% Task=%TASK_NAME%

set ORIG_PATH_NAME=%OUTPUT_PATH%\Bin\Android\test.apk
if not exist %ORIG_PATH_NAME% (
	echo "%ORIG_PATH_NAME% is not exist"
) else (
	REM 先把上次打出来的apk删除掉
	if exist %APK_FULL_PATH% (
		echo "delete apk %APK_FULL_PATH%"
		del %APK_FULL_PATH%
	) else (
		echo "apk output path=%APK_FULL_PATH%"
	)
	
	echo "%ORIG_PATH_NAME% is exist"
	ren %ORIG_PATH_NAME% Plane.apk
)

rem pause