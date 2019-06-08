namespace ToolSet
{
    public class MergeFileCtx
    {
        public MergeFile mMergeFile;

        public MergeFileCtx()
        {

        }

        public void _preInit()
        {
            this.mMergeFile = new MergeFile();
        }

        public void _execInit()
        {
            this.mMergeFile.init();
        }

        public void _postInit()
        {
            
        }

        public void _preDispose()
        {
            
        }

        public void _execDispose()
        {
            this.mMergeFile.dispose();
        }

        public void _postDispose()
        {

        }
    }
}