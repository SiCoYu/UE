using Mono.Xml;
using SDK.Lib;
using System.Security;

namespace ToolSet
{
	public class ProjectConfig
	{
		protected string mEngineRootPath;
		protected string mProjectRootPath;
		protected string mPakOutPath;

		public ProjectConfig()
		{

		}

		public void init()
		{
			this._parseConfig();
		}

		public void dispose()
		{

		}

		public string getEngineRootPath()
		{
			return this.mEngineRootPath;
		}

		public string getProjectRootPath()
		{
			return this.mProjectRootPath;
		}

		public string getPakOutPath()
		{
			return this.mPakOutPath;
		}

		protected void _parseConfig()
		{
			string path = "ProjectConfig.xml";

			MFileStream fileStream = new MFileStream(path);
			fileStream.open();
			string strXml = fileStream.readText();

			SecurityParser xmlParse = new SecurityParser();
			xmlParse.LoadXml(strXml);
			SecurityElement configElement = xmlParse.ToXml();

			SecurityElement projectElement = null;
			UtilXml.getXmlChild(configElement, "Project", ref projectElement);

			SecurityElement projectPathElement = null;
			UtilXml.getXmlChild(projectElement, "ProjectPath", ref projectPathElement);
			UtilXml.getXmlAttrStr(projectPathElement, "EngineRootPath", ref this.mEngineRootPath);
			UtilXml.getXmlAttrStr(projectPathElement, "ProjectRootPath", ref this.mProjectRootPath);

			SecurityElement pakPathElement = null;
			UtilXml.getXmlChild(projectElement, "PakPath", ref pakPathElement);
			UtilXml.getXmlAttrStr(pakPathElement, "OutPath", ref this.mPakOutPath);
		}
	}
}