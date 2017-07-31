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

cd %BASE_DIR%

if not exist %APK_ORIG_FULL_PATH% (
	echo "%APK_ORIG_FULL_PATH% is not exist"
) else (
	REM 先把上次打出来的apk删除掉
	if exist %APK_ORIG_FULL_PATH% (
		echo "delete apk %APK_ORIG_FULL_PATH%"
		del %APK_ORIG_FULL_PATH%
	) else (
		echo "apk output path=%APK_ORIG_FULL_PATH%"
	)
	
	echo "%APK_ORIG_FULL_PATH% is exist"
	ren %APK_ORIG_FULL_PATH% Plane.apk
)

rem pause