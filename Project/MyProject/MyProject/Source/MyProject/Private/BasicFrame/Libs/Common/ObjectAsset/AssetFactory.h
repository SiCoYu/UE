var GlobalNS = require("GlobalNS").GlobalNS;

GlobalNS.MLoader("BuildFactoryBase");

var M = GlobalNS.Class(GlobalNS.BuildFactoryBase);
M.clsName = "AssetFactory";
GlobalNS[M.clsName] = M;

M.prototype.ctor = function ()
{

}

M.prototype.init = function ()
{
    
}

M.prototype.dispose = function ()
{
    
}

M.prototype.createObject = function (typeUniqueId, assetUniqueId)
{
    var ret = null;
    var tmpl = null;

    if(GlobalNS.AssetUniqueId.eAssetUId_FocusEntity == assetUniqueId)
    {
        tmpl = GlobalNS.Ctx.msInstance.mAssetRef.getFocusPrefab();
        ret = GlobalNS.UtilEngineWrap.instantiate(tmpl);
    }
    else if(GlobalNS.AssetUniqueId.eAssetUId_GridEntity == assetUniqueId)
    {
        tmpl = GlobalNS.Ctx.msInstance.mAssetRef.getGridPrefab();
        ret = GlobalNS.UtilEngineWrap.instantiate(tmpl);
    }
    else if(GlobalNS.AssetUniqueId.eAssetUId_MaskEntity0 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity1 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity2 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity3 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity4 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity5 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity6 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity7 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity8 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity9 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity10 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity11 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity12 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity13 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity14 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity15 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity16 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity17 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity18 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity19 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_MaskEntity20 == assetUniqueId)
    {
        tmpl = GlobalNS.Ctx.msInstance.mAssetRef.getMaskPrefabByLineId(
            assetUniqueId - GlobalNS.AssetUniqueId.eAssetUId_MaskEntity0
        );
        ret = GlobalNS.UtilEngineWrap.instantiate(tmpl);
    }
    else if(GlobalNS.AssetUniqueId.eAssetUId_PanelPrefab == assetUniqueId)
    {
        tmpl = GlobalNS.Ctx.msInstance.mAssetRef.getPanelPrefab();
        ret = GlobalNS.UtilEngineWrap.instantiate(tmpl);
    }
    else if(GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity0 == assetUniqueId || 
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity1 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity2 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity3 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity4 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity5 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity6 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity7 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity8 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity9 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity10 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity11 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity12 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity13 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity14 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity15 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity16 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity17 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity18 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity19 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity20 == assetUniqueId)
    {
        tmpl = GlobalNS.Ctx.msInstance.mAssetRef.getSegmentPrefabByLineId(
            assetUniqueId - GlobalNS.AssetUniqueId.eAssetUId_SegmentEntity0
        );
        ret = GlobalNS.UtilEngineWrap.instantiate(tmpl);
    }
    else if(GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity0 == assetUniqueId || 
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity1 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity2 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity3 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity4 == assetUniqueId || 
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity5 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity6 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity7 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity8 == assetUniqueId || 
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity9 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity10 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity11 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity12 == assetUniqueId || 
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity13 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity14 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity15 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity16 == assetUniqueId || 
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity17 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity18 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity19 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity20 == assetUniqueId)
    {
        tmpl = GlobalNS.Ctx.msInstance.mAssetRef.getSegmentPrefabByLineId(
            assetUniqueId - GlobalNS.AssetUniqueId.eAssetUId_SparkSegmentEntity0
        );
        ret = GlobalNS.UtilEngineWrap.instantiate(tmpl);
    }
    else if(GlobalNS.AssetUniqueId.eAssetUId_StartEntity0 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity1 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity2 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity3 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity4 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity5 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity6 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity7 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity8 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity9 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity10 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity11 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity12 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity13 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity14 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity15 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity16 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity17 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity18 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity19 == assetUniqueId ||
            GlobalNS.AssetUniqueId.eAssetUId_StartEntity20 == assetUniqueId)
    {
        tmpl = GlobalNS.Ctx.msInstance.mAssetRef.getStartPrefabByLineId(
            assetUniqueId - GlobalNS.AssetUniqueId.eAssetUId_StartEntity0
        );
        ret = GlobalNS.UtilEngineWrap.instantiate(tmpl);
    }
    else if(GlobalNS.AssetUniqueId.eAssetUId_GridLineEntity == assetUniqueId)
    {
        tmpl = GlobalNS.Ctx.msInstance.mAssetRef.getGridLinePrefab();
        ret = GlobalNS.UtilEngineWrap.instantiate(tmpl);
    }
    else if(GlobalNS.AssetUniqueId.eAssetUId_SparkEntity == assetUniqueId)
    {
        tmpl = GlobalNS.Ctx.msInstance.mAssetRef.getSparkPrefab();
        ret = GlobalNS.UtilEngineWrap.instantiate(tmpl);
    }
    else if(GlobalNS.AssetUniqueId.eAssetUId_TrailEntity == assetUniqueId)
    {
        tmpl = GlobalNS.Ctx.msInstance.mAssetRef.getTrailPrefab();
        ret = GlobalNS.UtilEngineWrap.instantiate(tmpl);
    }
    else if(GlobalNS.AssetUniqueId.eAssetUId_PanelFadeoutEntity == assetUniqueId)
    {
        tmpl = GlobalNS.Ctx.msInstance.mAssetRef.getPanelFadeoutPrefab();
        ret = GlobalNS.UtilEngineWrap.instantiate(tmpl);
    }
    else if(GlobalNS.AssetUniqueId.eAssetUId_BottomSparkStartEntity == assetUniqueId)
    {
        tmpl = GlobalNS.Ctx.msInstance.mAssetRef.getBottomSparkStartEntityPrefab();
        ret = GlobalNS.UtilEngineWrap.instantiate(tmpl);
    }

    return ret;
}