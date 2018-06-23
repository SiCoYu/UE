using SDK.Lib;
using Game.UI;

namespace Game.Game
{
    public class GameModule : IGameModule
    {
        public GameRouteNotify mGameRouteNotify;
        public GameNetNotify mGameNetNotify;
        protected GotoScene mGotoScene;
        protected GameUiEventNotify mGameUiEventNotify;
        protected GameSceneLogicNotify mGameSceneLogicNotify;

        public GameModule()
        {

        }

        public void init()
        {
            this.registerScriptType();
            this.initGVar();
            this.loadGameScene();
        }

        public void dispose()
        {
            if(null != this.mGameNetNotify)
            {
                this.mGameNetNotify.dispose();
                this.mGameNetNotify = null;
            }
            if(null != this.mGameRouteNotify)
            {
                this.mGameRouteNotify.dispose();
                this.mGameRouteNotify = null;
            }
            if (null != this.mGotoScene)
            {
                this.mGotoScene.dispose();
                this.mGotoScene = null;
            }
            if(null != this.mGameUiEventNotify)
            {
                if (null != Ctx.msInstance.mGlobalDelegate)
                {
                    Ctx.msInstance.mGlobalDelegate.mFormCodeLoadedDispatch.removeEventHandle(
                        this.mGameUiEventNotify,
                        this.mGameUiEventNotify.onCodeFormLoaded,
                        0
                    );
                    Ctx.msInstance.mGlobalDelegate.mFormWidgetLoadedDispatch.removeEventHandle(
                        this.mGameUiEventNotify,
                        this.mGameUiEventNotify.onWidgetLoaded,
                        0
                    );
                }

                this.mGameUiEventNotify.dispose();
                this.mGameUiEventNotify = null;
            }
            if(null != CtxExt.msInstance.mSceneEventNotify)
            {
                CtxExt.msInstance.mSceneEventNotify = null;
            }

            this.unregisterScriptType();
        }

        public void initGVar()
        {
            this.mGotoScene = new GotoScene();

            // 游戏逻辑处理
            this.mGameUiEventNotify = new GameUiEventNotify();

            Ctx.msInstance.mGlobalDelegate.mFormCodeLoadedDispatch.addEventHandle(
                this.mGameUiEventNotify,
                this.mGameUiEventNotify.onCodeFormLoaded,
                0
            );
            Ctx.msInstance.mGlobalDelegate.mFormWidgetLoadedDispatch.addEventHandle(
                this.mGameUiEventNotify,
                this.mGameUiEventNotify.onWidgetLoaded,
                0
            );

            this.mGameNetNotify = new GameNetNotify();
            this.mGameNetNotify.init();
            Ctx.msInstance.mNetCmdNotify.addOneNofity(this.mGameNetNotify);

            this.mGameRouteNotify = new GameRouteNotify();
            this.mGameRouteNotify.init();
            Ctx.msInstance.mMsgRouteNotify.addOneNotify(this.mGameRouteNotify);

            Ctx.msInstance.mNetCmdNotify.isStopNetHandle = false;     // 开始网络消息处理
            CtxExt.msInstance.mSceneEventNotify = new GameSceneEventNotify();

            this.mGameSceneLogicNotify = new GameSceneLogicNotify();

            this.mGotoScene.init();
            this.mGotoScene.addSceneHandle();
        }

        public void loadGameScene()
        {
            //this.mGotoScene.loadSceneByLevelName("TestScene.unity");

            if (MacroDef.DISABLE_TEST_SCENE)
            {
                //this.mGotoScene.loadSceneByLevelName("NewWorldTest.unity");
                this.mGotoScene.loadSceneByMapId((int)MapIdCV.eCommonMap);
            }
            else
            {
                this.mGotoScene.loadSceneByLevelName("TestShader.unity");
            }
        }

        protected void registerScriptType()
        {
            Ctx.msInstance.mScriptDynLoad.registerScriptType("Game.UI.UiBlurBg", typeof(UiBlurBg));
            Ctx.msInstance.mScriptDynLoad.registerScriptType("Game.UI.UiTest", typeof(UiTest));
            Ctx.msInstance.mScriptDynLoad.registerScriptType("Game.UI.UiTerrainEdit", typeof(UiTerrainEdit));
            Ctx.msInstance.mScriptDynLoad.registerScriptType("Game.UI.UiPack", typeof(UiPack));
            Ctx.msInstance.mScriptDynLoad.registerScriptType("Game.UI.UiJoyStick", typeof(UiJoyStick));
            Ctx.msInstance.mScriptDynLoad.registerScriptType("Game.UI.UiForwardForce", typeof(UiForwardForce));
        }

        protected void unregisterScriptType()
        {
            Ctx.msInstance.mScriptDynLoad.unregisterScriptType("Game.UI.UIBlurBg");
            Ctx.msInstance.mScriptDynLoad.unregisterScriptType("Game.UI.UITest");
            Ctx.msInstance.mScriptDynLoad.unregisterScriptType("Game.UI.UITerrainEdit");
            Ctx.msInstance.mScriptDynLoad.unregisterScriptType("Game.UI.UIPack");
            Ctx.msInstance.mScriptDynLoad.unregisterScriptType("Game.UI.UIJoyStick");
            Ctx.msInstance.mScriptDynLoad.unregisterScriptType("Game.UI.UIForwardForce");
        }
    }
}