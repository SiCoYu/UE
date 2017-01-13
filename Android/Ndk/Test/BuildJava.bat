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

set JDK_PATH=D:\ProgramFiles\Java\jdk1.8.0_65

rem %JDK_PATH%\bin\javac.exe -d %JAVA_CLASS_OUTPATH% -sourcepath %BASE_DIR%Java Com\Ndk\Test\JniClient.java
rem %JDK_PATH%\bin\javac.exe -d %JAVA_CLASS_OUTPATH% -sourcepath %JAVA_SRC_ROOT% -s %JAVA_SRC_ROOT% Com\Ndk\Test\JniClient.java
rem %JDK_PATH%\bin\javac.exe -d %JAVA_CLASS_OUTPATH% -sourcepath %JAVA_SRC_ROOT% -s %JAVA_SRC_ROOT% @%JAVA_SRC_ROOT%/Sources.list
%JDK_PATH%\bin\javac.exe -d %JAVA_CLASS_OUTPATH% @%JAVA_SRC_ROOT%/Sources.list

cd %INIT_PATH%