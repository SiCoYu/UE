#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 玩家管理器
 */
public class PlayerMgr : EntityMgrBase
{
	protected PlayerMain mHero;
	protected UniqueStrIdGen mChildUniqueStrIdGen;

	public PlayerTarget mPlayerTarget;
	protected TimerItemBase mRepeatTimer;

	protected int mCurNum;
	protected int mMaxNum;

	protected bool mIsDoFire; // 长按连续射击
	protected float mFireTimeStamp;  // 射击时间戳

	protected TimeInterval mTimeInterval;
	protected TimerItemBase mTimer;

	public PlayerMgr()
	{
		this.mUniqueStrIdGen = new UniqueStrIdGen(UniqueStrIdGen.PlayerPrefix, 0);
		this.mChildUniqueStrIdGen = new UniqueStrIdGen(UniqueStrIdGen.PlayerChildPrefix, 0);

		this.mCurNum = 0;
		this.mMaxNum = 10;
		this.mIsDoFire = false;
		this.mFireTimeStamp = 0;

		this.mTimeInterval = new TimeInterval();
		this.mTimeInterval.setInterval(0.05f);
	}

	override protected void _onTickExec(float delta, TickMode tickMode)
	{
		if (TickMode.eTM_Update == tickMode)
		{
			int idx = 0;
			int count = this.mSceneEntityList.count();
			SceneEntityBase entity = null;

			while (idx < count)
			{
				entity = this.mSceneEntityList[idx];

				if (Ctx.msInstance.mConfig.mIsActorMoveUseFixUpdate)
				{
					if (EntityType.ePlayerMain != entity.getEntityType())
					{
						if (!entity.isClientDispose())
						{
							entity.onTick(delta, tickMode);
						}
					}
				}
				else
				{
					if (!entity.isClientDispose())
					{
						entity.onTick(delta, tickMode);
					}
				}

				++idx;
			}
		}
		else if(TickMode.eTM_LateUpdate == tickMode)
		{
			this.postUpdate();
		}
	}

	private bool calcArrowPos(int index, uint topx_id, ref bool isShowArrow, ref UnityEngine.Vector2 arrow_pos, ref UnityEngine.Quaternion arrow_rotation)
	{
		UnityEngine.Vector2 old_pos = arrow_pos;
		bool old_show = isShowArrow;
		
		return false;
	}

