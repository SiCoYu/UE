MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiRankListPanel.RankListPanelNS");
MLoader("MyLua.Ui.UiRankListPanel.RankListPanelData");
MLoader("MyLua.Ui.UiRankListPanel.RankListPanelCV");

local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiRankListPanel";
GlobalNS.RankListPanelNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUiRankListPanel;
	self.mData = GlobalNS.new(GlobalNS.RankListPanelNS.RankListPanelData);
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);
    --返回游戏按钮
	self.mBackGameBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mBackGameBtn:addEventHandle(self, self.onBtnClk, 0);

    --listitem prefab
    self.mListitem_prefab = GlobalNS.new(GlobalNS.AuxPrefabLoader);
	self.mListitem_prefab:setIsNeedInsPrefab(false);

    --listitems数组
    self.listitems = { };
    self.avatarimages = { };
    self.myavatar = nil;
    self.honerimages = {};
    self.myhoner = nil;
end

function M:onReady()
    M.super.onReady(self);
    self.RankBG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, "RankListBG");
	self.mBackGameBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(
			self.RankBG, 
			GlobalNS.RankListPanelNS.RankListPanelPath.BtnBackGame)
		);

    --获取ScrollRect的GameObject对象
    self.mScrollRect = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.RankBG, "ScrollRect");
    local viewport =  GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mScrollRect, "Viewport");
    --获取ScrollRect下Content中的RectTransform组件
    self.mRankContent = GlobalNS.UtilEngineWrap.getComByPath(viewport, "Content", "RectTransform");
    
    --获取MyRank的GameObject对象
    self.mMyRankArea = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.RankBG, "MyRank");

    --加载listitem prefab
	self.mListitem_prefab:asyncLoad("UI/UiRankListPanel/ListItem.prefab", self, self.onPrefabLoaded, nil); 
    
    self:updateUIData();
end

function M:onShow()
    M.super.onShow(self);    
end

function M:onHide()
    M.super.onHide(self);
end

function M:onExit()
    M.super.onExit(self);
end

function M:onBtnClk()
    if self.myavatar ~= nil then
        self.myavatar:dispose();
        self.myavatar = nil;
    end
    for i=1, #self.avatarimages do
        self.avatarimages[i]:dispose();
    end
    self.avatarimages = {};

    if self.myhoner ~= nil then
        self.myhoner:dispose();
        self.myhoner = nil;
    end
    for i=1, #self.honerimages do
        self.honerimages[i]:dispose();
    end
    self.honerimages = {};
    self.mListitem_prefab:dispose();
    self:exit();
    
    GCtxExt.mPlayerData.mGameData:returnStartGame();
end

function M:onPrefabLoaded(dispObj)
    --获取listitemprefab对象
    self.mListitemPrefab = self.mListitem_prefab:getPrefabTmpl();
    
    for i=1, GCtxExt.mPlayerData.mGameData.ranklistCount do
        --用listitemprefab生成GameObject对象
        local listitem = GlobalNS.UtilEngineWrap.Instantiate(self.mListitemPrefab);
        listitem.transform.parent = self.mRankContent;
        listitem.transform.localScale = Vector3.New(1.0, 1.0, 1.0);

        listitem.name = "Item" .. i;

        self.listitems[i] = listitem;
    end

    --滚动到起始位置，默认会在中间
    GlobalNS.UtilEngineWrap.GetComponent(self.mScrollRect, "ScrollRect").verticalNormalizedPosition = 1;

    self:updateUIData();
end

--我的排名数据
function M:SetMyRankInfo()
    for i=1, GCtxExt.mPlayerData.mGameData.ranklistCount do
        if(GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_rank == GCtxExt.mPlayerData.mGameData.myRank) then

            --荣誉
            local myHoner = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mMyRankArea, "Honer");
            if GCtxExt.mPlayerData.mGameData.myRank > 3 then
                myHoner:SetActive(false);
            else
                myHoner:SetActive(true);
                self.myhoner = GlobalNS.new(GlobalNS.AuxImage);
                self.myhoner:setSelfGo(myHoner);
                if GCtxExt.mPlayerData.mGameData.myRank == 1 then
					self.myhoner:setSpritePath("DefaultSkin/SkyWarSkin/rank1.png", "rank1");
                    --self.myhoner:setSpritePath("DefaultSkin/GameOption/GameOption_RGB.png", "cup_gold");
                elseif GCtxExt.mPlayerData.mGameData.myRank == 2 then
					self.myhoner:setSpritePath("DefaultSkin/SkyWarSkin/rank2.png", "rank2");
                    --self.myhoner:setSpritePath("DefaultSkin/GameOption/GameOption_RGB.png", "cup_yin");
                else
					self.myhoner:setSpritePath("DefaultSkin/SkyWarSkin/rank3.png", "rank3");
                    --self.myhoner:setSpritePath("DefaultSkin/GameOption/GameOption_RGB.png", "cup_tong");
                end
            end

            --排名
            local myRank = GlobalNS.UtilEngineWrap.getComByPath(self.mMyRankArea, "Rank", "Text");
            myRank.text = "" .. i;

            --头像
            local myAvatar = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mMyRankArea, "Avatar");
            self.myavatar = GlobalNS.new(GlobalNS.AuxImage);
            self.myavatar:setSelfGo(myAvatar);
            local avatarindex = GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_avatarindex;
            if avatarindex == 0 then
                avatarindex = 1;
            end
			self.myavatar:setSpritePath("DefaultSkin/Avatar/"..avatarindex..".png", GlobalNS.UtilStr.tostring(avatarindex));
            --self.myavatar:setSpritePath("DefaultSkin/Avatar/Avatar_RGB.png", GlobalNS.UtilStr.tostring(avatarindex));

            --用户名
            local myName = GlobalNS.UtilEngineWrap.getComByPath(self.mMyRankArea, "Name", "Text");
            myName.text = GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_name;

            --[[
            --本轮质量
            local myMass = GlobalNS.UtilEngineWrap.getComByPath(self.mMyRankArea, "Mass", "Text");
            local radius = GlobalNS.UtilMath.getRadiusByMass(GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_radius); --服务器传过来的是质量
            myMass.text = GlobalNS.UtilMath.getShowMass(radius);
            ]]--

            --吞食数量
            local mySwallowNum = GlobalNS.UtilEngineWrap.getComByPath(self.mMyRankArea, "SwallowNum", "Text");
            mySwallowNum.text = GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_swallownum;

            break;
        end
    end
