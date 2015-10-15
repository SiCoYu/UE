﻿using System;
using System.Collections.Generic;

namespace SDK.Lib
{
    public class MsgRouteHandleBase
    {
        public Dictionary<int, Action<MsgRouteBase>> m_id2HandleDic = new Dictionary<int, Action<MsgRouteBase>>();

        public virtual void handleMsg(MsgRouteBase msg)
        {
            if (m_id2HandleDic.ContainsKey((int)msg.m_msgID))
            {
                m_id2HandleDic[(int)msg.m_msgID](msg);
            }
            else
            {
                Ctx.m_instance.m_logSys.log(string.Format(Ctx.m_instance.m_langMgr.getText(LangTypeId.eMsgRoute1, LangItemID.eItem1), (int)msg.m_msgID));
            }
        }
    }
}