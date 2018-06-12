namespace SDK.Lib
{
    /**
     * @brief 场景 Sprite 层
     */
    public enum SceneLayerId
    {
        eTerrain = 0,
        eCameraMask = 1,     // 相机遮罩
        eTerrainFrame = 10,
        eEnergy = 20,           // 能源
        eBullet = 20,           // 子弹也是 0，因为子弹和能源是在同一个图集
        ePlayerShadow = 30,     // 玩家影子，在一个图集里面
        ePlayer = 40,           // 玩家，从 40 - 1000 开始，每一个图集一个深度 [Order in Layer]，这样才会合并批次   
        
        eEffectBase = 200,          // 特效基础值，特效会在更上层，但是会单独的一层
    }
}