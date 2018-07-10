#pragma once

#include "GObject.h"
#include "IDispatchObject.h"
#include <string>
#include "EventDispatchDelegate.h"
#include "MEncode.h"
#include "FileOpState.h"
#include "MFileAccess.h"
#include "MFileMode.h"
#include "MSeekOrigin.h"
#include "PlatformDefine.h"

class FArchive;

MY_BEGIN_NAMESPACE(MyNS)

class AddOnceAndCallOnceEventDispatch;

/**
 * @brief 仅支持本地文件操作，仅支持同步操作
   IFileManager 是逻辑文件系统，提供上层统一接口
   class CORE_API FFileManagerGeneric
	: public IFileManager ，FFileManagerGeneric 是基本实现
   FPlatformFileManager 是平台相关的具体文件系统操作
   class SANDBOXFILE_API FSandboxPlatformFile : public IPlatformFile ，FSandboxPlatformFile 沙盒文件系统
 */
class MDataStream : public GObject/*, public IDispatchObject*/
{
protected:
	FArchive* mFileStream;
	std::string mFilePath;
	MFileMode mMode;
	MFileAccess mAccess;
    FileOpState mFileOpState;
    bool mIsSyncMode;
    AddOnceAndCallOnceEventDispatch* mOpenedEvtDisp;   // 文件打开结束分发

	std::string mText;
    unsigned char* mBytes;
	TArray<uint8> mArrayBuffer;

    /**
     * @brief 仅支持同步操作，目前无视参数 isSyncMode 和 evtDisp。FileMode.CreateNew 如果文件已经存在就抛出异常，FileMode.Append 和 FileAccess.Write 要同时使用
     */
public:
	MDataStream(std::string filePath, EventDispatchDelegate openedDisp = EventDispatchDelegate(), MFileMode mode = eOpen, MFileAccess access = eRead, bool isSyncMode = true);

public:
	void seek(long offset, MSeekOrigin origin);
	void addOpenedHandle(EventDispatchDelegate openedDisp = EventDispatchDelegate());
	void dispose();

protected:
	void syncOpenFileStream();

public:
    // 异步打开结束
	void onAsyncOpened();

protected:
	void checkAndOpen(EventDispatchDelegate openedDisp = EventDispatchDelegate());

public:
	bool isValid();

    // 获取总共长度
	int getLength();

protected:
	void close();

public:
	std::string readText(int offset = 0, int count = 0, MEncode encode = MEncode::eUTF8);
	unsigned char* readByte(int offset = 0, int count = 0);
	void writeText(std::string text, MEncode encode = MEncode::eUTF8);

	void writeByte(unsigned char* bytes, int offset = 0, int count = 0);
	void writeLine(std::string text, MEncode encode = MEncode::eUTF8);
};

MY_END_NAMESPACE