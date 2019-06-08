using Newtonsoft.Json.Linq;
using SDK.Lib;

namespace ToolSet
{
    public class SerializeKey
    {
        public static string BaseLevelInfo = "BaseLevelInfo";
        public static string DailyLevelInfo = "DailyLevelInfo";
        public static string Gold = "Gold";
        public static string Star = "Star";
        public static string UpdateTime = "UpdateTime";
        public static string VersionAndGameId = "ak-010101";       // 版本和游戏Id
        public static string Version = "al-010101";                // 版本
        public static string GameId = "am-010101";                 // 游戏Id
    }

    public class KeyValueItem
    {
        public string mKey;
        public string mValue;
    }

    public class OnePlayerInfo
    {
        public string mId;
        public string mStar;
        public string mGold;
        public string mBaseLevelInfo;
        public string mDailyLevelInfo;
        public string mUpdateTime;
        public string mVersion;
        public string mGameId;

        public MKeyIndexList<int, LevelJson> mBaseLevelInfoJsonList;
        public MKeyIndexList<int, LevelJson> mDailyLevelInfoJsonList;
        public MList<KeyValueItem> mKeyValueList;

        public OnePlayerInfo()
        {
            this.mStar = "0";
            this.mGold = "0";
            this.mBaseLevelInfo = "";
            this.mDailyLevelInfo = "";
            this.mUpdateTime = "";
            this.mVersion = "1.0.18";
            this.mGameId = "QQPlayGameAB";  // 默认老版本

            this.mBaseLevelInfoJsonList = new MKeyIndexList<int, LevelJson>();
            this.mDailyLevelInfoJsonList = new MKeyIndexList<int, LevelJson>();

            this.mKeyValueList = new MList<KeyValueItem>();
        }

        public bool isNewVersion()
        {
            return (this.mGameId == "QQPlayGameAA");
        }

        public bool isTestId()
        {
            bool ret = false;

            if("0179776F18B293E077E6F3BD516734EE" == this.mId ||
               "002E79550EC4A6C0F7ABE541E261A262" == this.mId ||
               "0051BCE0603157B462DBD012FF5D4084" == this.mId ||
               "0059D388E1AC56E6D923DE1E79779D44" == this.mId ||
               "02BBEC1711A36964D8F80E1A45B6AAED" == this.mId ||
               "00B5CD6E678EE6B392DBFF033631522B" == this.mId ||
               "001D2DF74A94AE26F6D90BA1D7FCC2D5" == this.mId ||
               "00415CD04E4EE3CE8BE857993D898C9" == this.mId ||
               "01F4003B84B977DFA20AEE719A491FCA" == this.mId ||
               "01D8F658B5CD46A84A59D458145D45CA" == this.mId ||
               "03294371F36592C93C99AFEB809BB60C" == this.mId ||
               "02C4CA5E121DF5BFCD9442A4D4DC0ED6" == this.mId ||
               "0344069077F89A2B7E5AD5EA894841AB" == this.mId ||
               "0323E98440E4F32B90BC49544E94923A" == this.mId ||
               "02D9A55E68B71F223922CA3BBCCDD2C1" == this.mId ||
               "009EA1C9BAEE1FD732E5A808331F7AFE" == this.mId ||
               "00CB915D8D734485EE90D1EA760D1F2B" == this.mId)
            {
                ret = true;
            }

            return ret;
        }

        public void addKV(string key, string value)
        {
            KeyValueItem keyValueItem = new KeyValueItem();
            keyValueItem.mKey = key;
            keyValueItem.mValue = value;
            this.mKeyValueList.add(keyValueItem);

            if (SerializeKey.BaseLevelInfo == key)
            {
                this.mBaseLevelInfo = value;

                JObject jsonObject = null;
                int index = 0;
                int listLen = 11;

                JToken token = null;
                int packId = 0;
                int levelId = 0;

                LevelJson levelJson = null;

                jsonObject = UtilJson.convertStrToJson(this.mBaseLevelInfo);

                if (null != jsonObject)
                {
                    while (index < listLen)
                    {
                        key = "aa-" + index;
                        token = jsonObject.GetValue(key);

                        if (null != token)
                        {
                            packId = UtilJson.getJsonAttrIntFromTokenByName(token, "PackId");
                            levelId = UtilJson.getJsonAttrIntFromTokenByName(token, "LevelId");

                            if (!this.mBaseLevelInfoJsonList.containsKey(index))
                            {
                                levelJson = new LevelJson();
                                this.mBaseLevelInfoJsonList.add(index, levelJson);

                                levelJson.mPackId = packId;
                                levelJson.mLevelId = levelId;
                            }
                        }

                        index += 1;
                    }
                }
            }
            else if (SerializeKey.DailyLevelInfo == key)
            {
                this.mDailyLevelInfo = value;
            }
            else if (SerializeKey.Gold == key)
            {
                this.mGold = value;
            }
            else if (SerializeKey.Star == key)
            {
                this.mStar = value;
            }
            else if (SerializeKey.UpdateTime == key)
            {
                this.mUpdateTime = value;
            }
            else if (SerializeKey.VersionAndGameId == key)
            {
                JObject jsonObject = null;
                jsonObject = UtilJson.convertStrToJson(value);

                this.mVersion = UtilJson.getJsonAttrStrFromTokenByName(jsonObject, SerializeKey.Version);
                this.mGameId = UtilJson.getJsonAttrStrFromTokenByName(jsonObject, SerializeKey.GameId);
            }
        }

