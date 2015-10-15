#ifndef __MsgRouteDispList_H
#define __MsgRouteDispList_H

#include "MList.h"

class MsgRouteDispHandle;

class MsgRouteDispList
{
protected:
	MList<MsgRouteDispHandle*> m_dispList;

public:
    void addOneDisp(MsgRouteDispHandle* disp)
    {
        if(m_dispList.IndexOf(disp) == -1)
        {
            m_dispList.Add(disp);
        }
    }

    void removeOneDisp(MsgRouteDispHandle* disp)
    {
        if(m_dispList.IndexOf(disp) != -1)
        {
            m_dispList.Remove(disp);
        }
    }

    void handleMsg(MsgRouteBase* msg)
    {
        for(auto item : m_dispList.getList())
        {
            item.handleMsg(msg);
        }

        //Ctx.m_instance.m_poolSys.deleteObj(msg);
    }
};

#endif