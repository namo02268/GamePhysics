#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include "ECS_def.h"

class Entity {
private:
	EntityID m_id;

public:
	Entity(EntityID id) : m_id(id) {}
	~Entity() = default;
	EntityID GetID() { return m_id; }
};
