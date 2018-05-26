#include "MyProject.h"
#include "MDataStream.h"
#include "HAL/FileManager.h"		// IFileManager
#include "Serialization/Archive.h"	// FArchive
#include "UtilStr.h"
#include "Misc/FileHelper.h"		// FFileHelper
#include "AddOnceAndCallOnceEventDispatch.h"

MDataStream::MDataStream(std::string filePath, EventDispatchDelegate openedDisp, MFileMode mode, MFileAccess access, bool isSyncMode)
{
	this->mFilePath = filePath;
	this->mMode = mode;
	this->mAccess = access;
	this->mFileOpState = eNoOp;
	this->mIsSyncMode = isSyncMode;

	this->checkAndOpen(openedDisp);
}

void MDataStream::seek(long offset, MSeekOrigin origin)
{
    if(this->mFileOpState == eOpenSuccess)
    {
		this->mFileStream->Seek(offset);
    }
}

void MDataStream::addOpenedHandle(EventDispatchDelegate openedDisp)
{
    if (this->mOpenedEvtDisp == nullptr)
    {
		this->mOpenedEvtDisp = new AddOnceAndCallOnceEventDispatch();
    }

	this->mOpenedEvtDisp->addEventHandle(openedDisp);
}

void MDataStream::dispose()
{
	this->close();
}

void MDataStream::syncOpenFileStream()
{
	if (this->mFileOpState == eNoOp)
	{
		this->mFileOpState = eOpening;
		//try
		//{
		FString path = UtilStr::ConvStdStr2FString(this->mFilePath);

		if (eRead == this->mAccess)
		{
			this->mFileStream = IFileManager::Get().CreateFileReader(*path);
		}
		else
		{
			this->mFileStream = IFileManager::Get().CreateFileWriter(*path);
		}

		this->mFileOpState = eOpenSuccess;
		//}
		//catch (Exception exp)
		//{
		//	mFileOpState = eOpenFail;
		//}

		onAsyncOpened();
	}
}

// 异步打开结束
void MDataStream::onAsyncOpened()
{
	if (this->mOpenedEvtDisp != nullptr)
	{
		this->mOpenedEvtDisp->dispatchEvent(this);
	}
}

void MDataStream::checkAndOpen(EventDispatchDelegate openedDisp)
{
	if (openedDisp != nullptr)
	{
		this->addOpenedHandle(openedDisp);
	}

	if (this->mFileOpState == eNoOp)
	{
		this->syncOpenFileStream();
	}
}

bool MDataStream::isValid()
{
	return mFileOpState == eOpenSuccess;
}

// 获取总共长度
int MDataStream::getLength()
{
	int len = 0;
	if (this->mFileOpState == eOpenSuccess)
	{
		if (this->mFileStream != nullptr)
		{
			len = (int)this->mFileStream->TotalSize();
		}
	}

	return len;
}

void MDataStream::close()
{
	if (this->mFileOpState == eOpenSuccess)
	{
		bool Success = false;

		if (this->mFileStream != nullptr)
		{
			Success = this->mFileStream->Close();
			MY_DELETE this->mFileStream;
			this->mFileStream = nullptr;
		}

		if (Success)
		{
			this->mFileOpState = eOpenClose;
			this->mFileOpState = eNoOp;
		}
		else
		{
			this->mFileOpState = eOpenFail;
		}
	}
}

std::string MDataStream::readText(int offset, int count, GkEncode encode)
{
	std::string retStr = "";
	FString fStr;

	if (FFileHelper::LoadFileToString(fStr, UtilStr::convStdStr2TCHAR(mFilePath)))
	{
		retStr = UtilStr::ConvFString2StdStr(fStr);
	}

	return retStr;
}

unsigned char* MDataStream::readByte(int offset, int count)
{
	if (count == 0)
	{
		count = getLength();
	}

	unsigned char* bytes = nullptr;

	if (FFileHelper::LoadFileToArray(mArrayBuffer, UtilStr::convStdStr2TCHAR(mFilePath)))
	{
		bytes = mArrayBuffer.GetData();
	}

	return bytes;
}

void MDataStream::writeText(std::string text, GkEncode gkEncode)
{
	//Encoding encode = UtilSysLibWrap.convGkEncode2EncodingEncoding(gkEncode);
	//FFileHelper::EEncodingOptions::Type encode = FFileHelper::EEncodingOptions::ForceUTF8;
	// UE 4.18
	FFileHelper::EEncodingOptions encode = FFileHelper::EEncodingOptions::ForceUTF8;
	checkAndOpen();
	FFileHelper::SaveStringToFile(UtilStr::ConvStdStr2FString(text), UtilStr::convStdStr2TCHAR(mFilePath), encode);
}

void MDataStream::writeByte(unsigned char* bytes, int offset, int count)
{
	TArrayView<const uint8> Array = MakeArrayView(bytes + offset, count);
	FFileHelper::SaveArrayToFile(Array, UtilStr::convStdStr2TCHAR(mFilePath));
}

void MDataStream::writeLine(std::string text, GkEncode gkEncode)
{
	//text = text + UtilSysLibWrap.CR_LF;
	this->writeText(text, gkEncode);
}