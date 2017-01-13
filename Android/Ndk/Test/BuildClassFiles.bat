:: echo on
@echo off
set BaseDir=%~dp0
%BaseDir:~0,2%

cd %BaseDir%
%BaseDir:~0,2%

D:\ProgramFiles\Java\jdk1.8.0_65\bin\javac.exe -d %BaseDir%Java\JavaClassFiles -sourcepath %BaseDir%Java Com\Ndk\Test\JniClient.java