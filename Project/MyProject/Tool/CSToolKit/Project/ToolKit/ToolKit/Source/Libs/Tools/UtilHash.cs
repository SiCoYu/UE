using System.Security.Cryptography;
using System.IO;
using System.Text;

namespace SDK.Lib
{
    public class UtilHash
    {
        static public string buildStringMd5(string sDataIn)
        {
            string md5Str = "";
            StringBuilder md5StrBuilder = new StringBuilder();
            byte[] data = Encoding.GetEncoding("utf-8").GetBytes(md5Str);

            MD5 md5Provider = new MD5CryptoServiceProvider();
            byte[] bytes = md5Provider.ComputeHash(data);

            for (int index = 0; index < bytes.Length; index++)
            {
                md5StrBuilder.Append(bytes[index].ToString("x2"));
            }

            md5Str = md5StrBuilder.ToString();
            return md5Str;
        }

        static public string buildFileMd5(string filePath)
        {
            FileStream file = new FileStream(filePath, FileMode.Open, FileAccess.Read, FileShare.Read);

            MD5CryptoServiceProvider md5Provider = new MD5CryptoServiceProvider();
            byte[] hash_byte = md5Provider.ComputeHash(file);

            string str = System.BitConverter.ToString(hash_byte);
            str = str.Replace("-", "");

            md5Provider.Clear();
            file.Close();

            return str;
        }
    }
}