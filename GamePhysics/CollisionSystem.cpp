#include "CollisionSystem.h"
#include "Scene.h"
#include "CollisionEvent.h"

#include "TransformComponent.h"
#include "CollisionComponent.h"

CollisionSystem::CollisionSystem() {
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<CollisionComponent>();
	m_requiredComponent[family] = true;
}

CollisionSystem::~CollisionSystem() {

}

void CollisionSystem::init() {

}

void CollisionSystem::update(float dt) {
	for (auto& a : m_entityArray) {
		for (auto& b : m_entityArray) {
			if (a.GetID() == b.GetID())
				break;
			auto a_trans = m_parentScene->getComponent<TransformComponent>(a);
			auto b_trans = m_parentScene->getComponent<TransformComponent>(b);
			auto a_col = m_parentScene->getComponent<CollisionComponent>(a);
			auto b_col = m_parentScene->getComponent<CollisionComponent>(b);
			CollisionPoints points = a_col->collider->TestCollision(
				a_trans,
				b_col->collider,
				b_trans);
			if (points.HasCollision) {
				CollisionEvent event(a, b, points);
				m_eventHandler->publish(&event);
			}
		}
	}
}

void CollisionSystem::draw() {

}