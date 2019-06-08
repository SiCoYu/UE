namespace SDK.Lib
{
    public enum MFileMode
    {
        eCreateNew = System.IO.FileMode.CreateNew,
        eCreate = System.IO.FileMode.Create,
        eOpen = System.IO.FileMode.Open,
        eOpenOrCreate = System.IO.FileMode.OpenOrCreate,
        eTruncate = System.IO.FileMode.Truncate,
        eAppend = System.IO.FileMode.Append
    }
}