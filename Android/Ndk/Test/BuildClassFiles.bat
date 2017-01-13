:: echo on
rem @echo off
set BASE_DIR=%~dp0
%BASE_DIR:~0,2%

cd %BASE_DIR%
%BASE_DIR:~0,2%

set JAVA_SRC_ROOT=%BASE_DIR%Java
cd %JAVA_SRC_ROOT%

set JAVA_CLASS_OUTPATH=%BASE_DIR%Java\JavaClass

set INIT_PATH=%BASE_DIR%

rem D:\ProgramFiles\Java\jdk1.8.0_65\bin\javac.exe -d %JAVA_CLASS_OUTPATH% -sourcepath %BASE_DIR%Java Com\Ndk\Test\JniClient.java
D:\ProgramFiles\Java\jdk1.8.0_65\bin\javac.exe -d %JAVA_CLASS_OUTPATH% Com\Ndk\Test\JniClient.java

cd %INIT_PATH%