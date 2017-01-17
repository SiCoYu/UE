#pragma once

#include "PlayerPawnDataBase.h"

/**
 * @brief https://wiki.unrealengine.com/Spawn_Different_Pawns_For_Every_Player
 */

struct TPPlayerPawnData : public PlayerPawnDataBase
{
	int32 Type;
};