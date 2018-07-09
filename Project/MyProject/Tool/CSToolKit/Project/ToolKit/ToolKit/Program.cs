namespace ToolKit
{
    public class Program
    {
        public static void Main(string[] args)
        {
            BuildPak buildPak = new BuildPak();
            buildPak.init();
            buildPak.build();
        }
    }
}