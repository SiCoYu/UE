:: echo on
rem @echo off
set BASE_DIR=%~dp0
%BASE_DIR:~0,2%

cd %BASE_DIR%
%BASE_DIR:~0,2%

set JAVA_CLASS_PATH=%BASE_DIR%Java\JavaClass
set INIT_PATH=%BASE_DIR%
set JDK_PATH=D:\ProgramFiles\Java\jdk1.8.0_65

%JDK_PATH%\bin\java.exe -classpath %JAVA_CLASS_PATH% Com.Ndk.Test.TestNdkActivity

cd %INIT_PATH%