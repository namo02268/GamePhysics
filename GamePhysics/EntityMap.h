#pragma once
#include <unordered_map>
#include <array>

#include "Entity.h"
#include "ECS_def.h"

class EntityMap {
private:
	std::unordered_map<Entity, ComponentInstance> m_entityToInstance;
	std::array<Entity, MAX_COMPONENTS_ARRRAY> m_instanceToEntity;

public:
	Entity getEntity(ComponentInstance i) { return m_instanceToEntity[i]; }
	ComponentInstance getInstance(Entity e) { return m_entityToInstance[e]; }

	void add(Entity& e, ComponentInstance i) {
		m_entityToInstance.insert({ e, i });
		m_instanceToEntity[i] = e;
	}

	void update(Entity& e, ComponentInstance i) {
		m_entityToInstance[e] = i;
		m_instanceToEntity[i] = e;
	}
	void remove(Entity& e) { m_entityToInstance.erase(e); }
};