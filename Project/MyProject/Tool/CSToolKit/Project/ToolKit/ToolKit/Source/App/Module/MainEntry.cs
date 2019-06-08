namespace ToolSet
{
    public class MainEntry
    {
        public static void Main(string[] args)
        {
            AppFrame myApp = new AppFrame();
            myApp.init();
            myApp.run();
        }
    }
}