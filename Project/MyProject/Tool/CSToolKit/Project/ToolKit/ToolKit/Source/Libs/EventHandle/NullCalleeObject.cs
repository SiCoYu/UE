namespace SDK.Lib
{
    /**
     * @brief 默认的接口实现
     */
    public class NullCalleeObject : ICalleeObject
    {
        public void call(IDispatchObject dispObj, uint uniqueId)
        {

        }
    }
}