#pragma once

#include "Component.h"
#include "SphereCollider.h"


class SphereColliderComponent : public Component {
public:
	Collider* collider;

public:
	SphereColliderComponent(glm::vec3 center, float radius) {
		collider = new SphereCollider(center, radius);
	}

	~SphereColliderComponent() {
		delete collider;
	}
};