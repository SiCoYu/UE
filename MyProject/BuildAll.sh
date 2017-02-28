CurrentPath=$(pwd)
BasePath=$(cd `dirname $0`; pwd)

cd "$BasePath"

WorkSpacePath="/Users/zt-2010879/File/OpenSource/UnrealEngine/UE4.xcworkspace"

SchemeName="BlankProgram"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="BuildPatchTool"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="CrashReportClient"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="MinidumpDiagnostics"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="CrossCompilerTool"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="UnrealLaunchDaemon"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="DsymExporter"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="ShaderCacheTool"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="UE4EditorServices"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="UnrealAtoS"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="ShaderCompileWorker"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="SlateViewer"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="SymbolDebugger"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="TestPAL"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="UnrealCEFSubProcess"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="UnrealCodeAnalyzer"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="UnrealFileServer"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="UnrealFrontend"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="UnrealHeaderTool"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="UnrealLightmass"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="UnrealPak"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="UnrealVersionSelector"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="UnrealWatchdog"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="BootstrapPackagedGame"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"

SchemeName="UE4"
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"