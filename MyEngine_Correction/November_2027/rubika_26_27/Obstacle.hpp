#pragma once

#include "Entity.h"

class Obstacle : public Entity
{
public:
	Obstacle(std::string friendlyName = "");
	~Obstacle();
};