local M = GlobalNS.StaticClass();
local this = M;
M.clsName = "UtilMath";
GlobalNS[M.clsName] = M;

function M.floor(value)
	return math.floor(value);
end

function M.ceil(value)
    return math.ceil(value);
end

function M.getMassByRadius(radius)
    return math.pow(radius, GlobalNS.CSSystem.Ctx.msInstance.mSnowBallCfg.mRealMassFactor);
end

function M.getRadiusByMass(mass)
    return math.pow(mass, 1/GlobalNS.CSSystem.Ctx.msInstance.mSnowBallCfg.mRealMassFactor);
end

function M.keepTwoDecimalPlaces(decimal)
    decimal = decimal * 100;
    if decimal % 1 >= 0.5 then 
        decimal=math.ceil(decimal);
    else
        decimal=math.floor(decimal);
    end
    return  decimal * 0.01;
end

--客户端显示质量
function M.getShowMass(radius)
    local showmass = "1毫克";
    local k = GlobalNS.CSSystem.Ctx.msInstance.mSnowBallCfg.mMassFactor;

    local _yt = math.pow((radius / math.pow(1000 * 1000 * 1000 * 10000 * 10000, 1/k)), k); --亿t
    if _yt >= 1 then
        showmass = string.format("%0.1f亿吨", _yt);
        return showmass;
    end

    local _wt = math.pow((radius / math.pow(1000 * 1000 * 1000 * 10000, 1/k)), k); --万t
    if _wt >= 1 then
        showmass = string.format("%0.1f万吨", _wt);
        return showmass;
    end

    local _t = math.pow((radius / math.pow(1000 * 1000 * 1000, 1/k)), k); --t
    if _t >= 1 then
        showmass = string.format("%0.1f吨", _t);
        return showmass;
    end

    local _kg = math.pow((radius / math.pow(1000 * 1000, 1/k)), k); --kg
    if _kg >= 1 then
        showmass = string.format("%0.1f千克", _kg);
        return showmass;
    end

    local _g = math.pow((radius / math.pow(1000, 1/k)), k); --g
    if _g >= 1 then
        showmass = string.format("%0.1f克", _g);
        return showmass;
    end

    local _mg = math.pow((radius), k); --mg
    showmass = string.format("%0.1f毫克", _mg);

    return showmass;
end

return M;