        // 导出 scv 格式数据
        public string toCsv()
        {
            string ret = "";

            ret = string.Format("{0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14}",
                    this.mId,
                    this.mStar,
                    this.mGold,
                    this.getStrLevelInfo(1),
                    this.getStrLevelInfo(2),
                    this.getStrLevelInfo(3),
                    this.getStrLevelInfo(4),
                    this.getStrLevelInfo(5),
                    this.getStrLevelInfo(6),
                    this.getStrLevelInfo(7),
                    this.getStrLevelInfo(8),
                    this.getStrLevelInfo(9),
                    this.getStrLevelInfo(10),
                    this.getStrLevelInfo(11),
                    this.mUpdateTime
                );

            return ret;
        }

        public string toOldCsv()
        {
            string ret = "";

            ret = string.Format("{0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14},{15}",
                    this.mId,
                    this.mGameId,
                    this.mStar,
                    this.mGold,
                    this.getStrLevelInfo(1),
                    this.getStrLevelInfo(2),
                    this.getStrLevelInfo(3),
                    this.getStrLevelInfo(4),
                    this.getStrLevelInfo(5),
                    this.getStrLevelInfo(6),
                    this.getStrLevelInfo(7),
                    this.getStrLevelInfo(8),
                    this.getStrLevelInfo(9),
                    this.getStrLevelInfo(10),
                    this.getStrLevelInfo(11),
                    this.mUpdateTime
                );

            return ret;
        }

        public string toNewCsv()
        {
            string ret = "";

            ret = string.Format("{0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14},{15},{16},{17},{18},{19},{20},{21},{22},{23},{24},{25},{26},{27},{28},{29},{30},{31},{32},{33},{34},{35},{36},{37},{38},{39},{40},{41}",
                    this.mId,
                    this.mGameId,
                    this.mStar,
                    this.mGold,
                    this.getStrLevelInfo(1),
                    this.getStrLevelInfo(2),
                    this.getStrLevelInfo(3),
                    this.getStrLevelInfo(4),
                    this.getStrLevelInfo(5),
                    this.getStrLevelInfo(6),
                    this.getStrLevelInfo(7),
                    this.getStrLevelInfo(8),
                    this.getStrLevelInfo(9),
                    this.getStrLevelInfo(10),
                    this.getStrLevelInfo(11),
                    this.getStrLevelInfo(12),
                    this.getStrLevelInfo(13),
                    this.getStrLevelInfo(14),
                    this.getStrLevelInfo(15),
                    this.getStrLevelInfo(16),
                    this.getStrLevelInfo(17),
                    this.getStrLevelInfo(18),
                    this.getStrLevelInfo(19),
                    this.getStrLevelInfo(20),
                    this.getStrLevelInfo(21),
                    this.getStrLevelInfo(22),
                    this.getStrLevelInfo(23),
                    this.getStrLevelInfo(24),
                    this.getStrLevelInfo(25),
                    this.getStrLevelInfo(26),
                    this.getStrLevelInfo(27),
                    this.getStrLevelInfo(28),
                    this.getStrLevelInfo(29),
                    this.getStrLevelInfo(30),
                    this.getStrLevelInfo(31),
                    this.getStrLevelInfo(32),
                    this.getStrLevelInfo(33),
                    this.getStrLevelInfo(34),
                    this.getStrLevelInfo(35),
                    this.getStrLevelInfo(36),
                    this.getStrLevelInfo(37),
                    this.mUpdateTime
                );

            return ret;
        }

        public string toDataBase()
        {
            string ret = "";

            int index = 0;
            int listLen = this.mKeyValueList.count();
            KeyValueItem keyValueItem = null;

            while (index < listLen)
            {
                keyValueItem = this.mKeyValueList.get(index);

                if(index > 0)
                {
                    ret += UtilSysLibWrap.CR_LF;
                }

                ret += string.Format("1901270677,{0},{1},{2},{3},{4}",
                        this.mId,
                        keyValueItem.mKey,
                        UtilSysLibWrap.encodeURIParam(keyValueItem.mValue),
                        "0", 
                        "0"
                    );

                index += 1;
            }

            return ret;
        }

