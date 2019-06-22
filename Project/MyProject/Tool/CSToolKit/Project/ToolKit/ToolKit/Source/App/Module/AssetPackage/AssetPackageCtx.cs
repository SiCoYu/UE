namespace ToolSet
{
	public class AssetPackageCtx
	{
		public SingleDependencyAssetPackageGraph mSingleDependencyGraph;

		public AssetPackageCtx()
		{
			this.mSingleDependencyGraph = new SingleDependencyAssetPackageGraph();
		}

		public void init()
		{
			this.mSingleDependencyGraph.Init();
		}

		public void dispose()
		{
			if (null != this.mSingleDependencyGraph)
			{
				this.mSingleDependencyGraph.Dispose();
				this.mSingleDependencyGraph = null;
			}
		}
	}
}