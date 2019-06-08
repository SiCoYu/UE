namespace SDK.Lib
{
    public class MMalloc
    {
        /**
         * @brief 申请一个对象
         */
        static public T1 newObject<T1>() where T1 : new()
        {
            T1 ret = default(T1);
            ret = new T1();
            return ret;
        }
    }
}