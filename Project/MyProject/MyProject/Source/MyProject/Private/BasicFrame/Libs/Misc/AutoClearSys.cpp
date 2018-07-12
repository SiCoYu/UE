#include <MyProject.h>
#include <AutoClearSys.h>

MY_BEGIN_NAMESPACE(MyNS)

AutoClearSys::AutoClearSys()
{
	//this.mInstallFlagFileFullPath = string.Format("{0}/{1}", MFileSys.msDataStreamPersistentDataPath, "InstallFlagFile.txt");
}

void AutoClearSys::init()
{

}

void AutoClearSys::dispose()
{

}

// 是否是安装后第一次启动
bool AutoClearSys::isFirstStartUpAfterInstalled()
{
	bool ret = false;

	//if (UtilFileIO.existFile(this.mInstallFlagFileFullPath))
	//{
	//	this.mDestDataStream = new MDataStream(this.mInstallFlagFileFullPath);
	//	this.mDestDataStream.open();
	//	string version = this.mDestDataStream.readText();
	//	this.mDestDataStream.dispose();
	//	this.mDestDataStream = null;

	//	if (MacroDef.ENABLE_LOG)
	//	{
	//		Ctx.msInstance.mLogSys.log(string.Format("AutoClearSys::isFirstStartUpAfterInstalled, existFile,  version = {0}, installversion = {1}", version, Ctx.msInstance.mVersionSys.mLocalVer.getInstallVersionString()), LogTypeId.eLogAutoClear);
	//	}

	//	// 第一次安装后启动
	//	if (version != Ctx.msInstance.mVersionSys.mLocalVer.getInstallVersionString())
	//	{
	//		ret = true;
	//	}
	//}
	//else
	//{
	//	if (MacroDef.ENABLE_LOG)
	//	{
	//		Ctx.msInstance.mLogSys.log("AutoClearSys::isFirstStartUpAfterInstalled, not exist", LogTypeId.eLogAutoClear);
	//	}

	//	ret = true;
	//}

	//if (MacroDef.ENABLE_LOG)
	//{
	//	Ctx.msInstance.mLogSys.log(string.Format("AutoClearSys::isFirstStartUpAfterInstalled, ret = {0}", ret.ToString()), LogTypeId.eLogAutoClear);
	//}

	return ret;
}

// 清理保存的文件
void AutoClearSys::clearFiles()
{
	//if (MacroDef.ENABLE_LOG)
	//{
	//	Ctx.msInstance.mLogSys.log(string.Format("AutoClearSys::clearFiles, path = {0}", MFileSys.msDataStreamPersistentDataPath), LogTypeId.eLogAutoClear);
	//}

	//UtilFileIO.clearDirectory(MFileSys.msDataStreamPersistentDataPath);
}

// 写入安装标志
void AutoClearSys::writeInstallFlag()
{
	//if (UtilFileIO.existFile(this.mInstallFlagFileFullPath))
	//{
	//	if (MacroDef.ENABLE_LOG)
	//	{
	//		Ctx.msInstance.mLogSys.log(string.Format("AutoClearSys::writeInstallFlag, exist file, path = {0}", this.mInstallFlagFileFullPath), LogTypeId.eLogAutoClear);
	//	}

	//	UtilFileIO.deleteFile(this.mInstallFlagFileFullPath);
	//}
	//else
	//{
	//	if (MacroDef.ENABLE_LOG)
	//	{
	//		Ctx.msInstance.mLogSys.log(string.Format("AutoClearSys::writeInstallFlag, not exist , path = {0}", this.mInstallFlagFileFullPath), LogTypeId.eLogAutoClear);
	//	}
	//}

	//this.mDestDataStream = new MDataStream(this.mInstallFlagFileFullPath, null, MFileMode.eCreateNew, MFileAccess.eWrite);
	//this.mDestDataStream.open();

	//this.mDestDataStream.writeText(Ctx.msInstance.mVersionSys.mLocalVer.getInstallVersionString());

	//this.mDestDataStream.dispose();
	//this.mDestDataStream = null;
}

void AutoClearSys::checkAutoClear()
{
	//if (this.isFirstStartUpAfterInstalled())
	//{
	//	this.clearFiles();
	//	this.writeInstallFlag();
	//}
}

MY_END_NAMESPACE