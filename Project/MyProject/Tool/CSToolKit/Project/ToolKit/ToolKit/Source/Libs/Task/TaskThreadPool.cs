﻿using System.Collections.Generic;

namespace SDK.Lib
{
    public class TaskThreadPool
    {
        protected MList<TaskThread> mList;

        public TaskThreadPool()
        {

        }

        public void init()
        {

        }

        public void dispose()
        {

        }

        public void initThreadPool(int numThread, TaskQueue taskQueue)
        {
            this.mList = new MList<TaskThread>(numThread);
            int index = 0;

            for(index = 0; index < numThread; ++index)
            {
                this.mList.add(new TaskThread(string.Format("TaskThread{0}", index), taskQueue));
                this.mList[index].start();
            }
        }

        public void notifyIdleThread()
        {
            foreach(var item in this.mList.list())
            {
                if(item.notifySelf())       // 如果唤醒某个线程就退出，如果一个都没有唤醒，说明当前线程都比较忙，需要等待
                {
                    break;
                }
            }
        }
    }
}