#pragma once
#include "GUI.h"
#include "Scene.h"

#include "TransformComponent.h"
#include "MaterialComponent.h"

//----------------------------------------------Transform----------------------------------------------//
class TransfromComponentGUI : public ComponentGUIBase {
public:
	TransfromComponentGUI(Scene* scene) {
		m_parentScene = scene;
		ID = getComponentTypeID<TransformComponent>();
	}

	void draw(Entity& e) {
		if (ImGui::TreeNode("Transform")) {
			ImGui::DragFloat3("Position", &m_parentScene->getComponent<TransformComponent>(e).position.x, 0.01f);
			ImGui::DragFloat3("Scale", &m_parentScene->getComponent<TransformComponent>(e).scale.x, 0.01f);
			ImGui::DragFloat3("Rotation", &m_parentScene->getComponent<TransformComponent>(e).rotation.x, 1.0f);
			if (ImGui::Button("Remove Component"))
				m_parentScene->removeComponent<TransformComponent>(e);
			ImGui::TreePop();
		}
	}
};

//----------------------------------------------Material----------------------------------------------//
class MaterialComponentGUI : public ComponentGUIBase {
public:
	MaterialComponentGUI(Scene* scene) {
		m_parentScene = scene;
		ID = getComponentTypeID<MaterialComponent>();
	}

	void draw(Entity& e) {
		if (ImGui::TreeNode("Material")) {
			ImGui::ColorEdit3("Albedo", &m_parentScene->getComponent<MaterialComponent>(e).albedo.x);
			ImGui::SliderFloat("Metallic", &m_parentScene->getComponent<MaterialComponent>(e).metallic, 0.0f, 1.0f);
			ImGui::SliderFloat("Roughness", &m_parentScene->getComponent<MaterialComponent>(e).roughness, 0.0f, 1.0f);
			ImGui::SliderFloat("ao", &m_parentScene->getComponent<MaterialComponent>(e).ao, 0.0f, 1.0f);
			if (ImGui::Button("Remove Component"))
				m_parentScene->removeComponent<MaterialComponent>(e);
			ImGui::TreePop();
		}
	}
};

