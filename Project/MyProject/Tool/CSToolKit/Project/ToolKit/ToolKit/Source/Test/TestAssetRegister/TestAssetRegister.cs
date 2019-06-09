namespace ToolSet
{
	public class TestAssetRegister : TestBase
	{
		protected AssetRegister mAssetRegister;

		public TestAssetRegister()
		{
			this.mAssetRegister = new AssetRegister();
		}

		public override void init()
		{
			base.init();

			this.mAssetRegister.init();
		}

		public override void dispose()
		{
			base.dispose();

			this.mAssetRegister.dispose();
			this.mAssetRegister = null;
		}

		public override void run()
		{
			base.run();
		}
	}
}