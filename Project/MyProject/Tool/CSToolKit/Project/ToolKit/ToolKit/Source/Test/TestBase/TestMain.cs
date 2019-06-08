namespace ToolSet
{
	public class TestMain
	{
		public TestBuildOnePak mTestBuildOnePak;

		public TestMain()
		{
			this.mTestBuildOnePak = new TestBuildOnePak();
		}

		public void init()
		{
			this.mTestBuildOnePak.init();
		}

		public void dispose()
		{
			this.mTestBuildOnePak.dispose();
			this.mTestBuildOnePak = null;
		}

		public void run()
		{
			this.mTestBuildOnePak.run();
		}
	}
}