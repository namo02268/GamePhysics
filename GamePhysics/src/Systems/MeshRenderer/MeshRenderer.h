#pragma once

#include "ECS/System.h"
#include "Resources/Shader/Shader.h"

class MeshRenderer : public System {
private:
	Shader* m_shader;
	glm::quat oldQuat = glm::quat(glm::vec3(0.0f));
	glm::vec3 oldRadians = glm::vec3(0.0f);

public:
	MeshRenderer(Shader* shader);
	~MeshRenderer();

	void init() override;
	void update(float dt) override;
	void draw() override;
};

