namespace SDK.Lib
{
    /**
     * @brief 默认的接口实现
     */
    public class NullDelayHandleItem : IDelayHandleItem
    {
        public void setClientDispose(bool isDispose)
        {

        }

        public bool isClientDispose()
        {
            return false;
        }
    }
}