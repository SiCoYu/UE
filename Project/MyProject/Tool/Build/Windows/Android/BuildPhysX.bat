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

%RUNUAT_APP_FULL_PATH% BuildPhysX TargetLibs=PhysX+APEX TargetPlatforms=Android TargetConfigs=profile+debug+checked

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

rem pause