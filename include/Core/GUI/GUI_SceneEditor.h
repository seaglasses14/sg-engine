#pragma once

#include "Scene/Scene.h"
#include "Core/Objects/GObject.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "Core/Input/InputRegistry.h"

struct EditorData
{
	// Windows data
	
};

class GUI_SceneEditor
{
public:
	EditorData data;

	void Draw();
	void DrawViewport(GLint texId);
	GUI_SceneEditor(GLFWwindow* pWindow, Scene* pScene);

	bool b_open_SceneViewer = true;
	bool b_open_ObjectDetail = true;
	bool b_open_InputBindings = false;
	bool b_open_Scene = true;

	// State data
	bool b_viewportHovered = false;

	// Temp data
	GObject* selectedObject = nullptr;
	GObject* editingObject = nullptr;
	GObject* highlightedObject = nullptr;

	InputInfo selected_combo_inputInfo;
	InputInfo selected_mapping_inputInfo;

	char renameBuffer[256];
	bool isStartingRenaming = false;

private:
	GLFWwindow* window;
	Scene* scene;

	bool object_highlight = false;
	void GUIW_MenuBar();
	void GUIW_SceneViewer(bool* b_open);
	void GUIW_ObjectDetail(bool* b_open, GObject* selectedObject);
	void GUIW_InputBindings(bool* b_open);
	
	void GUIW_Scene(bool* b_open, bool* b_viewportHovered, GLint texId);

	// Helper Functions
	void StartRenamingObject(GObject* obj);
	void StopRenamingObject(GObject* obj);

	// ComboBox
	static bool InputCodeComboBox(InputInfo& selected_combo_inputInfo);

	void ContextMenu(GObject* obj);
};