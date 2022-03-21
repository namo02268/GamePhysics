#pragma once

#include "Window.h"

class SceneWindow : public Window {
public:
	SceneWindow(int width, int height, const char* title);
	~SceneWindow() = default;

	void update();
	void draw(unsigned int renderTexture);
};