::echo off
echo on

set BASE_DIR=%~dp0
echo "BASE_DIR="%BASE_DIR%

set DRIVER=%BASE_DIR:~0,2%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

if not defined BuildParam (
	if exist ..\BuildParam.bat (
		call ..\BuildParam.bat
	)
)

rem G:\ProgramFiles\cmake-3.7.2-win64-x64\bin\cmake.exe G:/UE/Project/MyProject/MyProject/ThirdParty/Src -G "Unix Makefiles" -DANDROID_NDK=G:/ProgramFiles/android/android-ndk-r17b/ -DCMAKE_TOOLCHAIN_FILE=G:/ProgramFiles/android/android-ndk-r17b/build/cmake/android.toolchain.cmake -DANDROID_ABI=arm64-v8a
rem https://developer.android.google.cn/ndk/guides/cmake
rem https://stackoverflow.com/questions/32753905/cmake-android-ndk-toolchain-on-windows
rem https://blog.csdn.net/xinyu391/article/details/73614692
%CMAKE_BIN% -DCMAKE_TOOLCHAIN_FILE=%NDK_TOOLCHAIN_FILE% -DANDROID_ABI=whatever %THIRDPARTY_SRC%

rem pause