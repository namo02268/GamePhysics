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
			auto transfromComponent = m_parentScene->getComponent<TransformComponent>(e);
			ImGui::DragFloat3("Position", &transfromComponent->position.x, 0.01f);
			ImGui::DragFloat3("Scale", &transfromComponent->scale.x, 0.01f);
			ImGui::DragFloat3("Rotation", &transfromComponent->rotation.x, 1.0f);
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
			auto materialComponent = m_parentScene->getComponent<MaterialComponent>(e);
			ImGui::ColorEdit3("Albedo", &materialComponent->albedo.x);
			ImGui::SliderFloat("Metallic", &materialComponent->metallic, 0.0f, 1.0f);
			ImGui::SliderFloat("Roughness", &materialComponent->roughness, 0.0f, 1.0f);
			ImGui::SliderFloat("ao", &materialComponent->ao, 0.0f, 1.0f);
			if (ImGui::Button("Remove Component"))
				m_parentScene->removeComponent<MaterialComponent>(e);
			ImGui::TreePop();
		}
	}
};

