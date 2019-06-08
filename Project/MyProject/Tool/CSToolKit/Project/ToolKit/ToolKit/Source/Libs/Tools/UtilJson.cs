using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.IO;

namespace SDK.Lib
{
    public class UtilJson
    {
        static public JObject convertStrToJson(string str)
        {
            JObject jsonObj = null;

            try
            {
                //格式化json字符串
                JsonSerializer serializer = new JsonSerializer();
                TextReader tr = new StringReader(str);
                JsonTextReader jtr = new JsonTextReader(tr);

                object obj = serializer.Deserialize(jtr);
                jsonObj = obj as JObject;
            }
            catch(Exception exp)
            {
                System.Console.Write(exp.Message + " \n");
            }

            return jsonObj;
        }

        static public string convertJsonToStr(JObject jsonObj)
        {
            string ret = "";

            if (jsonObj != null)
            {
                JsonSerializer serializer = new JsonSerializer();
                StringWriter textWriter = new StringWriter();

                JsonTextWriter jsonWriter = new JsonTextWriter(textWriter)
                {
                    Formatting = Formatting.Indented,
                    Indentation = 4,
                    IndentChar = ' '
                };

                serializer.Serialize(jsonWriter, jsonObj);
                ret = textWriter.ToString();
            }

            return ret;
        }

        static public JToken getTokenFromJsonObject(JObject jsonObj, string attrPath)
        {
            JToken token = null;

            if (null != jsonObj)
            {
                string[] pathList = attrPath.Split('/');
                token = jsonObj.GetValue(pathList[0]);

                int listLen = pathList.Length;
                int index = 1;

                while (null != token && index < listLen)
                {
                    token = token[pathList[1]];

                    index += 1;
                }

                if (index != listLen)
                {
                    token = null;
                }
            }

            return token;
        }

        static public JToken getTokenFromJsonToken(JToken token, string attrPath)
        {
            JToken ret = null;

            if (null != token)
            {
                string[] pathList = attrPath.Split('/');

                int listLen = pathList.Length;
                int index = 1;

                while (null != token && index < listLen)
                {
                    token = token[pathList[1]];

                    index += 1;
                }

                if (index == listLen)
                {
                    ret = token;
                }
            }

            return token;
        }

        static public bool getJsonAttrBool(JToken token, bool defaultValue = false)
        {
            bool ret = defaultValue;

            if (null != token)
            {
                if (null != token)
                {
                    if (JTokenType.Boolean == token.Type)
                    {
                        ret = (bool)token;
                    }
                }
            }

            return ret;
        }

        static public int getJsonAttrInt(JToken token, int defaultValue = 0)
        {
            int ret = defaultValue;

            if (null != token)
            {
                if (null != token)
                {
                    if (JTokenType.Integer == token.Type)
                    {
                        ret = (int)token;
                    }
                }
            }

            return ret;
        }

        static public float getJsonAttrFloat(JToken token, float defaultValue = 0)
        {
            float ret = defaultValue;

            if (null != token)
            {
                if (null != token)
                {
                    if (JTokenType.Float == token.Type)
                    {
                        ret = (float)token;
                    }
                }
            }

            return ret;
        }

        static public string getJsonAttrString(JToken token, string defaultValue = "")
        {
            string ret = defaultValue;

            if (null != token)
            {
                if (null != token)
                {
                    if (JTokenType.String == token.Type)
                    {
                        ret = (string)token;
                    }
                }
            }

            return ret;
        }

        static public bool getJsonAttrBoolFromTokenByName(JToken token, string attrName, bool defaultValue = false)
        {
            bool ret = defaultValue;

            if (null != token && token.HasValues)
            {
                //ret = token.Value<bool>(attrName);

                JToken valueToken = token[attrName];

                if (null != valueToken)
                {
                    if (JTokenType.Boolean == valueToken.Type)
                    {
                        ret = (bool)valueToken;
                    }
                }
            }

            return ret;
        }

        static public int getJsonAttrIntFromTokenByName(JToken token, string attrName, int defaultValue = 0)
        {
            int ret = defaultValue;

            if (null != token && token.HasValues)
            {
                //ret = token.Value<int>(attrName);

                JToken valueToken = token[attrName];

                if (null != valueToken)
                {
                    if (JTokenType.Integer == valueToken.Type)
                    {
                        ret = (int)valueToken;
                    }
                }
            }

            return ret;
        }

        static public float getJsonAttrFloatFromTokenByName(JToken token, string attrName, float defaultValue = 0)
        {
            float ret = defaultValue;

            if (null != token && token.HasValues)
            {
                //ret = token.Value<float>(attrName);

                JToken valueToken = token[attrName];

                if (null != valueToken)
                {
                    if (JTokenType.Float == valueToken.Type)
                    {
                        ret = (float)valueToken;
                    }
                }
            }

            return ret;
        }

        static public string getJsonAttrStrFromTokenByName(JToken token, string attrName, string defaultValue = "")
        {
            string ret = defaultValue;

            if (null != token && token.HasValues)
            {
                //ret = token.Value<float>(attrName);

                JToken valueToken = token[attrName];

                if (null != valueToken)
                {
                    if (JTokenType.String == valueToken.Type)
                    {
                        ret = (string)valueToken;
                    }
                }
            }

            return ret;
        }

        static public bool getJsonAttrBoolFromJsonObjectByPath(JObject jsonObj, string attrPath, bool defaultValue = false)
        {
            bool ret = defaultValue;

            if (null != jsonObj)
            {
                JToken token = UtilJson.getTokenFromJsonObject(jsonObj, attrPath);
                ret = UtilJson.getJsonAttrBool(token);
            }

            return ret;
        }

        static public int getJsonAttrIntFromJsonObjectByPath(JObject jsonObj, string attrPath, int defaultValue = 0)
        {
            int ret = defaultValue;

            if (null != jsonObj)
            {
                JToken token = UtilJson.getTokenFromJsonObject(jsonObj, attrPath);
                ret = UtilJson.getJsonAttrInt(token);
            }

            return ret;
        }

        static public float getJsonAttrFloatFromJsonObjectByPath(JObject jsonObj, string attrPath, float defaultValue = 0)
        {
            float ret = defaultValue;

            if (null != jsonObj)
            {
                JToken token = UtilJson.getTokenFromJsonObject(jsonObj, attrPath);
                ret = UtilJson.getJsonAttrFloat(token);
            }

            return ret;
        }

        static public string getJsonAttrStringFromJsonObjectByPath(JObject jsonObj, string attrPath, string defaultValue = "")
        {
            string ret = defaultValue;

            if (null != jsonObj)
            {
                JToken token = UtilJson.getTokenFromJsonObject(jsonObj, attrPath);
                ret = UtilJson.getJsonAttrString(token);
            }

            return ret;
        }
    }
}