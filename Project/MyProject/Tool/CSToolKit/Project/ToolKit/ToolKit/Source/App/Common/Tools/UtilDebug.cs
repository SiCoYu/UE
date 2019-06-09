public static class UtilDebug
{
	public static void Assert(bool condition)
	{
		System.Diagnostics.Debug.Assert(condition);
	}

	public static void Assert(bool condition, string desc)
	{
		System.Diagnostics.Debug.Assert(condition, desc);
	}

	public static void Log(string str)
	{
		System.Console.WriteLine(str);
	}

	public static void LogError(string str)
	{
		System.Console.WriteLine(str);
	}
}