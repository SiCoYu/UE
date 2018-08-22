::echo off
echo on

set BASE_DIR=%~dp0
echo "BASE_DIR="%BASE_DIR%

set DRIVER=%BASE_DIR:~0,2%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

C:\ProgramFiles\Android\android-ndk-r17b\ndk-build.cmd Android.mk