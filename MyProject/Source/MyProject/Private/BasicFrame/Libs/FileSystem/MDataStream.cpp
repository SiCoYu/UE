#include "MyProject.h"
#include "MDataStream.h"
#include "HAL/FileManager.h"		// IFileManager
#include "Serialization/Archive.h"	// FArchive
#include "UtilStr.h"
#include "Misc/FileHelper.h"		// FFileHelper
#include "AddOnceAndCallOnceEventDispatch.h"

MDataStream::MDataStream(std::string filePath, EventDispatchDelegate openedDisp, MFileMode mode, MFileAccess access, bool isSyncMode)
{
    this->mTypeId = "MDataStream";

    mFilePath = filePath;
	mMode = mode;
	mAccess = access;
    mFileOpState = eNoOp;
    mIsSyncMode = isSyncMode;

    checkAndOpen(openedDisp);
}

void MDataStream::seek(long offset, MSeekOrigin origin)
{
    if(mFileOpState == eOpenSuccess)
    {
         mFileStream->Seek(offset);
    }
}

void MDataStream::addOpenedHandle(EventDispatchDelegate openedDisp)
{
    if (mOpenedEvtDisp == nullptr)
    {
        mOpenedEvtDisp = new AddOnceAndCallOnceEventDispatch();
    }

    mOpenedEvtDisp->addEventHandle(openedDisp);
}

void MDataStream::dispose()
{
    close();
}

void MDataStream::syncOpenFileStream()
{
	if (mFileOpState == eNoOp)
	{
		mFileOpState = eOpening;
		//try
		//{
		FString path = UtilStr::ConvStdStr2FString(mFilePath);

		if (MFileAccess.eRead == mAccess)
		{
			mFileStream = IFileManager::Get().CreateFileReader(*path);
		}
		else
		{
			mFileStream = IFileManager::Get().CreateFileWriter(*path);
		}

		mFileOpState = eOpenSuccess;
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
	if (mOpenedEvtDisp != nullptr)
	{
		mOpenedEvtDisp->dispatchEvent(this);
	}
}

void MDataStream::checkAndOpen(EventDispatchDelegate openedDisp)
{
	if (openedDisp != nullptr)
	{
		this->addOpenedHandle(openedDisp);
	}

	if (mFileOpState == eNoOp)
	{
		syncOpenFileStream();
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
	if (mFileOpState == eOpenSuccess)
	{
		if (mFileStream != nullptr)
		{
			len = (int)mFileStream->TotalSize();
		}
	}

	return len;
}

void MDataStream::close()
{
	if (mFileOpState == eOpenSuccess)
	{
		bool Success = false;
		if (mFileStream != nullptr)
		{
			Success = mFileStream->Close();
			delete mFileStream;
			mFileStream = nullptr;
		}

		if (Success)
		{
			mFileOpState = eOpenClose;
			mFileOpState = eNoOp;
		}
		else
		{
			mFileOpState = eOpenFail;
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
	//Encoding encode = UtilApi.convGkEncode2EncodingEncoding(gkEncode);
	EEncodingOptions::Type encode = EEncodingOptions::ForceUTF8;
	checkAndOpen();
	FFileHelper::SaveStringToFile(UtilStr::ConvStdStr2FString(text), UtilStr::convStdStr2TCHAR(mFilePath), encode);
}

void MDataStream::writeByte(unsigned char* bytes, int offset, int count)
{
	TArrayView<const uint8> Array;
	FFileHelper::SaveArrayToFile(Array, UtilStr::convStdStr2TCHAR(mFilePath));
}

void MDataStream::writeLine(std::string text, GkEncode gkEncode)
{
	//text = text + UtilApi.CR_LF;
	writeText(text, gkEncode);
}