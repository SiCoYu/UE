::echo off
echo on

set BASE_DIR=%~dp0
echo "BASE_DIR="%BASE_DIR%

set DRIVER=%BASE_DIR:~0,2%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

rem https://blog.csdn.net/u012702547/article/details/48196933
rem G:\ProgramFiles\android\android-ndk-r17b\ndk-build.cmd -B V=1 NDK_LOG=1 -j 2 -C %BASE_DIR% NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_APPLICATION_MK=./Application.mk
G:\ProgramFiles\android\android-ndk-r17b\ndk-build.cmd -B NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_APPLICATION_MK=./Application.mk