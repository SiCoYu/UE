using SDK.Lib;

public class AssetRegister
{
	public AssetRegister()
	{

	}

	public void Init()
	{
		this._parseConfig();
	}

	public void Dispose()
	{

	}

	public string[] GetDependencies(string longPackageName, bool recurse)
	{
		return null;
	}

	protected void _parseConfig()
	{
		string path = "";
		MFileStream fileStream = new MFileStream(path);
		fileStream.open();
		string text = fileStream.readText();

		SimpleJSON.JSONNode rootNode = SimpleJSON.JSON.Parse(text);
		SimpleJSON.JSONNode dependencyNode = null;
		string key = null;
		string[] dependencyArray = null;

		foreach (SimpleJSON.JSONNode assetNode in rootNode.Children)
		{
			key = assetNode.Value;
			dependencyArray = assetNode["DependenciesInGameContentDir"];
		}
	}
}