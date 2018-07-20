::echo off
echo on

set BASE_DIR=%~dp0
echo "BASE_DIR="%BASE_DIR%

set DRIVER=%BASE_DIR:~0,2%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

D:/File/Self/UE/UnrealEngine/Engine/Binaries/DotNET/UnrealBuildTool.exe Debug Win64 -Project="D:/File/Self/UE/UE/Project/MyProject/MyProject/MyProject.uproject" -TargetType=Editor -Progress -NoHotReloadFromIDE -2017

rem pause