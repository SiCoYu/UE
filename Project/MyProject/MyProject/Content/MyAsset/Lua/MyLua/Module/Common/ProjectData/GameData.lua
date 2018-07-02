local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "GameData";
GlobalNS[M.clsName] = M;

function M:ctor(...)
    self.isRelogin = false; --是否重新登录游戏

    self.ranklistCount = 0; --结算排行数量
    self.myRank = 0; --自己结算时排名
    self.rankinfolist = {}; --结算排行榜

    self.reliveTime = 0; --复活倒计时
    self.enemyName = 0; --敌人名称
    self.iskilledbyself = false; --自杀

    self.mTimer = GlobalNS.new(GlobalNS.DaoJiShiTimer);

    self.mMessageType = 1; --消息类型：1.弹出框 2.滚动提示
    self.mMessageText = ""; --消息内容
    self.mMessageMethond = 0; --对应调用方法

    self.mMyScore = 0;
    self.top10ranklist = {}; --top10 排行
    self.top10Count = 0;  --top10 个数
    self.top10_myrank = 1;
    self.mMyName = "";
end

function M:dtor()
    
end

function M:setRankInfoList(args)
    local ranklist = args[0];
    self.myRank = args[1];
    self.ranklistCount = args[2];
    for i=1, self.ranklistCount do
        self.rankinfolist[i] = 
        {
            m_rank = ranklist[i-1].rank;
            m_eid = ranklist[i-1].eid;
            m_name = ranklist[i-1].name;
            m_killnum = ranklist[i-1].killnum;
            m_swallownum = ranklist[i-1].swallownum;
            m_avatarindex = ranklist[i-1].avatarindex;
        };
    end

    local form = GCtx.mUiMgr:getForm(GlobalNS.UiFormId.eUiRankListPanel);
    if nil ~= form and form.mIsReady then
        form:updateUIData();
    end
end

function M:setTop10RankList(args)
    local top10 = args[0];
    self.top10_myrank = args[1];
    self.top10Count = args[2];
    self.mMyName = args[3];
    for i=1, self.top10Count do
        self.top10ranklist[i] = 
        {
            m_rank = top10[i-1].rank;
            m_eid = top10[i-1].eid;
            m_name = top10[i-1].name;
        };
    end

    if GCtx.mUiMgr:hasForm(GlobalNS.UiFormId.eUiTopXRankPanel) then
        local form = GCtx.mUiMgr:getForm(GlobalNS.UiFormId.eUiTopXRankPanel);
        if nil ~= form and form.mIsReady then            
            form:updateUIData();
        end
    end
end

--每局游戏倒计时
function M:setGameTime(totalTime)
	self.mTimer.mIsDisposed = false;
    self.mTimer:setTotalTime(totalTime);
    self.mTimer:setFuncObject(self, self.onTick, 0);
    self.mTimer:Start();
end

function M:onTick(dispObj, eventId)
    local lefttime = GlobalNS.UtilMath.ceil(self.mTimer:getLeftRunTime());
	if GCtx.mUiMgr:hasForm(GlobalNS.UiFormId.eUiPlayerDataPanel) then
        local form = GCtx.mUiMgr:getForm(GlobalNS.UiFormId.eUiPlayerDataPanel);
        if nil ~= form and form.mIsReady then
            form:refreshLeftTime(lefttime);
        end
    end
end

function M:ShowMessageBox(msg)
    self.mMessageType = 1;
    self.mMessageText = msg;
    GCtx.mUiMgr:loadAndShow(GlobalNS.UiFormId.eUiMessagePanel);
end

function M:ShowRollMessage(msg)
    self.mMessageType = 2;
    self.mMessageText = msg;
    GCtx.mUiMgr:loadAndShow(GlobalNS.UiFormId.eUiMessagePanel);
end

function M:returnStartGame()
    GCtxExt.mPlayerData.mGameData.isRelogin = true;
    self:clearResource();
    GlobalNS.CSSystem.Ctx.msInstance.mNetEventHandle:Disconnect();
	GCtx.mUiMgr:loadAndShow(GlobalNS.UiFormId.eUiStartGame);
    --GlobalNS.CSSystem.Ctx.msInstance.mModuleSys:unloadModule(GlobalNS.CSSystem.ModuleId.GAMEMN);
    GlobalNS.CSSystem.Ctx.msInstance.mModuleSys:loadModule(GlobalNS.CSSystem.ModuleId.LOGINMN);
end

function M:clearResource()
    self.mTimer:Stop();
    GlobalNS.CSSystem.Ctx.msInstance.mPlayerMgr:dispose();
    GlobalNS.CSSystem.Ctx.msInstance.mSnowBlockMgr:dispose();
    GlobalNS.CSSystem.Ctx.msInstance.mComputerBallMgr:dispose();
    GlobalNS.CSSystem.Ctx.msInstance.mPlayerSnowBlockMgr:dispose();
    GlobalNS.CSSystem.Ctx.msInstance.mFlyBulletMgr:dispose();
    GlobalNS.CSSystem.Ctx.msInstance.mFlyBulletFlockMgr:dispose();
	GlobalNS.CSSystem.Ctx.msInstance.mHudSystem:dispose();

    GCtx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiPlayerDataPanel);
    GCtx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiOptionPanel);
    GCtx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiTopXRankPanel);
    GCtx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiRelivePanel);
end

return M;