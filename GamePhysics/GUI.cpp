#include "GUI.h"
#include "Scene.h"
#include "GUIComponent.h"
#include "ComponentGUIs.h"


void imgui_theme();

GUI::GUI(Window* window) {
	this->parentWindow = window;

	auto family = getComponentTypeID<GUIComponent>();
	m_requiredComponent[family] = true;
}

GUI::~GUI() {
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GUI::init() {
	// init imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	const char* glsl_version = "#version 330";
	ImGui_ImplGlfw_InitForOpenGL(parentWindow->GetWindow(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// imgui configuration
	imgui_theme();

	// add Component GUIs
	auto transformComponentGUI = std::make_unique<TransfromComponentGUI>(m_parentScene);
	m_componentGUIbit[transformComponentGUI->ID] = true;
	auto materialComponentGUI = std::make_unique<MaterialComponentGUI>(m_parentScene);
	m_componentGUIbit[materialComponentGUI->ID] = true;
	auto rigidBodyComponentGUI = std::make_unique<RigidBodyComponentGUI>(m_parentScene);
	m_componentGUIbit[rigidBodyComponentGUI->ID] = true;
	auto cameraComponentGUI = std::make_unique<CameraComponentGUI>(m_parentScene);
	m_componentGUIbit[cameraComponentGUI->ID] = true;

	m_componentGUIs[transformComponentGUI->ID] = std::move(transformComponentGUI);
	m_componentGUIs[materialComponentGUI->ID] = std::move(materialComponentGUI);
	m_componentGUIs[rigidBodyComponentGUI->ID] = std::move(rigidBodyComponentGUI);
	m_componentGUIs[cameraComponentGUI->ID] = std::move(cameraComponentGUI);
}

void GUI::update(float dt) {
}

void GUI::draw() {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	bool open;

	// Scene GUI
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(200, parentWindow->GetHeight()));
	ImGui::Begin("Scene", &open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	static int selected = -1;
	for (int n = 0; n < m_entityArray.size(); n++) {
		if (ImGui::Selectable(m_entityArray[n].name.c_str(), selected == n)) {
			selected = n;
		}
	}
	
	ImGui::End();

	// Component GUI
	ImGui::SetNextWindowPos(ImVec2(parentWindow->GetWidth() - 400.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(400.0f, parentWindow->GetHeight()));
	ImGui::Begin("Inspector", &open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::PushItemWidth(200);

	if (selected != -1) {
		ImGui::PushID(m_entityArray[selected].GetID());
		for (int i = 0; i < MAX_COMPONENTS_FAMILY; i++) {
			if (m_entityArray[selected].attachedComponent[i] && m_componentGUIbit[i]) {
				ImGui::SetNextItemOpen(true, ImGuiCond_Once);
				m_componentGUIs[i]->draw(m_entityArray[selected]);
				ImGui::Separator();
			}
		}

		ImGui::PushItemWidth(50.0f);
		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("Component");

		if (ImGui::BeginPopup("Component"))
		{
			if (ImGui::Selectable("Transform"))
				m_parentScene->addComponent<TransformComponent>(m_entityArray[selected]);
			if (ImGui::Selectable("Material"))
				m_parentScene->addComponent<MaterialComponent>(m_entityArray[selected]);
			if (ImGui::Selectable("RigidBody"))
				m_parentScene->addComponent<RigidBodyComponent>(m_entityArray[selected]);
			ImGui::EndPopup();
		}
		ImGui::PopID();
	}

	ImGui::PopItemWidth();
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imgui_theme() {
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	style.Colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
	style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

	style.ChildRounding = 4.0f;
	style.FrameBorderSize = 1.0f;
	style.FrameRounding = 2.0f;
	style.GrabMinSize = 7.0f;
	style.PopupRounding = 2.0f;
	style.ScrollbarRounding = 12.0f;
	style.ScrollbarSize = 13.0f;
	style.TabBorderSize = 1.0f;
	style.TabRounding = 0.0f;
	style.WindowRounding = 4.0f;

}