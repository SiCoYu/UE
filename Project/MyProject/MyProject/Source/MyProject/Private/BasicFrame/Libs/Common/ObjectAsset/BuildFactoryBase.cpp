var GlobalNS = require("GlobalNS").GlobalNS;

GlobalNS.MLoader("GObject");

var M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "BuildFactoryBase";
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