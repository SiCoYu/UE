namespace SDK.Lib
{
    public class Singleton<T> where T : class, IMyDispose, new()
    {
	    protected static T msSingleton;

        public static T getSingleton()
        {
            if (null == msSingleton)
            {
                msSingleton = new T();
                msSingleton.init();
            }

            return msSingleton;
        }

        public static void deleteSingleton()
        {
            if (null != msSingleton)
            {
                msSingleton.dispose();
                msSingleton = null;
            }
        }

        // 是否是有效数据
        public static bool isValid()
        {
            return (null != msSingleton);
        }
    }
}