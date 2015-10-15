﻿using System.Collections.Generic;

namespace SDK.Lib
{
    public class MsgRouteDispHandle
    {
        public Dictionary<int, MsgRouteHandleBase> m_id2DispDic = new Dictionary<int, MsgRouteHandleBase>();

        public virtual void handleMsg(MsgRouteBase msg)
        {
            string textStr = "";
            if (m_id2DispDic.ContainsKey((int)msg.m_msgType))
            {
                textStr = Ctx.m_instance.m_langMgr.getText(LangTypeId.eMsgRoute1, LangItemID.eItem2);
                Ctx.m_instance.m_logSys.log(string.Format(textStr, (int)msg.m_msgType));
                m_id2DispDic[(int)msg.m_msgType].handleMsg(msg);
            }
            else
            {
                textStr = Ctx.m_instance.m_langMgr.getText(LangTypeId.eMsgRoute1, LangItemID.eItem3);
                Ctx.m_instance.m_logSys.log(string.Format(textStr, (int)msg.m_msgID));
            }
        }
    }
}