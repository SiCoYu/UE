namespace ToolSet
{
	public class TestMain
	{
		public TestBuildPak mTestBuildPak;

		public TestMain()
		{
			this.mTestBuildPak = new TestBuildPak();
		}

		public void init()
		{
			this.mTestBuildPak.init();
		}

		public void dispose()
		{
			this.mTestBuildPak.dispose();
			this.mTestBuildPak = null;
		}

		public void run()
		{
			this.mTestBuildPak.run();
		}
	}
}