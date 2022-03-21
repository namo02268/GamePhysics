#pragma once

#include "Scene.h"
#include "ECS_def.h"

#include "ComponentEditors.h"

class Editor {
private:
	Scene* m_parentScene;
	std::array<std::unique_ptr<ComponentEditorBase>, MAX_COMPONENTS_FAMILY> m_componentGUIs;
	ComponentFamily m_componentGUIbit;

public:
	Editor(Scene* scene) : m_parentScene(scene) { init(); }
	~Editor() = default;

	void init();
	void draw();
};