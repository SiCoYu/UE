using System.Text;

namespace SDK.Lib
{
    public class UtilStr
    {
        static public bool IsNullOrEmpty(string str)
        {
            bool ret = false;
            ret = string.IsNullOrEmpty(str);
            return ret;
        }

        static public void removeLastCR(ref string srcStr)
        {
            if(!string.IsNullOrEmpty(srcStr))
            {
                if(srcStr[srcStr.Length - 1] == Symbolic.CR)
                {
                    srcStr = srcStr.Substring(0, srcStr.Length - 1);
                }
            }
        }

        //static public void split(ref string str, params string[] param)
        // 仅支持一个符号分割
        static public string[] split(ref string str, char splitSymbol)
        {
            char[] split = new char[1];
            split[0] = splitSymbol;
            string[] strArr = null;

            if (!string.IsNullOrEmpty(str))
            {
                strArr = str.Split(split);
            }

            return strArr;
        }

        static public string[] split(ref string str, string splitSymbol)
        {
            string[] split = new string[1];
            split[0] = splitSymbol;
            string[] strArr = null;

            if (!string.IsNullOrEmpty(str))
            {
                strArr = str.Split(split, System.StringSplitOptions.RemoveEmptyEntries);
            }

            return strArr;
        }

        // 计算字符最后出现的位置，仅支持一个字符， string::LastIndexOf 比较耗时，好像要进入本地代码执行
        static public int LastIndexOf(ref string str, char findStr)
        {
            int lastIndex = -1;
            int index = str.Length - 1; 

            while (index >= 0)
            {
                if(str[index] == findStr)
                {
                    lastIndex = index;
                    break;
                }

                --index;
            }

            return lastIndex;
        }

        static public int IndexOf(ref string str, char findStr)
        {
            int retIndex = -1;
            int index = 0;
            int listLen = str.Length;

            while (index < listLen)
            {
                if (str[index] == findStr)
                {
                    retIndex = index;
                    break;
                }

                index += 1;
            }

            return retIndex;
        }

        static public string toStringByCount(int count, string str)
        {
            if(count < 0)
            {
                count = 0;
            }

            string ret = "";
            System.Text.StringBuilder stringBuilder = new System.Text.StringBuilder();

            int index = 0;

            while(index < count)
            {
                stringBuilder.Append(str);

                index += 1;
            }

            ret = stringBuilder.ToString();

            return ret;
        }

        static public string formatFloat(float a, int b)
        {
            string s = a.ToString("F" + b);
            return s;
        }

        static public string getPrefixStr(string src, char splitChar)
        {
            string ret = "";

            int index = src.IndexOf(splitChar);

            // 找到并且不是第 0 个
            if (-1 != index && index != 0)
            {
                ret = src.Substring(0, index);
            }

            return ret;
        }

        static public string getSuffixStr(string src, char splitChar)
        {
            string ret = "";

            int index = src.IndexOf(splitChar);

            // 找到并且不是最后一个
            if (-1 != index && index != src.Length -1)
            {
                ret = src.Substring(index + 1, src.Length - 1 - index);
            }

            return ret;
        }

        static public string toLower(string str)
        {
            return str.ToLower();
        }

        static public string lower(string str)
        {
            return str.ToLower();
        }

        static public string replace(string srcStr, string findStr, string replaceStr)
        {
            return srcStr.Replace(findStr, replaceStr);
        }

        static public string truncate(string srcStr, int start = -1, int end = -1)
        {
            string ret = "";

            if (start != -1 && end != -1)
            {
                ret = srcStr.Substring(start, end);
            }
            else if(start != -1 && end == -1)
            {
                ret = srcStr.Substring(start);
            }
            else if(start == -1 && end != -1)
            {
                ret = srcStr.Substring(0, end);
            }

            return ret;
        }

        static public int len(string str)
        {
            int listLen = 0;
            listLen = str.Length;
            return listLen;
        }

        static public string format(string formatStr, object var0, object var1 = null, object var2 = null, object var3 = null, object var4 = null, object var5 = null, object var6 = null, object var7 = null, object var8 = null, object var9 = null)
        {
            string ret = "";

            if (var0 != null && var1 != null && var2 != null && var3 != null && var4 != null && var5 != null && var6 != null && var7 != null && var8 != null && var9 != null)
            {
                ret = string.Format(formatStr, var0, var1, var2, var3, var4, var5, var6, var7, var8, var9);
            }
            else if(var0 != null && var1 != null && var2 != null && var3 != null && var4 != null && var5 != null && var6 != null && var7 != null && var8 != null)
            {
                ret = string.Format(formatStr, var0, var1, var2, var3, var4, var5, var6, var7, var8);
            }
            else if (var0 != null && var1 != null && var2 != null && var3 != null && var4 != null && var5 != null && var6 != null && var7 != null)
            {
                ret = string.Format(formatStr, var0, var1, var2, var3, var4, var5, var6, var7);
            }
            else if (var0 != null && var1 != null && var2 != null && var3 != null && var4 != null && var5 != null && var6 != null)
            {
                ret = string.Format(formatStr, var0, var1, var2, var3, var4, var5, var6);
            }
            else if (var0 != null && var1 != null && var2 != null && var3 != null && var4 != null && var5 != null)
            {
                ret = string.Format(formatStr, var0, var1, var2, var3, var4, var5);
            }
            else if (var0 != null && var1 != null && var2 != null && var3 != null && var4 != null)
            {
                ret = string.Format(formatStr, var0, var1, var2, var3, var4);
            }
            else if (var0 != null && var1 != null && var2 != null && var3 != null)
            {
                ret = string.Format(formatStr, var0, var1, var2, var3);
            }
            else if (var0 != null && var1 != null && var2 != null)
            {
                ret = string.Format(formatStr, var0, var1, var2);
            }
            else if (var0 != null && var1 != null)
            {
                ret = string.Format(formatStr, var0, var1);
            }
            else if (var0 != null)
            {
                ret = string.Format(formatStr, var0);
            }
            else
            {
                ret = "";
            }

            return ret;
        }

        public static string convStringFromOneEncode2AnotherEncode(ref string srcStr, MEncode srcEncode, MEncode destEncode)
        {
            string ret = "";

            Encoding srcNativeEncode = UtilSysLibWrap.convOneEncode2AnotherEncode(srcEncode);
            Encoding destNativeEncode = UtilSysLibWrap.convOneEncode2AnotherEncode(destEncode);

            byte[] srcBytes = srcNativeEncode.GetBytes(srcStr);
            byte[] destBytes = Encoding.Convert(srcNativeEncode, destNativeEncode, srcBytes);

            ret = destNativeEncode.GetString(destBytes);

            return ret;
        }
    }
}