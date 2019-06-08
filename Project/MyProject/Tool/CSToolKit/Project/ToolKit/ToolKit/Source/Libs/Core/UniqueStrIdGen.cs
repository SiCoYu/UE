namespace SDK.Lib
{
    /**
     * @brief 唯一字符串生成器
     */
    public class UniqueStrIdGen : UniqueNumIdGen
    {
        public const string PlayerPrefix = "PL";
        public const string PlayerChildPrefix = "PC";
        public const string AbandonPlanePrefix = "AP";
        public const string BoomPlanePrefix = "BP";
        public const string RobotPrefix = "RT";
        public const string SnowBlockPrefix = "SM";
        public const string PlayerTargetPrefix = "PT";
        public const string ScoreEffectPrefix = "SE";
        public const string MeteStonePrefix = "MS";
        public const string GroundEntityPrefix = "GE";

        protected string mPrefix;
        protected string mRetId;
        protected System.Text.StringBuilder mStringBuilder;

        public UniqueStrIdGen(string prefix, uint baseUniqueId)
            : base(baseUniqueId)
        {
            this.mPrefix = prefix;
        }

        public string genNewStrId()
        {
            this.mStringBuilder = new System.Text.StringBuilder();
            this.mStringBuilder.Append(this.mPrefix);
            this.mStringBuilder.Append('_');
            this.mStringBuilder.Append(this.genNewId());
            this.mRetId = this.mStringBuilder.ToString();
            return this.mRetId;
        }

        public string getCurStrId()
        {
            return this.mRetId;
        }

        public string genStrIdById(uint id)
        {
            this.mStringBuilder = new System.Text.StringBuilder();
            this.mStringBuilder.Append(this.mPrefix);
            this.mStringBuilder.Append('_');
            this.mStringBuilder.Append(id);
            this.mRetId = this.mStringBuilder.ToString();
            return this.mRetId;
        }
    }
}