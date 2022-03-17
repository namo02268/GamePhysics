#pragma once

#include <vector>

#include "Entity.h"
#include "ECS_def.h"
#include "EventHandler.h"

class Scene;

class System {
protected:
	std::vector<Entity> m_entityArray;

public:
	Scene* m_parentScene;
	EventHandler* m_eventHandler;
	ComponentFamily m_requiredComponent;

public:
	virtual ~System() {}

	virtual void init() = 0;

	virtual void update(float dt) = 0;

	virtual void draw() = 0;

	void addEntity(Entity& e) {
		m_entityArray.emplace_back(e);
	}

	void removeEntity(Entity& e) {
		for (auto itr = m_entityArray.begin(); itr != m_entityArray.end(); ++itr) {
			Entity e_itr = *itr;
			if (e_itr == e) {
				m_entityArray.erase(itr);
				return;
			}
		}
	}
};