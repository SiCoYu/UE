namespace SDK.Lib
{
    /**
     * @brief 自动更新错误原因
     */
    public class AutoUpdateErrorInfo
    {
        protected AutoUpdateErrorCode mAutoUpdateErrorCode;
        protected string mAutoUpdateErrorDesc;

        public AutoUpdateErrorInfo()
        {
            this.mAutoUpdateErrorCode = AutoUpdateErrorCode.eErrorNo;
            this.mAutoUpdateErrorDesc = "";
        }

        public AutoUpdateErrorCode getErrorCode()
        {
            return this.mAutoUpdateErrorCode;
        }

        public void setErrorCode(AutoUpdateErrorCode value)
        {
            this.mAutoUpdateErrorCode = value;
        }
    }
}