        public LevelJson getLevelJson(int menuId)
        {
            LevelJson levelJson = null;

            if(this.mBaseLevelInfoJsonList.containsKey(menuId))
            {
                levelJson = this.mBaseLevelInfoJsonList.value(menuId);
            }

            return levelJson;
        }

        public string getStrLevelInfo(int menuId)
        {
            string ret = "";

            LevelJson levelJson = null;
            levelJson = this.getLevelJson(menuId);

            if(null != levelJson)
            {
                ret = string.Format("[{0}]-[{1}]", levelJson.mPackId, levelJson.mLevelId);
            }
            else
            {
                ret = string.Format("[{0}]-[{1}]", 0, 0);
            }

            return ret;
        }
    }

    public class ExportCsvFromJsonData
    {
        public MKeyIndexList<string, OnePlayerInfo> mId2PlayerList;
        public int mMaxCount;       // 最大玩家数量
        public int mMaxOldVersionCount;       // 最大玩家数量
        public int mCurOldVersionCount;
        public int mMaxNewVersionCount;       // 最大玩家数量
        public int mCurNewVersionCount;

        public ExportCsvFromJsonData()
        {
            this.mId2PlayerList = new MKeyIndexList<string, OnePlayerInfo>();
            this.mMaxCount = 50000000;
            this.mMaxOldVersionCount = 50000;
            this.mCurOldVersionCount = 0;
            this.mMaxNewVersionCount = 50000;
            this.mCurNewVersionCount = 0;
        }

        public int count()
        {
            return this.mId2PlayerList.count();
        }

        public void incCurOldVersionCount()
        {
            this.mCurOldVersionCount += 1;
        }

        public bool isOldVersionCountGreatMax()
        {
            return this.mCurOldVersionCount > this.mMaxOldVersionCount;
        }

        public void incCurNewVersionCount()
        {
            this.mCurNewVersionCount += 1;
        }

        public bool isNewVersionCountGreatMax()
        {
            return this.mCurNewVersionCount > this.mMaxNewVersionCount;
        }

        public OnePlayerInfo getPlayerInfo(int index)
        {
            OnePlayerInfo ret = null;

            ret = this.mId2PlayerList.get(index);

            return ret;
        }

        public void addPlayerKeyValue(string id, string key, string value)
        {
            OnePlayerInfo playerInfo = null;

            if (!this.mId2PlayerList.containsKey(id))
            {
                // 不能超过最大数量
                if (this.mId2PlayerList.count() < this.mMaxCount)
                {
                    playerInfo = new OnePlayerInfo();
                    this.mId2PlayerList.add(id, playerInfo);

                    playerInfo.mId = id;
                }
            }
            else
            {
                playerInfo = this.mId2PlayerList.value(id);
            }

            if (null != playerInfo)
            {
                playerInfo.addKV(key, value);
            }
        }

        // 表头
        public string toCsvHead()
        {
            string ret = "";

            ret = "OpenId,Star,Gold,Basic level,SIOR Puzzle,APEX Puzzle,6 X 6,7 X 7,8 X 8,9 X 9,10 X 10,11 X 11,12 X 12,13 X 13,time";

            return ret;
        }

        public string toOldCsvHead()
        {
            string ret = "";

            ret = "OpenId,GameId,Star,Gold,Basic level,SIOR Puzzle,APEX Puzzle,6 X 6,7 X 7,8 X 8,9 X 9,10 X 10,11 X 11,12 X 12,13 X 13,time";

            return ret;
        }

        public string toNewCsvHead()
        {
            string ret = "";

            ret = "OpenId,GameId,Star,Gold,新手1,新手2,入门1,入门2,入门3,入门4,常规1,常规2,常规3,常规4,进阶1,进阶2,进阶3,进阶4,进阶5,高级1,高级2,高级3,高级4,高级5,专家1,专家2,专家3,专家4,大师1,大师2,大师3,大师4,宗师1,宗师2,宗师3,宗师4,泰斗1,泰斗2,泰斗3,泰斗4,圣贤1,time";

            ret = UtilStr.convStringFromOneEncode2AnotherEncode(ref ret, MEncode.eUTF8, MEncode.eGB2312);

            return ret;
        }

        public string toDataBaseHead()
        {
            string ret = "";

            ret = "appid,openid,k,value,create_time,update_time";

            ret = UtilStr.convStringFromOneEncode2AnotherEncode(ref ret, MEncode.eUTF8, MEncode.eGB2312);

            return ret;
        }
    }
}