	private void calcArrowPos(UnityEngine.Vector2 top1_UI_pos, UnityEngine.Vector2 me_UI_pos, ref bool isShowArrow, ref UnityEngine.Vector2 arrow_pos)
	{
		float offset = 40.0f;
		//float h_height = UtilEngineWrap.getScreenHeight() / 2.0f;
		//float h_width = UtilEngineWrap.getScreenWidth() / 2.0f;

		float h_width = Ctx.msInstance.mUiMgr.getCanvasSize(UiCanvasId.eFirstCanvas).x / 2.0f;
		float h_height = Ctx.msInstance.mUiMgr.getCanvasSize(UiCanvasId.eFirstCanvas).y / 2.0f;

		isShowArrow = true;
		if (UtilMath.isEqualFloat(top1_UI_pos.x , me_UI_pos.x))
		{
			//在垂直线上
			if (top1_UI_pos.y > me_UI_pos.y)//上边界
			{
				arrow_pos = new UnityEngine.Vector2(top1_UI_pos.x, h_height - offset);
			}
			else
			{
				arrow_pos = new UnityEngine.Vector2(top1_UI_pos.x, -h_height + offset);
			}
		}
		else if(UtilMath.isEqualFloat(top1_UI_pos.y, me_UI_pos.y))
		{
			//在水平线上
			if (top1_UI_pos.x > me_UI_pos.x)//右边界
			{
				arrow_pos = new UnityEngine.Vector2(top1_UI_pos.x, h_width - offset);
			}
			else
			{
				arrow_pos = new UnityEngine.Vector2(top1_UI_pos.x, -h_width + offset);
			}
		}
		else
		{
			// y = k * x （自己一直在原点(0,0)，所以不需要b，过原点的直线方程）
			float k = top1_UI_pos.y / top1_UI_pos.x;

			//第一象限
			if(top1_UI_pos.x > 0 && top1_UI_pos.y > 0)
			{
				//与上边界交点
				float x = (h_height - offset) / k;
				if(x < h_width - offset)
				{
					arrow_pos = new UnityEngine.Vector2(x, h_height - offset);
					return;
				}

				//不与上边界相交，一定跟右边界相交
				float y = k * (h_width - offset);
				arrow_pos = new UnityEngine.Vector2(h_width - offset, y);
			}

			//第二象限
			if (top1_UI_pos.x < 0 && top1_UI_pos.y > 0)
			{
				//与上边界交点
				float x = (h_height - offset) / k;
				if (x > -h_width + offset)
				{
					arrow_pos = new UnityEngine.Vector2(x, h_height - offset);
					return;
				}

				//不与上边界相交，一定跟左边界相交
				float y = k * (-h_width + offset);
				arrow_pos = new UnityEngine.Vector2(-h_width + offset, y);
			}

			//第三象限
			if (top1_UI_pos.x < 0 && top1_UI_pos.y < 0)
			{
				//与下边界交点
				float x = (-h_height + offset) / k;
				if (x > -h_width + offset)
				{
					arrow_pos = new UnityEngine.Vector2(x, -h_height + offset);
					return;
				}

				//不与下边界相交，一定跟左边界相交
				float y = k * (-h_width + offset);
				arrow_pos = new UnityEngine.Vector2(-h_width + offset, y);
			}

			//第四象限
			if (top1_UI_pos.x > 0 && top1_UI_pos.y < 0)
			{
				//与下边界交点
				float x = (-h_height + offset) / k;
				if (x < h_width - offset)
				{
					arrow_pos = new UnityEngine.Vector2(x, -h_height + offset);
					return;
				}

				//不与下边界相交，一定跟右边界相交
				float y = k * (h_width - offset);
				arrow_pos = new UnityEngine.Vector2(h_width - offset, y);
			}
		}
	}

	public void postUpdate()
	{
	   
	}

	public PlayerMain createHero()
	{
		return new PlayerMain();
	}

	public void addHero(PlayerMain hero)
	{
		if (null != hero)
		{
			this.mHero = hero as PlayerMain;
			this.addPlayer(this.mHero);

			if (Ctx.msInstance.mConfig.mIsActorMoveUseFixUpdate)
			{
				Ctx.msInstance.mFixedTickMgr.addTick(this.mHero as ITickedObject);
			}
		}
	}

	public void removeHero()
	{
		if (null != this.mHero)
		{
			if (Ctx.msInstance.mConfig.mIsActorMoveUseFixUpdate && null != Ctx.msInstance.mFixedTickMgr)
			{
				Ctx.msInstance.mFixedTickMgr.removeTick(this.mHero as ITickedObject);
			}

			this.removePlayer(this.mHero);
			this.mHero = null;
		}
	}

	public PlayerMain getHero()
	{
		return this.mHero;
	}

	override public void init()
	{
		base.init();
	}

	public void addPlayer(Player player)
	{
		this.addEntity(player);
	}

	public void removePlayer(Player player)
	{
		this.removeEntity(player);
		--this.mMaxNum;
	}

	public string genChildNewStrId()
	{
		return this.mChildUniqueStrIdGen.genNewStrId();
	}

	public void createPlayerMain()
	{
		this.mHero = new PlayerMain();
		this.mHero.init();
		this.mHero.setDestPos(new UnityEngine.Vector3(50, 1.3f, 50f), true);
		this.mHero.setDestRotateEulerAngle(UtilMath.UnitQuat.eulerAngles, true);
	}
};

MY_END_NAMESPACE