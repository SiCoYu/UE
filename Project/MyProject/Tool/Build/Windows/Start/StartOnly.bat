::echo on

echo off

if not defined ../BuildParam (
	if exist ../BuildParam.bat (
		call ../BuildParam.bat
	)
)

if exist ../CreateDir.bat (
	call ../CreateDir.bat
)

set BASE_DIR=%~dp0
echo "BASE_DIR="%BASE_DIR%

set DRIVER=%BASE_DIR:~0,2%
echo "DRIVER="%DRIVER%

%DRIVER%
cd %BASE_DIR%

:: LLM NOLLM
:: Engine\Source\Runtime\Core\Private\HAL\LowLevelMemTracker.cpp
:: UTF8Output
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: crashreports noinnerexception useautoreporter
:: Engine\Source\Runtime\Launch\Private\Windows\LaunchWindows.cpp
%UE4_BIN_APP_FULL_PATH% crashreports noinnerexception useautoreporter -cmd UTF8Output LLM NOLLM

pause