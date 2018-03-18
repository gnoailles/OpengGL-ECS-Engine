#pragma once
#include "GameObject.h"

class Player : public GameObject<Player>
{
public:
	Player(GAMEOBJECT_INIT_PARAMS);
	~Player();
};

