#pragma once
#include <glm/glm.hpp>

#include "Component.h"
#include "Collider.h"


class CollisionComponent : public Component {
public:
	Collider* collider;

public:
	CollisionComponent(Collider* collider) : collider(collider) {}
};
