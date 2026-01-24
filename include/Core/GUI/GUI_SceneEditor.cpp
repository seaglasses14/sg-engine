#include "Core/GUI/GUI_SceneEditor.h"
#include "imgui.h"
#include "Core/Objects/Components/Component.h"
#include "glm/glm.hpp"
#include "Core/Log.h"
#include <string>

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
                    if (pr.type == PropertyType::Vec3f)
                    {
                        ImGui::DragFloat3(pr.label.c_str(), static_cast<float*>(pr.data), 1.f, 0.f, 0.f, "%.3f", ImGuiSliderFlags_ColorMarkers);
                        /*
                        std::string a = "X: " + std::to_string(static_cast<glm::vec3*>(pr.data)->x)
                                       +" Y: " + std::to_string(static_cast<glm::vec3*>(pr.data)->y)
                                       +" Z: " + std::to_string(static_cast<glm::vec3*>(pr.data)->z);
                        LOG_INFO(a);
                        */
                    }
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
