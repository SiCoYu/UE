using System.Collections;
using System.Security;

namespace SDK.Lib
{
    public class UtilXml
    {
        public const int XML_OK = 0;
        public const int XML_FAIL = 1;

        static public int getXmlAttrBool(SecurityElement xmlNode, string attrName, ref bool ret)
        {
            if (null != xmlNode && null != xmlNode.Attributes && xmlNode.Attributes.ContainsKey(attrName))
            {
                if (UtilSysLibWrap.TRUE == xmlNode.Attribute(attrName))
                {
                    ret = true;
                }
                else if (UtilSysLibWrap.FALSE == xmlNode.Attribute(attrName))
                {
                    ret = false;
                }
                else
                {
                    ret = false;
                }

                return XML_OK;
            }

            ret = false;
            return XML_FAIL;
        }

        static public int getXmlAttrStr(SecurityElement xmlNode, string attrName, ref string ret)
        {
            if (null != xmlNode && null != xmlNode.Attributes && xmlNode.Attributes.ContainsKey(attrName))
            {
                ret =  xmlNode.Attribute(attrName);
                return XML_OK;
            }

            ret = "";
            return XML_FAIL;
        }

        static public int getXmlAttrUShort(SecurityElement xmlNode, string attrName, ref ushort ret)
        {
            if (null != xmlNode && null != xmlNode.Attributes && xmlNode.Attributes.ContainsKey(attrName))
            {
                ushort.TryParse(xmlNode.Attribute(attrName), out ret);
                return XML_OK;
            }

            ret = 0;
            return XML_FAIL;
        }

        static public int getXmlAttrInt(SecurityElement xmlNode, string attrName, ref short ret)
        {
            if (null != xmlNode && null != xmlNode.Attributes && xmlNode.Attributes.ContainsKey(attrName))
            {
                short.TryParse(xmlNode.Attribute(attrName), out ret);
                return XML_OK;
            }

            ret = 0;
            return XML_FAIL;
        }

        static public int getXmlAttrUInt(SecurityElement xmlNode, string attrName, ref uint ret)
        {
            if (null != xmlNode && null != xmlNode.Attributes && xmlNode.Attributes.ContainsKey(attrName))
            {
                uint.TryParse(xmlNode.Attribute(attrName), out ret);
                return XML_OK;
            }

            ret = 0;
            return XML_FAIL;
        }

        static public int getXmlAttrInt(SecurityElement xmlNode, string attrName, ref int ret)
        {
            if (null != xmlNode && null != xmlNode.Attributes && xmlNode.Attributes.ContainsKey(attrName))
            {
                int.TryParse(xmlNode.Attribute(attrName), out ret);
                return XML_OK;
            }

            ret = 0;
            return XML_FAIL;
        }

        static public int getXmlAttrFloat(SecurityElement xmlNode, string attrName, ref float ret)
        {
            if (null != xmlNode && null != xmlNode.Attributes && xmlNode.Attributes.ContainsKey(attrName))
            {
                float.TryParse(xmlNode.Attribute(attrName), out ret);
                return XML_OK;
            }

            ret = 0;
            return XML_FAIL;
        }

        // 获取一个 Element 中对应名字是 attrName 的孩子节点列表
        static public int getXmlChildList(SecurityElement xmlNode, string nodeName, ref ArrayList list)
        {
            if (null != xmlNode)
            {
                int index = 0;
                int listLen = xmlNode.Children.Count;
                SecurityElement child = null;

                //foreach (SecurityElement child in xmlNode.Children)
                while(index < listLen)
                {
                    child = xmlNode.Children[index] as SecurityElement;

                    //比对下是否使自己所需要得节点
                    if (child.Tag == nodeName)
                    {
                        list.Add(child);
                    }

                    index += 1;
                }
            }

            if (list.Count > 0)
            {
                return XML_OK;
            }
            else
            {
                list.Clear();
                return XML_FAIL;
            }
        }

