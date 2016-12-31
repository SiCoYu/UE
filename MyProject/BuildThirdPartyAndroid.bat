:: echo on
@echo off
set BaseDir=%~dp0
%BaseDir:~0,2%

cd %BaseDir%ThirdParty\Src\lua-5.3.1
%BaseDir:~0,2%

F:\ProgramFiles\android\android-ndk-r13b\ndk-build.cmd NDK_PROJECT_PATH=%BaseDir%ThirdParty\Src\lua-5.3.1 NDK_APPLICATION_MK=%BaseDir%ThirdParty\Src\lua-5.3.1\Application.mk