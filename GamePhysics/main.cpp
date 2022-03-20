#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Window.h"
#include "Scene.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "EventHandler.h"

#include "Renderer.h"
#include "CameraSystem.h"
#include "IBL.h"
#include "GUI.h"
#include "Physics.h"
#include "CollisionSystem.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"

#include "CameraComponent.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "MaterialComponent.h"
#include "GUIComponent.h"
#include "RigidBodyComponent.h"
#include "CollisionComponent.h"

int main() {
	Window window(800, 600, "Kikurage");

	//-------------------------------initialize scene-------------------------------//
	auto entityManager = std::make_unique<EntityManager>();
	auto eventHandler = std::make_unique<EventHandler>();
	Scene scene(std::move(entityManager), std::move(eventHandler));

	//-----------------------------------Resources-----------------------------------//
	stbi_set_flip_vertically_on_load(true);

	ResourceManager::LoadShaderFromFile("resources/shaders/Simple.vert", "resources/shaders/PBR_nonTexture.frag", nullptr, "PBR");
	ResourceManager::LoadShaderFromFile("resources/shaders/background.vert", "resources/shaders/background.frag", nullptr, "backgroundShader");
	ResourceManager::LoadMeshFromFile("resources/objects/suzanne/suzanne.obj", "suzanne");
	ResourceManager::LoadMeshFromFile("resources/objects/sphere/sphere.obj", "sphere");
	ResourceManager::LoadMeshFromFile("resources/objects/plane/plane.obj", "plane");

	//-----------------------------add systems to scene-----------------------------//
	// camera system
	auto cameraSystem = std::make_unique<CameraSystem>(&window);
	cameraSystem->addShader(ResourceManager::GetShader("PBR"));
	cameraSystem->addShader(ResourceManager::GetShader("backgroundShader"));
	scene.addSystem(std::move(cameraSystem));
	// renderer
	auto renderer = std::make_unique<Renderer>(ResourceManager::GetShader("PBR"));
	scene.addSystem(std::move(renderer));
	// IBL
	auto ibl = std::make_unique<IBL>(ResourceManager::GetShader("PBR"), ResourceManager::GetShader("backgroundShader"));
	scene.addSystem(std::move(ibl));
	// GUI
	auto gui = std::make_unique<GUI>(&window);
	scene.addSystem(std::move(gui));
	// Physics
	auto physics = std::make_unique<Physics>();
	scene.addSystem(std::move(physics));
	// Collision 
	auto collisionSystem = std::make_unique<CollisionSystem>();
	scene.addSystem(std::move(collisionSystem));

	//---------------------------------add entities---------------------------------//
	// camera
	auto cameraEntity = scene.createEntity();
	scene.addComponent<TransformComponent>(cameraEntity, glm::vec3(20.0f, 5.0f, 20.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	scene.addComponent<CameraComponent>(cameraEntity);
	scene.addComponent<GUIComponent>(cameraEntity);

	/*
	// sphere
	auto sphere1 = scene.createEntity();
	scene.addComponent<GUIComponent>(sphere1);
	scene.addComponent<TransformComponent>(sphere1, glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	scene.addComponent<MeshComponent>(sphere1, ResourceManager::GetMesh("sphere"));
	scene.addComponent<MaterialComponent>(sphere1);
	scene.addComponent<RigidBodyComponent>(sphere1, true, false);
	scene.addComponent<CollisionComponent>(sphere1, new SphereCollider(glm::vec3(0.0f), 1.0f));

	// sphere
	auto sphere2 = scene.createEntity();
	scene.addComponent<GUIComponent>(sphere2);
	scene.addComponent<TransformComponent>(sphere2, glm::vec3(0.0f, 6.0f, 3.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	scene.addComponent<MeshComponent>(sphere2, ResourceManager::GetMesh("sphere"));
	scene.addComponent<MaterialComponent>(sphere2);
	scene.addComponent<RigidBodyComponent>(sphere2, true, false);
	scene.addComponent<CollisionComponent>(sphere2, new SphereCollider(glm::vec3(0.0f), 1.0f));
	// sphere
	auto sphere3 = scene.createEntity();
	scene.addComponent<GUIComponent>(sphere3);
	scene.addComponent<TransformComponent>(sphere3, glm::vec3(0.0f, 10.0f, 6.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	scene.addComponent<MeshComponent>(sphere3, ResourceManager::GetMesh("sphere"));
	scene.addComponent<MaterialComponent>(sphere3);
	scene.addComponent<RigidBodyComponent>(sphere3, true, false);
	scene.addComponent<CollisionComponent>(sphere3, new SphereCollider(glm::vec3(0.0f), 1.0f));
	*/
	// plane
	auto plane = scene.createEntity();
	scene.addComponent<GUIComponent>(plane);
	scene.addComponent<TransformComponent>(plane, glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(3.0f), glm::vec3(0.0f));
	scene.addComponent<MeshComponent>(plane, ResourceManager::GetMesh("plane"));
	scene.addComponent<MaterialComponent>(plane);
	scene.addComponent<RigidBodyComponent>(plane, false, true);
	scene.addComponent<CollisionComponent>(plane, new PlaneCollider(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));

	// init
	scene.init();

	// timing
	float deltaTime = 0.0f;
	float lastFrame = window.GetTime();

	// then before rendering, configure the viewport to the original framebuffer's screen dimensions
	int scrWidth, scrHeight;
	glfwGetFramebufferSize(window.GetWindow(), &scrWidth, &scrHeight);
	glViewport(0, 0, scrWidth, scrHeight);

	//--------------------------------------render loop--------------------------------------//
	while (!window.Closed())
	{
		float currentFrame = window.GetTime();
		deltaTime = currentFrame - lastFrame;
		if (deltaTime >= 1.0f / 120.0f) {
			lastFrame = currentFrame;

			if (window.IsKeyPressed(GLFW_KEY_X)) {
				auto sphere1 = scene.createEntity();
				scene.addComponent<TransformComponent>(sphere1, glm::vec3((float)rand() / RAND_MAX * 2, 10.0f, (float)rand() / RAND_MAX * 2), glm::vec3(1.0f), glm::vec3(0.0f));
				scene.addComponent<MeshComponent>(sphere1, ResourceManager::GetMesh("sphere"));
				scene.addComponent<MaterialComponent>(sphere1, glm::vec3((float)rand() / RAND_MAX, rand() % 2, (float)rand() / RAND_MAX), (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f);
				scene.addComponent<RigidBodyComponent>(sphere1, true, false);
				scene.addComponent<CollisionComponent>(sphere1, new SphereCollider(glm::vec3(0.0f), 1.0f));
				scene.addComponent<GUIComponent>(sphere1);
			}

			window.Clear();

			scene.update(deltaTime);

			scene.draw();

			window.Update();
		}
	}

	// delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	return 0;
}
