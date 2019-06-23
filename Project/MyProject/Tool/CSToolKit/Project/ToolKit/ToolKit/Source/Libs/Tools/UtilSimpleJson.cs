namespace SDK.Lib
{
    public static class UtilSimpleJson
	{
        public static string removeJsonKeyQuotes(ref string jsonKey)
		{
			string ret = jsonKey;

			if('"' == ret[0])
			{
				ret = ret.Substring(1);
			}
			if ('"' == ret[ret.Length - 1])
			{
				ret = ret.Substring(0, ret.Length - 1);
			}

			return ret;
		}
    }
}