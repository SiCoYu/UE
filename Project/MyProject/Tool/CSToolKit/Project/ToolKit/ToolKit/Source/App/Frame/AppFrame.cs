using SDK.Lib;

namespace ToolSet
{
    public class AppFrame
    {
        public AppFrame()
        {
            
        }

        public void init()
        {
            CtxExt.instance();
            Ctx.msInstance.init();
        }

        public void dispose()
        {
			Ctx.msInstance.dispose();
		}

        public void run()
        {
            Ctx.msInstance.run();
        }
    }
}