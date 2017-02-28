CurrentPath=$(pwd)
BasePath=$(cd `dirname $0`; pwd)

cd "$BasePath"

WorkSpacePath=/Users/zt-2010879/File/OpenSource/UnrealEngine/UE4.xcworkspace
SchemeName=UE4
xcodebuild -workspace "$WorkSpacePath" -scheme "$SchemeName"