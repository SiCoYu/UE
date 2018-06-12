namespace SDK.Lib
{
    public class SceneLayerSys
    {
        protected MDictionary<string, int> mAtlas2LayerDepthDic; 

        public SceneLayerSys()
        {
            this.mAtlas2LayerDepthDic = new MDictionary<string, int>();

            this.mAtlas2LayerDepthDic.add("Atlas/Planes/AbandonPlanes.asset", (int)SceneLayerId.ePlayer);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/CartoonPlanes.asset", (int)SceneLayerId.ePlayer + 1);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/DefaultPlanes.asset", (int)SceneLayerId.ePlayer + 2);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Boom.asset", (int)SceneLayerId.ePlayer + 3);

            //飞机
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_1.asset", (int)SceneLayerId.ePlayer + 4);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_2.asset", (int)SceneLayerId.ePlayer + 5);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_3.asset", (int)SceneLayerId.ePlayer + 6);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_4.asset", (int)SceneLayerId.ePlayer + 7);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_5.asset", (int)SceneLayerId.ePlayer + 8);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_6.asset", (int)SceneLayerId.ePlayer + 9);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_7.asset", (int)SceneLayerId.ePlayer + 10);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_8.asset", (int)SceneLayerId.ePlayer + 11);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_9.asset", (int)SceneLayerId.ePlayer + 12);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_10.asset", (int)SceneLayerId.ePlayer + 13);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_11.asset", (int)SceneLayerId.ePlayer + 14);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_12.asset", (int)SceneLayerId.ePlayer + 15);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_13.asset", (int)SceneLayerId.ePlayer + 16);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_14.asset", (int)SceneLayerId.ePlayer + 17);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_15.asset", (int)SceneLayerId.ePlayer + 18);
            this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_16.asset", (int)SceneLayerId.ePlayer + 19);
			this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_17.asset", (int)SceneLayerId.ePlayer + 20);
			this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_18.asset", (int)SceneLayerId.ePlayer + 21);
			this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_19.asset", (int)SceneLayerId.ePlayer + 22);
			this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_20.asset", (int)SceneLayerId.ePlayer + 23);
			this.mAtlas2LayerDepthDic.add("Atlas/Planes/Plane_21.asset", (int)SceneLayerId.ePlayer + 24);
            //一定要注意图包路径的大小写（如：Plane_16.asset），否则无法动态合并批次
        }

        // 获取资源映射
        public MDictionary<string, int> getAtlas2LayerDepthDic()
        {
            return this.mAtlas2LayerDepthDic;
        }

        public void init()
        {

        }

        public void dispose()
        {

        }

        public int getLayerDepthByAtlas(string atlas)
        {
            int ret = (int)SceneLayerId.ePlayer;

            this.mAtlas2LayerDepthDic.tryGetValue(atlas, out ret);

            return ret;
        }
    }
}