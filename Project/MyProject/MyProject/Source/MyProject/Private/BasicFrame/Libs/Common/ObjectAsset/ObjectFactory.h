var GlobalNS = require("GlobalNS").GlobalNS;

GlobalNS.MLoader("BuildFactoryBase");

var M = GlobalNS.Class(GlobalNS.BuildFactoryBase);
M.clsName = "ObjectFactory";
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
    return ret;
}