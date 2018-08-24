::echo off
echo on

set BASE_DIR=%~dp0
echo "BASE_DIR="%BASE_DIR%

set DRIVER=%BASE_DIR:~0,2%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

rem G:\ProgramFiles\android\android-ndk-r17b\ndk-build.cmd NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_APPLICATION_MK=./Application.mk

G:\ProgramFiles\android\android-ndk-r17b\ndk-build.cmd -B NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_APPLICATION_MK=./Application.mk APP_PLATFORM=android-22 APP_ABI=armeabi-v7a MY_DEBUG=DEBUG