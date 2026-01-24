#pragma once

#include "Core/Objects/GObject.h"

class GUI_SceneEditor
{
public:
	bool b_open_SceneViewer = true;
	bool b_open_ObjectDetail = true;

	void Draw();
	GObject* selectedObject = new GObject();

private:
	void GUIW_SceneViewer(bool* b_open);
	void GUIW_ObjectDetail(bool* b_open, GObject* selectedObject);
};