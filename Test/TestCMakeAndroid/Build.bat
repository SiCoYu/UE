set BASE_DIR=%~dp0
echo "BASE_DIR="%BASE_DIR%

set DRIVER=%BASE_DIR:~0,2%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

D:\ProgramFiles\cmake-3.11.3-win64-x64\bin\cmake -DDEBUG=ON -DCMAKE_TOOLCHAIN_FILE=C:/ProgramFiles/Android/android-ndk-r17b/build/cmake/android.toolchain.cmake -DANDROID_NDK=C:/ProgramFiles/Android/android-ndk-r17b -DANDROID_ABI=armeabi-v7a -DANDROID_TOOLCHAIN=clang -DANDROID_PLATFORM=android-21 -DANDROID_STL=c++_shared

pause