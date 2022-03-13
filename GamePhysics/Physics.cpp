#include "Physics.h"
#include "Scene.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"

Physics::Physics() {
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<RigidBodyComponent>();
	m_requiredComponent[family] = true;
}

Physics::~Physics() {

}

void Physics::init() {

}

void Physics::update(float dt) {
	dt /= 10;
	for (auto& e : m_entityArray) {
		auto& transfromComponent = m_parentScene->getComponent<TransformComponent>(e);
		auto& collisionComponent = m_parentScene->getComponent<RigidBodyComponent>(e);

		collisionComponent.force += collisionComponent.mass * m_gravity;

		collisionComponent.velocity += collisionComponent.force / collisionComponent.mass * dt;
		transfromComponent.position += collisionComponent.velocity * dt;

		collisionComponent.force = glm::vec3(0.0f);
	}
}

void Physics::draw() {

}