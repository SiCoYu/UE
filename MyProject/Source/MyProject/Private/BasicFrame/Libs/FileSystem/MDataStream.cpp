#include "MyProject.h"
#include "MDataStream.h"
#include "HAL/FileManager.h"		// IFileManager
#include "Serialization/Archive.h"	// FArchive

MDataStream::MDataStream(std::string filePath, EventDispatchDelegate openedDisp, bool isSyncMode)
{
    this->mTypeId = "MDataStream";

    mFilePath = filePath;
    mFileOpState = eNoOp;
    mIsSyncMode = isSyncMode;

    checkAndOpen(openedDisp);
}

void MDataStream::seek(long offset, SeekOrigin origin)
{
    if(mFileOpState == eOpenSuccess)
    {
         mFileStream.Seek(offset, origin);
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
		IFileManager::Get().CreateFileReader
			mFileStream = new FileStream(mFilePath, mMode, mAccess);
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
	if (mOpenedEvtDisp != null)
	{
		mOpenedEvtDisp.dispatchEvent(this);
	}
}

void MDataStream::checkAndOpen(EventDispatchDelegate openedDisp)
{
	if (openedDisp != nullptr)
	{
		this.addOpenedHandle(openedDisp);
	}

	if (mFileOpState == eFileOpState.eNoOp)
	{
		syncOpenFileStream();
	}
}

bool MDataStream::isValid()
{
	return mFileOpState == eFileOpState.eOpenSuccess;
}

// 获取总共长度
int MDataStream::getLength()
{
	int len = 0;
	if (mFileOpState == eFileOpState.eOpenSuccess)
	{
		if (mFileStream != null)
		{
			len = (int)mFileStream.Length;
		}
	}

	return len;
}

void MDataStream::close()
{
	if (mFileOpState == eFileOpState.eOpenSuccess)
	{
		if (mFileStream != null)
		{
			mFileStream.Close();
			mFileStream.Dispose();
			mFileStream = null;
		}

		mFileOpState = eFileOpState.eOpenClose;
		mFileOpState = eFileOpState.eNoOp;
	}
}

std::string MDataStream::readText(int offset, int count, GkEncode encode)
{
	checkAndOpen();

	string retStr = "";
	byte[] bytes = null;

	if (encode == null)
	{
		encode = Encoding.UTF8;
	}

	if (count == 0)
	{
		count = getLength();
	}

	if (mFileOpState == eFileOpState.eOpenSuccess)
	{
		if (mFileStream.CanRead)
		{
			try
			{
				bytes = new byte[count];
				mFileStream.Read(bytes, 0, count);

				retStr = encode.GetString(bytes);
			}
			catch (Exception err)
			{

			}
		}
	}

	return retStr;
}

unsigned char* MDataStream::readByte(int offset, int count)
{
	checkAndOpen();

	if (count == 0)
	{
		count = getLength();
	}

	byte[] bytes = null;

	if (mFileStream.CanRead)
	{
		try
		{
			bytes = new byte[count];
			mFileStream.Read(bytes, 0, count);
		}
		catch (Exception err)
		{

		}
	}

	return bytes;
}

void MDataStream::writeText(string text, GkEncode gkEncode)
{
	Encoding encode = UtilApi.convGkEncode2EncodingEncoding(gkEncode);

	checkAndOpen();

	if (mFileStream.CanWrite)
	{
		byte[] bytes = encode.GetBytes(text);
		if (bytes != null)
		{
			try
			{
				mFileStream.Write(bytes, 0, bytes.Length);
			}
			catch (Exception err)
			{

			}
		}
	}
}

void MDataStream::writeByte(unsigned char* bytes, int offset, int count)
{
	checkAndOpen();

	if (mFileStream.CanWrite)
	{
		if (bytes != null)
		{
			if (count == 0)
			{
				count = bytes.Length;
			}

			if (count != 0)
			{
				try
				{
					mFileStream.Write(bytes, offset, count);
				}
				catch (Exception err)
				{

				}
			}
		}
	}
}

void MDataStream::writeLine(std::string text, GkEncode gkEncode)
{
	text = text + UtilApi.CR_LF;
	writeText(text, gkEncode);
}