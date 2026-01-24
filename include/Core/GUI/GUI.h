#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Core/GUI/GUI_SceneEditor.h"

class GUI
{
public:
	GUI(GLFWwindow* window);
	void StartDrawing();
	void SetIOConfigFlag(ImGuiConfigFlags_ flag);
	void Draw();
	void Render();
	void Shutdown();

private:
	GUI_SceneEditor* sceneEditor = new GUI_SceneEditor();
};

