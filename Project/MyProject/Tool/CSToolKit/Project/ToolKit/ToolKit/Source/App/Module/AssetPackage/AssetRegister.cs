using SDK.Lib;

namespace ToolSet
{
	public class AssetRegisterDependencyItem
	{
		protected string mAssetPath;

		public AssetRegisterDependencyItem()
		{

		}

		public void setAssetPath(string path)
		{
			this.mAssetPath = path;
		}

		public string getAssetPath()
		{
			return this.mAssetPath;
		}
	}

	public class AssetRegisterItem
	{
		protected string mLongPackageName;
		protected string mAbsolutePackagePath;

		protected MList<AssetRegisterDependencyItem> mAssetDependencyList;
		protected MList<AssetRegisterDependencyItem> mAssetDependencyOtherList;

		public AssetRegisterItem()
		{
			this.mAssetDependencyList = new MList<AssetRegisterDependencyItem>();
			this.mAssetDependencyOtherList = new MList<AssetRegisterDependencyItem>();
		}

		public string GetLongPackageName()
		{
			return this.mLongPackageName;
		}

		public void SetLongPackageName(string path)
		{
			this.mLongPackageName = path;

			UtilUE4EngineWrap.TryConvertLongPackageNameToFilename(ref this.mLongPackageName, ref this.mAbsolutePackagePath);
		}

		public string GetAbsolutePackagePath()
		{
			return this.mAbsolutePackagePath;
		}

		public void SetAbsolutePackagePath(string path)
		{
			this.mAbsolutePackagePath = path;
		}

		public void addDependencyInAssetPath(string path)
		{
			AssetRegisterDependencyItem item = new AssetRegisterDependencyItem();
			item.setAssetPath(path);
			this.mAssetDependencyList.add(item);
		}

		public void addDependencyInOtherPath(string path)
		{
			AssetRegisterDependencyItem item = new AssetRegisterDependencyItem();
			item.setAssetPath(path);
			this.mAssetDependencyOtherList.add(item);
		}

		public string[] getDependencyArrayInAssetPath()
		{
			string[] ret = new string[this.mAssetDependencyList.count()];

			int index = 0;
			int listLen = this.mAssetDependencyList.count();

			while (index < listLen)
			{
				ret[index] = this.mAssetDependencyList[index].getAssetPath();
				++index;
			}

			return ret;
		}
	}

	public class AssetRegister
	{
		protected MDictionary<string, AssetRegisterItem> mAssetPath2RegisterDic;

		public AssetRegister()
		{
			this.mAssetPath2RegisterDic = new MDictionary<string, AssetRegisterItem>();
		}

		public void init()
		{
			this._parseConfig();
		}

		public void dispose()
		{

		}

		public string[] GetDependencies(string longPackageName, bool recurse)
		{
			AssetRegisterItem item = null;
			string[] ret = null;

			if (this.mAssetPath2RegisterDic.tryGetValue(longPackageName, out item))
			{
				ret = item.getDependencyArrayInAssetPath();
			}

			return ret;
		}

		protected void _parseConfig()
		{
			string path = string.Format("{0}/ExportAssetDependecies/AssetDependencies.json", UtilUE4EngineWrap.ProjectSavedDir());
			MFileStream fileStream = new MFileStream(path);
			fileStream.open();
			string text = fileStream.readText();

			SimpleJSON.JSONNode rootNode = SimpleJSON.JSON.Parse(text);
			string key = null;
			SimpleJSON.JSONNode valueNode = null;
			SimpleJSON.JSONArray valueNodeArray = null;
			int index = 0;
			string valueStr;
			AssetRegisterItem assetRegisterItem = null;

			//foreach (SimpleJSON.JSONNode assetNode in rootNode.Children)
			//foreach (string keys in rootNode.Keys)
			foreach (System.Collections.Generic.KeyValuePair<string, SimpleJSON.JSONNode> kvData in rootNode)
			{
				key = kvData.Key;

				assetRegisterItem = new AssetRegisterItem();
				this.mAssetPath2RegisterDic.add(key, assetRegisterItem);

				assetRegisterItem.SetLongPackageName(key);
				valueNode = kvData.Value["DependenciesInGameContentDir"];
				valueNodeArray = valueNode.AsArray;

				while (index < valueNodeArray.Count)
				{
					valueStr = valueNodeArray[index].ToString();
					assetRegisterItem.addDependencyInAssetPath(valueStr);
					++index;
				}

				index = 0;

				valueNode = kvData.Value["OtherDependencies"];
				valueNodeArray = valueNode.AsArray;

				while (index < valueNodeArray.Count)
				{
					valueStr = valueNodeArray[index].ToString();
					assetRegisterItem.addDependencyInOtherPath(valueStr);
					++index;
				}
			}
		}
	}
}