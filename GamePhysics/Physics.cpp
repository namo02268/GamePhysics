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
	m_eventHandler->subscribe(this, &Physics::onCollisionEvent);
}

void Physics::update(float dt) {
	dt /= 10;
	for (auto& e : m_entityArray) {
		auto transfromComponent = m_parentScene->getComponent<TransformComponent>(e);
		auto collisionComponent = m_parentScene->getComponent<RigidBodyComponent>(e);

		collisionComponent->force += collisionComponent->mass * m_gravity;

		collisionComponent->velocity += collisionComponent->force / collisionComponent->mass * dt;
		transfromComponent->position += collisionComponent->velocity * dt;

		collisionComponent->force = glm::vec3(0.0f);
	}
}

void Physics::draw() {

}

void Physics::onCollisionEvent(CollisionEvent* collision) {
	auto a_trans = m_parentScene->getComponent<TransformComponent>(collision->a);
	auto b_trans = m_parentScene->getComponent<TransformComponent>(collision->b);
//	auto& a_rigid = m_parentScene->getComponent<RigidBodyComponent>(collision->a);
//	auto& b_rigid = m_parentScene->getComponent<RigidBodyComponent>(collision->b);

	/*
	float aInvMass = a_rigid.mass;
	float bInvMass = b_rigid.mass;

	glm::vec3 resolution = collision->points.B - collision->points.A;

	const float percent = 0.8f;
	const float slop = 0.01f;

	glm::vec3 correction = collision->points.Normal * percent
		* fmax(resolution.length() - slop, 0.0f)
		/ (aInvMass + bInvMass);
		*/
//	a_trans.position -= aInvMass * correction;
//	b_trans.position += bInvMass * correction;

}