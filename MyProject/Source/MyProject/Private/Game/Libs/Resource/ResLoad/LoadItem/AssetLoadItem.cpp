﻿using System.Collections;
using UnityEngine;

namespace SDK.Lib
{
    /**
     * @brief 仅仅支持从 Resources 默认 Bundle 包中加载
     */
    public class ResourceLoadItem : LoadItem
    {
        protected UnityEngine.Object m_prefabObj;

        public UnityEngine.Object prefabObj
        {
            get
            {
                return m_prefabObj;
            }
            set
            {
                m_prefabObj = value;
            }
        }

        override public void load()
        {
            base.load();
            if (m_loadNeedCoroutine)
            {
                Ctx.m_instance.m_coroutineMgr.StartCoroutine(loadFromDefaultAssetBundleByCoroutine());
            }
            else
            {
                loadFromDefaultAssetBundle();
            }
        }

        // 这个是卸载，因为有时候资源加载进来可能已经不用了，需要直接卸载掉
        override public void unload()
        {
            if (m_prefabObj != null)
            {
                UtilApi.DestroyImmediate(m_prefabObj, true);
                m_prefabObj = null;
            }
            base.unload();
        }

        // Resources.Load就是从一个缺省打进程序包里的AssetBundle里加载资源，而一般AssetBundle文件需要你自己创建，运行时 动态加载，可以指定路径和来源的。
        protected void loadFromDefaultAssetBundle()
        {
            m_prefabObj = Resources.Load<Object>(m_pathNoExt);

            if (m_prefabObj != null)
            {
                nonRefCountResLoadResultNotify.resLoadState.setSuccessLoaded();
            }
            else
            {
                nonRefCountResLoadResultNotify.resLoadState.setFailed();
            }
            nonRefCountResLoadResultNotify.loadResEventDispatch.dispatchEvent(this);
        }

        protected IEnumerator loadFromDefaultAssetBundleByCoroutine()
        {
            ResourceRequest req = Resources.LoadAsync<Object>(m_pathNoExt);
            yield return req;

            if (req.asset != null && req.isDone)
            {
                m_prefabObj = req.asset;
                nonRefCountResLoadResultNotify.resLoadState.setSuccessLoaded();
            }
            else
            {
                nonRefCountResLoadResultNotify.resLoadState.setFailed();
            }

            nonRefCountResLoadResultNotify.loadResEventDispatch.dispatchEvent(this);
        }
    }
}