        // 获取一个孩子节点
        static public int getXmlChild(SecurityElement xmlNode, string nodeName, ref SecurityElement childNode)
        {
            if (null != xmlNode)
            {
                int index = 0;
                int listLen = xmlNode.Children.Count;
                SecurityElement child = null;

                //foreach (SecurityElement child in xmlNode.Children)
                while(index < listLen)
                {
                    child = xmlNode.Children[index] as SecurityElement;

                    //比对下是否使自己所需要得节点
                    if (child.Tag == nodeName)
                    {
                        childNode = child;
                        return XML_OK;
                    }

                    index += 1;
                }
            }

            childNode = null;
            return XML_FAIL;
        }

        // 获取某一个元素的所有 Child 列表
        public static int getXmlElementAllChildList(SecurityElement xmlNode, string nodeName, ref ArrayList list)
        {
            SecurityElement objElem = null;

            if (string.IsNullOrEmpty(nodeName))
            {
                objElem = xmlNode;
            }
            else
            {
                UtilXml.getXmlChild(xmlNode, nodeName, ref objElem);
            }

            list = objElem.Children;

            return XML_OK;
        }

        // 获取一个 Element 中对应目录是 pathListStr 的列表，目录个是为 "aaa.bbb.ccc"
        static public int getXmlChildListByPath(
            SecurityElement xmlNode, 
            string pathListStr, 
            ref ArrayList list
            )
        {
            string[] pathList = UtilStr.split(ref pathListStr, '.');
            string curName = "";
            SecurityElement curElement = xmlNode;  // 当前元素

            int elemIdx = 0;
            int elemLen = 0;

            int childIdx = 0;
            int childLen = 0;

            SecurityElement child = null;
            bool isLastOne = false;

            while (elemIdx < elemLen)
            {
                // 如果是最后一级
                if(elemIdx == elemLen - 1)
                {
                    isLastOne = true;
                }

                curName = pathList[elemIdx];

                if (null != curElement)
                {
                    childIdx = 0;
                    childLen = curElement.Children.Count;

                    while (childIdx < childLen)
                    {
                        child = curElement.Children[childIdx] as SecurityElement;

                        //比对下是否使自己所需要得节点
                        if (child.Tag == curName)
                        {
                            if (!isLastOne)
                            {
                                curElement = child;
                                break;
                            }
                            else
                            {
                                list.Add(child);
                            }
                        }

                        ++childIdx;
                    }
                }

                ++elemIdx;
            }

            if (list.Count > 0)
            {
                return XML_OK;
            }
            else
            {
                list.Clear();
                return XML_FAIL;
            }
        }

        // 遍历每一个节点
        static public void forEachXmlChild(
            SecurityElement xmlNode, 
            string nodeName, 
            ICalleeObject This, 
            MMonoXmlAction<SecurityElement, SecurityElement> handle
            )
        {
            ArrayList itemNodeList = new ArrayList();
            UtilXml.getXmlChildList(xmlNode, nodeName, ref itemNodeList);

            foreach (SecurityElement itemElem in itemNodeList)
            {
                if(null != handle)
                {
                    handle(itemElem, xmlNode);
                }
            }
        }

        static public void getElementsByTagNameAndIndex(
            SecurityElement parentElement,
            string tagName,
            int index,
            ref SecurityElement xmlElement)
        {
            ArrayList arrayList = null;
            UtilXml.getXmlElementAllChildList(parentElement, tagName, ref arrayList);

            if(null != arrayList && 
               index < arrayList.Count)
            {
                xmlElement = arrayList[index] as SecurityElement;
            }
        }

        static public void traverseChildElementByName(
            SecurityElement parentElement,
            string elementName,
            ICalleeObject pThis,
            MMonoXmlAction<SecurityElement, SecurityElement> handle)
        {
            ArrayList arrayList = null;
            UtilXml.getXmlElementAllChildList(parentElement, elementName, ref arrayList);

            if (null != arrayList)
            {
                int index = 0;
                int listLen = arrayList.Count;
                SecurityElement xmlElement = null;

                while (index < listLen)
                {
                    xmlElement = arrayList[index] as SecurityElement;
                    handle(parentElement, xmlElement);
                }
            }
        }
    }
}