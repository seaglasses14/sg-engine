#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Core/GUI/GUI_SceneEditor.h"
#include "Scene/Scene.h"

class GUI
{
public:
	GUI(GLFWwindow* window, Scene* pScene);
	void StartDrawing();
	void SetIOConfigFlag(ImGuiConfigFlags_ flag);
	void Draw();
	void DrawViewport(GLint texId);
	void Render();
	void Shutdown();

private:
	Scene* scene;
	GUI_SceneEditor* sceneEditor;
};

