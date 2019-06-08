using System;
using System.IO;
using System.Text;

namespace SDK.Lib
{
    /**
     * @brief 仅支持本地文件操作，仅支持同步操作
     */
    public class MFileStream : GObject, IDispatchObject
    {
        public FileStream mFileStream;
        
        protected string mFilePath;
        protected MFileMode mMode;
        protected MFileAccess mAccess;
        protected MFileOpState mFileOpState;

        protected string mText;
        protected byte[] mBytes;
        protected AddOnceAndCallOnceEventDispatch mOpenedEventDispatch;

        /**
         * @brief 仅支持同步操作，目前无视参数 isSyncMode 和 evtDisp。FileMode.CreateNew 如果文件已经存在就抛出异常，FileMode.Append 和 FileAccess.Write 要同时使用
         */
        public MFileStream(string filePath, MEventDispatchAction<IDispatchObject> openedHandle = null, MFileMode mode = MFileMode.eOpen, MFileAccess access = MFileAccess.eRead)
        {
            this.mTypeId = "MFileStream";

            this.mFilePath = filePath;
            this.mMode = mode;
            this.mAccess = access;
            this.mFileOpState = MFileOpState.eNoOp;

            //this.checkAndOpen(openedHandle);
        }

        public void open()
        {
            this.checkAndOpen(null);
        }

        public void seek(long offset, MSeekOrigin origin)
        {
            if(this.mFileOpState == MFileOpState.eOpenSuccess)
            {
                this.mFileStream.Seek(offset, (SeekOrigin)origin);
            }
        }

        public void addOpenedHandle(MEventDispatchAction<IDispatchObject> openedDisp = null)
        {
            if (this.mOpenedEventDispatch == null)
            {
                this.mOpenedEventDispatch = new AddOnceAndCallOnceEventDispatch();
            }

            this.mOpenedEventDispatch.addEventHandle(null, openedDisp);
        }

        override public void dispose()
        {
            this.close();
        }

        protected void syncOpenFileStream()
        {
            if (this.mFileOpState == MFileOpState.eNoOp)
            {
                this.mFileOpState = MFileOpState.eOpening;

                try
                {
                    this.mFileStream = new FileStream(this.mFilePath, (FileMode)this.mMode, (FileAccess)this.mAccess);
                    this.mFileOpState = MFileOpState.eOpenSuccess;
                }
                catch(Exception err)
                {
                    this.mFileOpState = MFileOpState.eOpenFail;

                    Ctx.msInstance.mLogSys.log(string.Format("MFileStream::syncOpenFileStream, error, Exception = {0}", err.ToString()), LogTypeId.eLogLocalFile);
                }

                this.onAsyncOpened();
            }
        }

        // 异步打开结束
        public void onAsyncOpened()
        {
            if (this.mOpenedEventDispatch != null)
            {
                this.mOpenedEventDispatch.dispatchEvent(this);
            }
        }

        protected void checkAndOpen(MEventDispatchAction<IDispatchObject> openedHandle = null)
        {
            if (openedHandle != null)
            {
                this.addOpenedHandle(openedHandle);
            }

            if (this.mFileOpState == MFileOpState.eNoOp)
            {
                this.syncOpenFileStream();
            }
        }

        public bool isValid()
        {
            return this.mFileOpState == MFileOpState.eOpenSuccess;
        }

        // 获取总共长度
        public int getLength()
        {
            int len = 0;

            if (this.mFileOpState == MFileOpState.eOpenSuccess)
            {
                if (this.mFileStream != null)
                {
                    len = (int)this.mFileStream.Length;
                }
                /*
                if (mFileStream != null && mFileStream.CanSeek)
                {
                    try
                    {
                        len = (int)mFileStream.Seek(0, SeekOrigin.End);     // 移动到文件结束，返回长度
                        len = (int)mFileStream.Position;                    // Position 移动到 Seek 位置
                    }
                    catch(Exception err)
                    {
                    }
                }
                */
            }

            return len;
        }

        protected void close()
        {
            if (this.mFileOpState == MFileOpState.eOpenSuccess)
            {
                if (this.mFileStream != null)
                {
                    this.mFileStream.Close();
                    this.mFileStream.Dispose();
                    this.mFileStream = null;
                }

                this.mFileOpState = MFileOpState.eOpenClose;
                this.mFileOpState = MFileOpState.eNoOp;
            }
        }

        public string readText(int offset = 0, int count = 0, Encoding encode = null)
        {
            this.checkAndOpen();

            string retStr = "";
            byte[] bytes = null;

            if (encode == null)
            {
                encode = Encoding.UTF8;
            }

            if (count == 0)
            {
                count = this.getLength();
            }

            if (this.mFileOpState == MFileOpState.eOpenSuccess)
            {
                if (this.mFileStream.CanRead)
                {
                    try
                    {
                        bytes = new byte[count];
                        this.mFileStream.Read(bytes, 0, count);

                        retStr = encode.GetString(bytes);
                    }
                    catch (Exception err)
                    {
                        Ctx.msInstance.mLogSys.log(string.Format("MFileStream::syncOpenFileStream, error, Exception = {0}", err.ToString()), LogTypeId.eLogLocalFile);
                    }
                }
            }

            return retStr;
        }

        public byte[] readByte(int offset = 0, int count = 0)
        {
            this.checkAndOpen();

            if (count == 0)
            {
                count = this.getLength();
            }

            byte[] bytes = null;

            if (this.mFileStream.CanRead)
            {
                try
                {
                    bytes = new byte[count];
                    this.mFileStream.Read(bytes, 0, count);
                }
                catch (Exception err)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("MFileStream::readByte, error, Exception = {0}", err.ToString()), LogTypeId.eLogLocalFile);
                }
            }

            return bytes;
        }

        public void writeText(string text, MEncode srcEncode = MEncode.eUTF8)
        {
            Encoding encode = UtilSysLibWrap.convOneEncode2AnotherEncode(srcEncode);

            this.checkAndOpen();

            if (this.mFileStream.CanWrite)
            {
                //if (encode == null)
                //{
                //    encode = MEncode.UTF8;
                //}

                byte[] bytes = encode.GetBytes(text);

                if (bytes != null)
                {
                    try
                    {
                        this.mFileStream.Write(bytes, 0, bytes.Length);
                    }
                    catch (Exception err)
                    {
                        Ctx.msInstance.mLogSys.log(string.Format("MFileStream::writeText, error, Exception = {0}", err.ToString()), LogTypeId.eLogLocalFile);
                    }
                }
            }
        }

        public void writeByte(byte[] bytes, int offset = 0, int count = 0)
        {
            this.checkAndOpen();

            if (this.mFileStream.CanWrite)
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
                            this.mFileStream.Write(bytes, offset, count);
                        }
                        catch (Exception err)
                        {
                            Ctx.msInstance.mLogSys.log(string.Format("MFileStream::writeByte, error, Exception = {0}", err.ToString()), LogTypeId.eLogLocalFile);
                        }
                    }
                }
            }
        }

        public void writeLine(string text, MEncode gkEncode = MEncode.eUTF8)
        {
            text = text + UtilSysLibWrap.CR_LF;
            this.writeText(text, gkEncode);
        }
    }
}