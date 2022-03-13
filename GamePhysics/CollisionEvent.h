#pragma once

#include "EventHandler.h"
#include "Entity.h"
#include "CollisionPoints.h"

class CollisionEvent : public Event {
public:
	Entity a;
	Entity b;
	CollisionPoints points;

public:
	CollisionEvent(Entity a, Entity b, CollisionPoints points) : a(a), b(b), points(points) {}
	~CollisionEvent() {}
};


