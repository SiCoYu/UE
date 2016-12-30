#pragma once

#include "GObject.h"
#include "IDispatchObject"
#include <string>
#include "EventDispatchDelegate.h"
#include "GkEncode.h"

using namespace NSEncode;

class AddOnceAndCallOnceEventDispatch;
class FArchive;

/**
 * @brief 仅支持本地文件操作，仅支持同步操作
   IFileManager 是逻辑文件系统，提供上层统一接口
   class CORE_API FFileManagerGeneric
	: public IFileManager ，FFileManagerGeneric 是基本实现
   FPlatformFileManager 是平台相关的具体文件系统操作
   class SANDBOXFILE_API FSandboxPlatformFile : public IPlatformFile ，FSandboxPlatformFile 沙盒文件系统
 */
class MDataStream : GObject, IDispatchObject
{
    enum FileOpState
    {
        eNoOp = 0,      // 无操作
        eOpening = 1,   // 打开中
        eOpenSuccess = 2,   // 打开成功
        eOpenFail = 3,      // 打开失败
        eOpenClose = 4,     // 关闭
    }

	enum FileMode
	{

	};

	enum FileAccess
	{

	};

protected:
	FArchive* 
	std::string mFilePath;
    eFileOpState mFileOpState;
    bool mIsSyncMode;
    AddOnceAndCallOnceEventDispatch* mOpenedEvtDisp;   // 文件打开结束分发，主要是 WWW 是异步读取本地文件的，因此需要确保文件被打开成功

	std::string mText;
    unsigned char* mBytes;

    /**
        * @brief 仅支持同步操作，目前无视参数 isSyncMode 和 evtDisp。FileMode.CreateNew 如果文件已经存在就抛出异常，FileMode.Append 和 FileAccess.Write 要同时使用
        */
public:
	MDataStream(std::string filePath, EventDispatchDelegate openedDisp = nullptr, bool isSyncMode = true);

public:
	void seek(long offset, SeekOrigin origin);
	void addOpenedHandle(EventDispatchDelegate openedDisp = nullptr);
    void dispose()

protected:
	void syncOpenFileStream();

public:
    // 异步打开结束
	void onAsyncOpened();

protected:
	void checkAndOpen(EventDispatchDelegate openedDisp = nullptr);

public:
	bool isValid();

    // 获取总共长度
	int getLength();

protected:
	void close();

public:
	std::string readText(int offset = 0, int count = 0, GkEncode encode = NSEncode::eUTF8);
	unsigned char* readByte(int offset = 0, int count = 0);
	void writeText(std::string text, GkEncode gkEncode = NSEncode::eUTF8);

	void writeByte(unsigned char* bytes, int offset = 0, int count = 0);
	void writeLine(std::string text, GkEncode gkEncode = NSEncode::eUTF8);
};