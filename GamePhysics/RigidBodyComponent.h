#pragma once
#include <glm/glm.hpp>

#include "Component.h"

class RigidBodyComponent : public Component {
public:
	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 force = glm::vec3(0.0f);

	float mass = 0.1f;
	float restitution = 1.0f;
	float staticFriction = 0.2f;
	float dynamicFriction = 0.1f;

	bool isGravity = false;
	bool isStatic = false;

public:
	RigidBodyComponent() {}
	RigidBodyComponent(bool isGravity, bool isStatic) : isGravity(isGravity), isStatic(isStatic) {}
};
