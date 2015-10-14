﻿using System;
using UnityEngine;
using System.Collections;

namespace SDK.Lib
{
    public class LoadItem : IDispatchObject
    {
        protected ResPackType m_resPackType;
        protected ResLoadType m_resLoadType;   // 资源加载类型

        protected string m_path;                // 完整的目录
        protected string m_pathNoExt;           // 不包括扩展名字的路径
        protected string m_extName;             // 扩展名字

        protected WWW m_w3File;
        protected bool m_loadNeedCoroutine;     // 加载是否需要协同程序

        protected AssetBundle m_assetBundle;

        protected NonRefCountResLoadResultNotify m_nonRefCountResLoadResultNotify;

        public LoadItem()
        {
            m_nonRefCountResLoadResultNotify = new NonRefCountResLoadResultNotify();
        }

        public ResPackType resPackType
        {
            get
            {
                return m_resPackType;
            }
            set
            {
                m_resPackType = value;
            }
        }

        public string path
        {
            get
            {
                return m_path;
            }
            set
            {
                m_path = value;
            }
        }

        public string pathNoExt
        {
            get
            {
                return m_pathNoExt;
            }
            set
            {
                m_pathNoExt = value;
            }
        }

        public string extName
        {
            get
            {
                return m_extName;
            }
            set
            {
                m_extName = value;
            }
        }

        public WWW w3File
        {
            get
            {
                return m_w3File;
            }
        }

        public bool loadNeedCoroutine
        {
            get
            {
                return m_loadNeedCoroutine;
            }
            set
            {
                m_loadNeedCoroutine = value;
            }
        }

        public ResLoadType resLoadType
        {
            get
            {
                return m_resLoadType;
            }
            set
            {
                m_resLoadType = value;
            }
        }

        public AssetBundle assetBundle
        {
            get
            {
                return m_assetBundle;
            }
            set
            {
                m_assetBundle = value;
            }
        }

        public NonRefCountResLoadResultNotify nonRefCountResLoadResultNotify
        {
            get
            {
                return m_nonRefCountResLoadResultNotify;
            }
            set
            {
                m_nonRefCountResLoadResultNotify = value;
            }
        }

        virtual public void load()
        {
            nonRefCountResLoadResultNotify.resLoadState.setLoading();
        }

        // 这个是卸载，因为有时候资源加载进来可能已经不用了，需要直接卸载掉
        virtual public void unload()
        {

        }

        virtual public void reset()
        {
            //m_type = ResType.eNoneType;
            m_path = "";
            //m_loadNeedCoroutine = false;
            m_w3File = null;
            m_loadNeedCoroutine = false;
        }

        virtual protected IEnumerator downloadAsset()
        {
            string path = "";
            if (m_resLoadType == ResLoadType.eLoadDicWeb)
            {
                path = "file://" + Application.dataPath + "/" + m_path;
            }
            else if (m_resLoadType == ResLoadType.eLoadWeb)
            {
                path = Ctx.m_instance.m_cfg.m_webIP + m_path;
            }
            deleteFromCache(path);
            m_w3File = WWW.LoadFromCacheOrDownload(path, 1);
            //m_w3File = WWW.LoadFromCacheOrDownload(path, UnityEngine.Random.Range(0, int.MaxValue));
            yield return m_w3File;

            onWWWEnd();
        }

        // 检查加载成功
        protected bool isLoadedSuccess(WWW www)
        {
            if (www.error != null)
            {
                return false;
            }

            return true;
        }

        // 加载完成回调处理
        virtual protected void onWWWEnd()
        {
            if (isLoadedSuccess(m_w3File))
            {
                m_assetBundle = m_w3File.assetBundle;

                nonRefCountResLoadResultNotify.resLoadState.setSuccessLoaded();
            }
            else
            {
                nonRefCountResLoadResultNotify.resLoadState.setFailed();
            }

            nonRefCountResLoadResultNotify.loadResEventDispatch.dispatchEvent(this);
        }

        protected void deleteFromCache(string path)
        {
            if(Caching.IsVersionCached(path, 1))
            {
                //Caching.DeleteFromCache(path);
                Caching.CleanCache();
            }
        }
    }
}