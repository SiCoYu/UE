:: echo on
@echo off
set BaseDir=%~dp0
%BaseDir:~0,2%

cd %BaseDir%
%BaseDir:~0,2%

F:\ProgramFiles\android\android-ndk-r13b\ndk-build.cmd NDK_PROJECT_PATH=%BaseDir% NDK_APPLICATION_MK=%BaseDir%\Application.mk