var GlobalNS = require("GlobalNS").GlobalNS;
require("ModuleLoad");
GlobalNS.MLoader("Enum");

var M = GlobalNS.Enum();
M.clsName = "TypeUniqueId";
GlobalNS[M.clsName] = M;

M.eTypeUId_Prefab = 0;