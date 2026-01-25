#include "Core/GUI/GUI_SceneEditor.h"
#include "imgui.h"
#include "Core/Objects/Components/Component.h"
#include "glm/glm.hpp"
#include "Core/Log.h"
#include <string>
#include "Core/GUI/GUI_PropertyHelper.h"

void GUI_SceneEditor::Draw()
{
    GUIW_ObjectDetail(&b_open_ObjectDetail, selectedObject);
}

void GUI_SceneEditor::GUIW_SceneViewer(bool* b_open)
{
}

void GUI_SceneEditor::GUIW_ObjectDetail(bool* b_open, GObject* selectedObject)
{
	if (*b_open)
	{
		ImGui::Begin("Details", b_open);

        for (Component* comp : selectedObject->components)
        {
            std::vector<Property> propertyData = comp->GetProperties();
            
            if (ImGui::CollapsingHeader(comp->label.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                for (Property pr : propertyData)
                {
                    GUI_PropertyHelper::DrawWidget(pr);
                }

            }


        }
        if (ImGui::CollapsingHeader("Header", ImGuiTreeNodeFlags_None))
        {
            ImGui::Text("IsItemHovered: %d", ImGui::IsItemHovered());
            for (int i = 0; i < 5; i++)
                ImGui::Text("Some content %d", i);
        }
        /*
        if (ImGui::CollapsingHeader("Header with a bullet", ImGuiTreeNodeFlags_Bullet))
            ImGui::Text("IsItemHovered: %d", ImGui::IsItemHovered());
        */


		ImGui::End();
	}
}
