#pragma once

#include "System.h"
#include "Window.h"
#include "Scene.h"
#include "ECS_def.h"

#include "ComponentGUIs.h"

class GUI {
private:
	Scene* m_parentScene;
	Window* m_parentWindow;
	std::array<std::unique_ptr<ComponentGUIBase>, MAX_COMPONENTS_FAMILY> m_componentGUIs;
	ComponentFamily m_componentGUIbit;

public:
	GUI(Window* window, Scene* scene) : m_parentWindow(window), m_parentScene(scene) { init(); }
	~GUI();

	void init();
	void update();
	void draw();
};