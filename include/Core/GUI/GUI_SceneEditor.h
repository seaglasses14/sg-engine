#pragma once

#include "Scene/Scene.h"
#include "Core/Objects/GObject.h"

class GUI_SceneEditor
{
public:
	bool b_open_SceneViewer = true;
	bool b_open_ObjectDetail = true;

	void Draw();
	GUI_SceneEditor(Scene* pScene);

private:
	Scene* scene;
	GObject* selectedObject = nullptr;
	GObject* highlightedObject = nullptr;
	bool object_highlight = false;
	void GUIW_SceneViewer(bool* b_open);
	void GUIW_ObjectDetail(bool* b_open, GObject* selectedObject);
	void GUIW_Scene(bool* b_open);
};