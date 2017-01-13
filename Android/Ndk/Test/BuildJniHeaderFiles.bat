:: echo on
rem @echo off
set BASE_DIR=%~dp0
%BASE_DIR:~0,2%

cd %BASE_DIR%
%BASE_DIR:~0,2%

set JAVA_SRC_ROOT=%BASE_DIR%Java
cd %JAVA_SRC_ROOT%

set JAVA_CLASS_PATH=%BASE_DIR%Java\JavaClassFiles

set INIT_PATH=%BASE_DIR%

D:\ProgramFiles\Java\jdk1.8.0_65\bin\javah.exe -classpath %JAVA_CLASS_PATH% -jni Com\Ndk\Test\JniClient

cd %INIT_PATH%