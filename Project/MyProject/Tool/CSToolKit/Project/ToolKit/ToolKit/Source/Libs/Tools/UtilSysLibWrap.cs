using System;

namespace SDK.Lib
{
    public class UtilSysLibWrap
    {
        public const string TRUE = "true";
        public const string FALSE = "true";
        public const string CR_LF = "\n";

        // 剔除字符串末尾的空格
        public static void trimEndSpace(ref string str)
        {
            str.TrimEnd('\0');
        }

        // 判断两个 GameObject 地址是否相等
        public static bool isAddressEqual(System.Object a, System.Object b)
        {
            return object.ReferenceEquals(a, b);
        }

        // 判断两个函数是否相等，不能使用 isAddressEqual 判断函数是否相等
        public static bool isDelegateEqual(ref MEventDispatchAction<IDispatchObject> a, ref MEventDispatchAction<IDispatchObject> b)
        {
            return a == b;
        }

        protected static long msCurTime;
        protected static System.TimeSpan msTimeSpan;

        // 返回 UTC 秒
        public static long getUTCSec()
        {
            UtilSysLibWrap.msCurTime = System.DateTime.Now.Ticks;
            UtilSysLibWrap.msTimeSpan = new System.TimeSpan(msCurTime);

            if (MacroDef.ENABLE_LOG)
            {
                if (null != Ctx.msInstance && null != Ctx.msInstance.mLogSys)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("UtilEngineWrap::msCurTime, msCurTime = {0}, msTimeSpan = {1}, totalSec = {2}", UtilSysLibWrap.msCurTime, UtilSysLibWrap.msTimeSpan, UtilSysLibWrap.msTimeSpan.TotalSeconds), LogTypeId.eLogMergeBug);
                }
            }

