using System;

namespace SDK.Lib
{
    public class UtilLogic
    {
        public static string getPathNoVer(string path)
        {
            if (path.IndexOf('?') != -1)
            {
                return path.Substring(0, path.IndexOf('?'));
            }

            return path;
        }

        // 判断一个 unicode 字符是不是汉字
        public static bool IsChineseLetter(string input, int index)
        {
            int code = 0;
            int chfrom = System.Convert.ToInt32("4e00", 16); //范围（0x4e00～0x9fff）转换成int（chfrom～chend）
            int chend = System.Convert.ToInt32("9fff", 16);

            if (input != "")
            {
                code = System.Char.ConvertToUtf32(input, index); //获得字符串input中指定索引index处字符unicode编码

                if (code >= chfrom && code <= chend)
                {
                    return true; //当code在中文范围内返回true
                }
                else
                {
                    return false; //当code不在中文范围内返回false
                }
            }

            return false;
        }

        public static bool IsIncludeChinese(string input)
        {
            int index = 0;

            for (index = 0; index < input.Length; ++index)
            {
                if (IsChineseLetter(input, index))
                {
                    return true;
                }
            }

            return false;
        }

        // 判断 unicode 字符个数，只判断字母和中文吗，中文算 2 个字节
        public static int CalcCharCount(string str)
        {
            int charCount = 0;
            int index = 0;

            for (index = 0; index < str.Length; ++index)
            {
                if (IsChineseLetter(str, index))
                {
                    charCount += 2;
                }
                else
                {
                    charCount += 1;
                }
            }

            return charCount;
        }

        public static string getPakPathAndExt(string path, string extName)
        {
            return string.Format("{0}.{1}", path, extName);
        }

        public static string convScenePath2LevelName(string path)
        {
            int slashIdx = path.LastIndexOf("/");
            int dotIdx = path.IndexOf(".");
            string retLevelName = "";
            if (slashIdx != -1)
            {
                if (dotIdx != -1)
                {
                    retLevelName = path.Substring(slashIdx + 1, dotIdx - slashIdx - 1);
                }
                else
                {
                    retLevelName = path.Substring(slashIdx + 1);
                }
            }
            else
            {
                retLevelName = path;
            }

            return retLevelName;
        }

        // 通过下划线获取最后的数字，例如 asdf_23 获取 23
        public static int findIdxByUnderline(string name)
        {
            int index = name.LastIndexOf("_");
            int ret = 0;

            if (-1 != index)
            {
                bool bSuccess = Int32.TryParse(name.Substring(index + 1, name.Length - 1 - index), out ret);
            }

            return ret;
        }

        public static string getImageByPinZhi(int pinzhi)
        {
            return string.Format("pinzhi_kapai_{0}", pinzhi);
        }

        // 从数字获取 5 位字符串
        public static string get5StrFromDigit(int digit)
        {
            string ret = "";
            if (digit < 10)
            {
                ret = string.Format("{0}{1}", "0000", digit.ToString());
            }
            else if (digit < 100)
            {
                ret = string.Format("{0}{1}", "000", digit.ToString());
            }

            return ret;
        }

        // 格式化时间，显示格式为 00年00天00时00分00秒
        static public string formatTime(int second)
        {
            string ret = "";

            int left = 0;
            int year = second / (356 * 24 * 60 * 60);
            left = second % (356 * 24 * 60 * 60);
            int day = left / (24 * 60 * 60);
            left = left % (24 * 60 * 60);
            int hour = left / (60 * 60);
            left = left % (60 * 60);
            int min = left / 60;
            left = left % 60;
            int sec = left;

            if(year != 0)
            {
                ret = string.Format("{0}{1}年", ret, year);
            }
            if (day != 0)
            {
                ret = string.Format("{0}{1}天", ret, day);
            }
            if (hour != 0)
            {
                ret = string.Format("{0}{1}时", ret, hour);
            }
            if (min != 0)
            {
                ret = string.Format("{0}{1}分", ret, min);
            }
            if (sec != 0)
            {
                ret = string.Format("{0}{1}秒", ret, sec);
            }

            return ret;
        }

        public static float getSquare(float num)
        {
            return num * num;
        }
        
        static public void convShadowFullPath2AtlasPathAndName(string fullPath, ref string atlasPath, ref string spriteName)
        {
            atlasPath = "Atlas/Planes/Shadow.asset";
            spriteName = UtilFileIO.getFileNameNoExt(fullPath);
        }

        // 0 + 1 开始是皮肤  1000 + 1 开始是  2000 + 1 开始是会员
        static public int convTotal2ShopTopPageIndex(uint totalIndex)
        {
            uint ret = 0;
            ret = totalIndex / 1000;
            return (int)ret;
        }

        static public int convTotal2ShopSubPageIndex(uint totalIndex)
        {
            uint ret = 0;
            ret = totalIndex % 1000;
            return (int)ret;
        }

        static public string getSpriteName(string imageName)
        {
            string name = String.Format("{0:0000}", MBitConverter.ToInt32(imageName));
            return name;
        }
    }
}