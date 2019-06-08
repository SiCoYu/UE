using SDK.Lib;

namespace ToolSet
{
    public class MergeFile
    {
        protected string mRootPath;
        protected string mOutPath;
        protected MFileStream mFileStream;

        public MergeFile()
        {
            this.mRootPath = "";
            this.mOutPath = "";
        }

        public void init()
        {
            
        }

        public void dispose()
        {
            
        }

        public void mergeFile()
        {
            //this.mRootPath = UtilFileIO.getCurrentDirectory();
            this.mRootPath = "G:/File/opensource/unity-game-git/MaYun/Html5Game/Project/Start/ProjectA/assets/Scripts";
            this.mOutPath = UtilFileIO.combine(this.mRootPath, "Out");
            UtilFileIO.clearOrCreateDirectory(this.mOutPath);

            this.mOutPath = UtilFileIO.combine(this.mRootPath, "Out/MergeFile.txt");
            this.mFileStream = new MFileStream(this.mOutPath, null, MFileMode.eCreate, MFileAccess.eWrite);
            this.mFileStream.open();

            UtilFileIO.traverseDirectory(
                this.mRootPath, 
                "", 
                null, 
                null, 
                null, 
                this.onFileHandle, 
                true, 
                false
            );

            this.mFileStream.dispose();
            this.mFileStream = null;
        }

        public void onFileHandle(string srcFullPath, string fileName, string destFullPath)
        {
            string fileExtName = UtilFileIO.getFileExt(fileName);

            System.Console.Write(srcFullPath + " Start" + " \n");

            if ("js" == fileExtName)
            {
                MFileStream fileStream = new MFileStream(srcFullPath, null, MFileMode.eOpen, MFileAccess.eRead);
                fileStream.open();

                string fileContent = fileStream.readText();
                this.mFileStream.writeText(fileContent);

                this.mFileStream.writeText(UtilSysLibWrap.CR_LF);

                fileStream.dispose();
                fileStream = null;
            }

            System.Console.Write(srcFullPath + " End" + " \n");
        }
    }
}