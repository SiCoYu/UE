using System;
using System.IO;
using System.Text;

namespace ToolKit
{
    /**
     * @ref UE4资源热更新 
     * @url http://blog.csdn.net/liulong1567/article/details/71597892
     */
    public class BuildPak
    {
        private void Btn_MultipleBuild_Click(object sender, EventArgs e)
        {
            //sb,sw,textWirter均是为了生成Json字符串而使用的  
            StringBuilder sb = new StringBuilder();
            StringWriter sw = new StringWriter(sb);
            //JsonTextWriter textWriter = new JsonTextWriter(sw);
            //textWriter.Formatting = Formatting.Indented;
            DateTime Today = DateTime.UtcNow;
            int second = Today.Second;

            //生成文件的MD5值  
            string fileMD5 = StrToMD5(second.ToString());

            //textWriter.WriteStartObject();
            //textWriter.WritePropertyName("FileVersion");
            //textWriter.WriteStartObject();
            //textWriter.WritePropertyName("MD5");
            //textWriter.WriteValue(fileMD5);
            //textWriter.WriteEndObject();

            // 检查选中的引擎根目录,其目录下是否包含有UnrealPak.exe文件  
            if (!File.Exists(TextBox_MultipleEnginePath.Text + @"\Engine\Binaries\Win64\UnrealPak.exe"))
            {
                MessageBox.Show("打包失败，没有找到 UnrealPak.exe，引擎路径不存在！");
                Btn_MultipleBuild.Enabled = true;
                Btn_MultipleBuild.Text = "打包";
                return;
            }

            textWriter.WritePropertyName("Files");
            textWriter.WriteStartArray();

            //根据多选框选中的文件来对文件进行打包  
            string[] assetNameArray = TextBox_MultipleUassetPath.Text.Split(' ');
            for (int i = 0; i < assetNameArray.Length; i++)
            {
                string assetFullName = assetNameArray[i].Replace('\\', '/');
                string[] assetArray = assetFullName.Split('/');
                string assetName = assetArray[assetArray.Length - 1].Replace(".uasset", "");
                string assetMD5 = StrToMD5(assetName + second.ToString());
                string outPath = TextBox_MultipleOutPath.Text + "\\" + assetName + ".pak";

                //通过Process相关类来多次调用UnrealPak.exe程序来打包  
                ProcessStartInfo info = new ProcessStartInfo();
                info.FileName = TextBox_MultipleEnginePath.Text + @"\Engine\Binaries\Win64\UnrealPak.exe";
                info.Arguments = @outPath + @" " + @assetFullName;
                info.WindowStyle = ProcessWindowStyle.Minimized;
                Process process = Process.Start(info);
                process.WaitForExit();

                //将文件的信息写入到Json文件中  
                textWriter.WriteStartObject();
                textWriter.WritePropertyName("FileName");
                textWriter.WriteValue(assetName);
                textWriter.WritePropertyName("MD5");
                textWriter.WriteValue(assetMD5);
                textWriter.WriteEndObject();
            }
            MessageBox.Show("生成pak完毕！");
            textWriter.WriteEndArray();
            textWriter.WriteEndObject();

            Btn_MultipleBuild.Text = "打包";
            Btn_MultipleBuild.Enabled = true;

            string saveData =
                TextBox_MultipleEnginePath.Text + ";" +
                TextBox_MultipleUassetPath.Text + ";" +
                TextBox_MultipleOutPath.Text;
            File.WriteAllText(Environment.CurrentDirectory + "/save.txt", saveData);

            //生成Version.txt文件  
            File.WriteAllText(TextBox_MultipleOutPath.Text + "/Version.txt", sb.ToString());
        }
        
        public string StrToMD5(string str)
        {
            byte[] data = Encoding.GetEncoding("GB2312").GetBytes(str);
            MD5 md5 = new MD5CryptoServiceProvider();
            byte[] OutBytes = md5.ComputeHash(data);

            string OutString = "";
            for (int i = 0; i < OutBytes.Length; i++)
            {
                OutString += OutBytes[i].ToString("x2");
            }
            return OutString.ToLower();
        }
    }
}