            return (long)(UtilSysLibWrap.msTimeSpan.TotalSeconds);
        }

        // 返回 UTC 秒
        public static double getFloatUTCSec()
        {
            UtilSysLibWrap.msCurTime = System.DateTime.Now.Ticks;
            UtilSysLibWrap.msTimeSpan = new System.TimeSpan(msCurTime);


            if (MacroDef.ENABLE_LOG)
            {
                if (null != Ctx.msInstance && null != Ctx.msInstance.mLogSys)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("UtilEngineWrap::msCurTime, msCurTime = {0}, msTimeSpan = {1}, totalSec = {2}", UtilSysLibWrap.msCurTime, UtilSysLibWrap.msTimeSpan, UtilSysLibWrap.msTimeSpan.TotalSeconds), LogTypeId.eLogMergeBug);
                }
            }

            return UtilSysLibWrap.msTimeSpan.TotalSeconds;
        }

        // 返回 UTC 毫秒
        public static double getFloatUTCMilliseconds()
        {
            UtilSysLibWrap.msCurTime = System.DateTime.Now.Ticks;
            UtilSysLibWrap.msTimeSpan = new System.TimeSpan(msCurTime);

            return UtilSysLibWrap.msTimeSpan.TotalMilliseconds;
        }

        // 获取当前时间的文本可读形式
        public static string getUTCFormatText()
        {
            return System.DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss");
        }

        // 获取当前时间的文本可读形式
        public static string getRandomVersion()
        {
            return System.DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss");
        }

        // 欧拉角增加
        static public float incEulerAngles(float degree, float delta)
        {
            return (degree + delta) % 360;
        }

        static public float decEulerAngles(float degree, float delta)
        {
            return (degree - delta) % 360;
        }

        // 转换二维索引到一维索引
        static public uint convTIdx2OIdx(short x, short y)
        {
            uint key = 0;
            key = (uint)(((ushort)y << 16) | (ushort)x);
            return key;
        }
        // 注意最大不能超过 65536
        static public uint packIndex(long x, long y)
        {
            short xs16 = (short)(x);
            short ys16 = (short)(y);

            ushort x16 = (ushort)(xs16);
            ushort y16 = (ushort)(ys16);

            uint key = 0;
            key = (uint)((x16 << 16) | y16);

            return key;
        }

        // 注意最大不能超过 65536
        static public void unpackIndex(uint key, ref long x, ref long y)
        {
            ushort y16 = (ushort)(key & 0xFFFF);
            ushort x16 = (ushort)((key >> 16) & 0xFFFF);

            x = (short)(x16);
            y = (short)(y16);
        }

        // 转换资源目录到精灵名字
        static public string convFullPath2SpriteName(string fullPath)
        {
            string spriteName = "";
            int lastSlashIndex = -1;
            int dotIndex = -1;

            lastSlashIndex = UtilStr.LastIndexOf(ref fullPath, '/');

            if (-1 == lastSlashIndex)
            {
                lastSlashIndex = UtilStr.LastIndexOf(ref fullPath, '\\');
            }

            dotIndex = UtilStr.LastIndexOf(ref fullPath, '.');

            if (-1 == lastSlashIndex)
            {
                if (-1 == dotIndex)
                {
                    spriteName = fullPath;
                }
                else
                {
                    spriteName = fullPath.Substring(0, dotIndex);
                }
            }
            else
            {
                if (-1 == dotIndex)
                {
                    spriteName = fullPath.Substring(lastSlashIndex + 1, fullPath.Length - lastSlashIndex);
                }
                else
                {
                    spriteName = fullPath.Substring(lastSlashIndex + 1, dotIndex - (lastSlashIndex + 1));
                }
            }

            return spriteName;
        }

        /**
         * @ref http://www.cnblogs.com/xuan52rock/p/5316370.html
         */
        public static int getYear()
        {
            int year = DateTime.Now.Year;
            return year;
        }

        public static int getMonth()
        {
            int month = DateTime.Now.Month;
            return month;
        }

        // 获取格式化时间
        static public string getFormatTime()
        {
            //return "[" + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss fff") + "] ";
            return "[" + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + "] ";
        }

        static public System.Text.Encoding convOneEncode2AnotherEncode(MEncode srcEncode)
        {
            System.Text.Encoding retEncode = System.Text.Encoding.UTF8;

            if (MEncode.eUTF8 == srcEncode)
            {
                // retEncode = System.Text.Encoding.GetEncoding("utf-8");
                retEncode = System.Text.Encoding.UTF8;
            }
            else if (MEncode.eGB2312 == srcEncode)
            {
                //retEncode = System.Text.Encoding.UTF8;
                //retEncode = System.Text.Encoding.Default;
                retEncode = System.Text.Encoding.GetEncoding("gb2312");
            }
            else if (MEncode.eUnicode == srcEncode)
            {
                retEncode = System.Text.Encoding.Unicode;
            }
            else if (MEncode.eDefault == srcEncode)
            {
                retEncode = System.Text.Encoding.Default;
            }

            return retEncode;
        }

        /**
         * @url https://blog.csdn.net/duling509/article/details/7169485
         * @url https://www.cnblogs.com/gavin-num1/p/5133435.html
         * 在JavaScript中推荐的做法是用encodeURI对URI的网址部分编码，用encodeURIComponent对URI中传递的参数进行编码。
　　     * 在C#中推荐的做法是用Uri.EscapeUriString对URI的网址部分编码，用Uri.EscapeDataString对URI中传递的参数进行编码。
         */
        public static string encodeURI(string url)
        {
            string ret = "";
            //return HttpUtility.UrlEncode(url);
            ret = Uri.EscapeUriString(url);
            return ret;
        }

        public static string encodeURIParam(string param)
        {
            string ret = "";
            //return HttpUtility.UrlEncode(param);
            ret = Uri.EscapeDataString(param);
            return ret;
        }

        public static string decodeURI(string url)
        {
            string ret = "";
            //ret = System.Web.UrlDecode(url);
            ret = Uri.UnescapeDataString(url);
            return ret;
        }

        public static string decodeURIParam(string param)
        {
            string ret = "";
            //ret = System.Web.UrlDecode(param);
            ret = Uri.UnescapeDataString(param);
            return ret;
        }

		public static void writeConsoleFromProcess(System.Diagnostics.Process process)
		{
			System.Console.WriteLine("StandardOutput:");
			System.Console.WriteLine(process.StandardOutput.ReadToEnd());
			System.Console.WriteLine("StandardError:");
			System.Console.WriteLine(process.StandardError.ReadToEnd());
		}
    }
}