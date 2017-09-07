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
:: stdout
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: testexit=
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: emitdrawevents
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: CLEANSCREENSHOTS
:: Engine\Source\Runtime\Core\Private\HAL\FileManagerGeneric.cpp
:: CLEANLOGS
:: Engine\Source\Runtime\Core\Private\HAL\FileManagerGeneric.cpp
:: RUN=
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: -GAME
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: -SERVER
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: BUILDMACHINE
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: norecentproject
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: BENCHMARK
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: Deterministic
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: UseFixedTimeStep
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: FixedSeed
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: -CmdLineFile=
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: UE-CmdLineArgs : additional command line arguments from environment variable
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: enablehighdpi
:: Engine\Source\Runtime\Core\Private\Windows\WindowsPlatformMisc.cpp
:: purgatorymallocproxy
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: poisonmallocproxy
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: WaitForDebugger
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: NOCONSOLE
:: Engine\Source\Runtime\Core\Private\GenericPlatform\GenericPlatformOutputDevices.cpp
:: nohmd
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: emulatestereo
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: PROMPTREMOTEDEBUG
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: PROMPTREMOTEDEBUGENSURE
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: WARNINGSASERRORS
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: SILENT
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
:: LOG
:: Engine\Source\Runtime\Launch\Private\LaunchEngineLoop.cpp
%UE4_BIN_APP_FULL_PATH% crashreports noinnerexception useautoreporter -cmd UTF8Output LLM NOLLM

pause