#include "GUI.h"

GUI::GUI(GLFWwindow* window)
{
	// Init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); // (void)io
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	// Style
	ImGui::StyleColorsDark();
	//ImGuiStyle& style = ImGui::GetStyle();
	//style.ScaleAllSizes(main_scale);
	//style.FontScaleDpi = main_scale;

	// Backend
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
}

void GUI::StartDrawing()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport();
	//ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}

void GUI::SetIOConfigFlag(ImGuiConfigFlags_ flag)
{
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= flag;
}

void GUI::Draw()
{
	sceneEditor->Draw();
}

void GUI::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