end

--排行榜数据
function M:SetTopXRankInfo()
    for i=1, GCtxExt.mPlayerData.mGameData.ranklistCount do
        local listitem = self.listitems[i].transform;
        
        --荣誉
        local Honer = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.listitems[i], "Honer");
        if i > 3 then
            Honer:SetActive(false);
        else
            Honer:SetActive(true);
            local honer = GlobalNS.new(GlobalNS.AuxImage);
            honer:setSelfGo(Honer);
            if i == 1 then
				honer:setSpritePath("DefaultSkin/SkyWarSkin/rank1.png", "rank1");
                --honer:setSpritePath("DefaultSkin/GameOption/GameOption_RGB.png", "cup_gold");
            elseif i == 2 then
				honer:setSpritePath("DefaultSkin/SkyWarSkin/rank2.png", "rank2");
                --honer:setSpritePath("DefaultSkin/GameOption/GameOption_RGB.png", "cup_yin");
            else
				honer:setSpritePath("DefaultSkin/SkyWarSkin/rank3.png", "rank3");
                --honer:setSpritePath("DefaultSkin/GameOption/GameOption_RGB.png", "cup_tong");
            end
            self.honerimages[i] = honer;
         end

        --排名
        local Rank = GlobalNS.UtilEngineWrap.getComByPath(listitem, "Rank", "Text");
        Rank.text = "" .. i;
        if GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_rank == GCtxExt.mPlayerData.mGameData.myRank then
            Rank.text = "<color=#32c832ff>"..i.."</color>";
        end

        --头像
        local Avatar = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.listitems[i], "Avatar");
        local avatarImage = GlobalNS.new(GlobalNS.AuxImage);
        avatarImage:setSelfGo(Avatar);
        local avatarindex = GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_avatarindex;
        if avatarindex == 0 then
            if GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_rank == GCtxExt.mPlayerData.mGameData.myRank then
                avatarindex = 1;
            else
                local _time = os.clock();
                math.randomseed(_time + i);
                avatarindex = math.random(1, 4);
            end
        end
		avatarImage:setSpritePath("DefaultSkin/Avatar/"..avatarindex..".png", GlobalNS.UtilStr.tostring(avatarindex));
        --avatarImage:setSpritePath("DefaultSkin/Avatar/Avatar_RGB.png", GlobalNS.UtilStr.tostring(avatarindex));
        self.avatarimages[i] = avatarImage;

        --用户名
        local Name = GlobalNS.UtilEngineWrap.getComByPath(listitem, "Name", "Text");
        Name.text = GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_name;
        if GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_rank == GCtxExt.mPlayerData.mGameData.myRank then
            Name.text = "<color=#32c832ff>"..GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_name.."</color>";
        end

        --[[
        --本轮质量
        local Mass = GlobalNS.UtilEngineWrap.getComByPath(listitem, "Mass", "Text");
        local radius = GlobalNS.UtilMath.getRadiusByMass(GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_radius); --服务器传过来的是质量
        Mass.text = GlobalNS.UtilMath.getShowMass(radius);
        if GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_rank == GCtxExt.mPlayerData.mGameData.myRank then
            Mass.text = "<color=#32c832ff>"..GlobalNS.UtilMath.getShowMass(radius).."</color>";
        end
        ]]--

        --吞食数量
        local SwallowNum = GlobalNS.UtilEngineWrap.getComByPath(listitem, "SwallowNum", "Text");
        SwallowNum.text = GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_swallownum;
        if GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_rank == GCtxExt.mPlayerData.mGameData.myRank then
            SwallowNum.text = "<color=#32c832ff>"..GCtxExt.mPlayerData.mGameData.rankinfolist[i].m_swallownum.."</color>";
        end
    end
end

function M:updateUIData()
    if #self.listitems == GCtxExt.mPlayerData.mGameData.ranklistCount then        
        self:SetMyRankInfo();
        self:SetTopXRankInfo();
    end
end

return M;