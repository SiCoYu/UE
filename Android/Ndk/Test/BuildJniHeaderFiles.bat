:: echo on
echo on
rem @echo off
set BASE_DIR=%~dp0
%BASE_DIR:~0,2%

cd %BASE_DIR%
%BASE_DIR:~0,2%

set JAVA_CLASS_PATH=%BASE_DIR%Java\JavaClass
set ANDROID_CLASS_PATH=F:\ProgramFiles\android\sdk\platforms\android-25\android.jar

cd %JAVA_CLASS_PATH%

set INIT_PATH=%BASE_DIR%

rem D:\ProgramFiles\Java\jdk1.8.0_65\bin\javah.exe -jni -classpath %ANDROID_CLASS_PATH%;%JAVA_CLASS_PATH% Com\Ndk\Test\JniClient
D:\ProgramFiles\Java\jdk1.8.0_65\bin\javah.exe -jni -classpath %ANDROID_CLASS_PATH%;%JAVA_CLASS_PATH% Com.Ndk.Test.JniClient

cd %INIT_PATH%

