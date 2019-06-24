namespace ToolSet
{
	public class TestMain
	{
		public TestBuildOnePak mTestBuildOnePak;
		public TestAssetRegister mTestAssetRegister;

		public TestMain()
		{
			this.mTestBuildOnePak = new TestBuildOnePak();
			this.mTestAssetRegister = new TestAssetRegister();
		}

		public void init()
		{
			this.mTestBuildOnePak.init();
			this.mTestAssetRegister.init();
		}

		public void dispose()
		{
			this.mTestBuildOnePak.dispose();
			this.mTestBuildOnePak = null;
			this.mTestAssetRegister.dispose();
			this.mTestAssetRegister = null;
		}

		public void run()
		{
			//this.mTestBuildOnePak.run();
			//this.mTestAssetRegister.run();
		}
	}
}