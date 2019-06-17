#pragma once

// Module.MyPlugin.cpp.obj : error LNK2019: unresolved external symbol "public: __cdecl TestModuleReferenceSubDir::TestModuleReferenceSubDir(void)" (??0TestModuleReferenceSubDir@@QEAA@XZ) referenced in function "public: __cdecl ATestPluginCharacter::ATestPluginCharacter(void)" (??0ATestPluginCharacter@@QEAA@XZ)
// MyProjectEditor 如果需要被插件引用， 需要添加 MYPROJECTEDITOR_API ，否则会导致编译不过
class MYPROJECTEDITOR_API TestModuleReferenceSubDirByOther
{
public:
	TestModuleReferenceSubDirByOther();
};