using SDK.Lib;

namespace ToolSet
{
    public class ExportCustom
    {
        protected string mRootPath;
        protected string mJsonOutPath;

        public ExportCustom()
        {
            this.mRootPath = "";
            this.mJsonOutPath = "";
        }

        virtual public void init()
        {
            
        }

        virtual public void dispose()
        {
            
        }

        public virtual string getRootPath()
        {
            return UtilFileIO.getCurrentDirectory();
        }

        public virtual string getExportDirName()
        {
            return "server_json";
        }

        virtual public void export()
        {
            this.mRootPath = this.getRootPath();
            //this.mRootPath = "D:/File/Work/Client-DunkShot-20180402/Design/Table";
            this.mJsonOutPath = UtilFileIO.combine(this.mRootPath, this.getExportDirName());
            UtilFileIO.clearOrCreateDirectory(this.mJsonOutPath);

            UtilFileIO.traverseDirectory(
                this.mRootPath, 
                "", 
                null, 
                null, 
                null, 
                this.onFileHandle, 
                false, 
                false
            );
        }

        virtual public void onFileHandle(string srcFullPath, string fileName, string destFullPath)
        {
            
        }
    }
}