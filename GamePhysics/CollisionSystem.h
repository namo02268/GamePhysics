#pragma once
#include "System.h"
#include "CollisionPoints.h"

struct Collision {
	Entity* ObjA;
	Entity* ObjB;
	CollisionPoints Points;
};

class CollisionSystem : public System {
private:

public:
	CollisionSystem();
	~CollisionSystem();

	void init() override;
	void update(float dt) override;
	void draw() override;
};
