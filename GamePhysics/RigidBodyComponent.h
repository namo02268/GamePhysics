#pragma once
#include <glm/glm.hpp>

#include "Component.h"

class RigidBodyComponent : public Component {
public:
	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 force = glm::vec3(0.0f);
	float mass = 1.0f;

public:
	RigidBodyComponent() {}
	RigidBodyComponent(glm::vec3 velocity, glm::vec3 force, float mass) : velocity(velocity), force(force), mass(mass) {}
};
