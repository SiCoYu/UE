:: echo on
echo on
rem @echo off
set BaseDir=%~dp0
%BaseDir:~0,2%

cd %BaseDir%
%BaseDir:~0,2%

set JAVA_SRC_ROOT=%BaseDir%Java
cd %JAVA_SRC_ROOT%

set JAVA_CLASS_OUTPATH=%BaseDir%Java\JavaClassFiles

set INIT_PATH=%BaseDir%

rem D:\ProgramFiles\Java\jdk1.8.0_65\bin\javac.exe -d %JAVA_CLASS_OUTPATH% -sourcepath %BaseDir%Java Com\Ndk\Test\JniClient.java
D:\ProgramFiles\Java\jdk1.8.0_65\bin\javac.exe -d %JAVA_CLASS_OUTPATH% Com\Ndk\Test\JniClient.java

cd %INIT_PATH%