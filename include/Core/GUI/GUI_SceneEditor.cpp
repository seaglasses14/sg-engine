#include "Core/GUI/GUI_SceneEditor.h"
#include "imgui.h"
#include "Core/Objects/Components/Component.h"
#include "glm/glm.hpp"
#include "Core/Log.h"
#include <string>
#include "Core/GUI/GUI_PropertyHelper.h"

void GUI_SceneEditor::Draw()
{
    GUIW_SceneViewer(&b_open_SceneViewer);
    GUIW_ObjectDetail(&b_open_ObjectDetail, selectedObject);
}

void GUI_SceneEditor::DrawViewport(GLint texId)
{
    GUIW_Scene(&b_open_Scene, &b_viewportHovered, texId);
}

GUI_SceneEditor::GUI_SceneEditor(Scene* pScene)
{
    scene = pScene;
}

void GUI_SceneEditor::GUIW_SceneViewer(bool* b_open)
{
    if (*b_open)
    {
        ImGui::Begin("Scene", b_open);

        if (ImGui::Button("Add Object"))
        {
            scene->AddObject("Object");
        }

        if (ImGui::BeginListBox("##Scene", ImVec2(-FLT_MIN, 20 * ImGui::GetTextLineHeightWithSpacing())))
        {
            for (GObject* obj : scene->objects)
            {
                const bool is_selected = (selectedObject == obj);
                if (ImGui::Selectable(obj->label.c_str(), is_selected))
                    selectedObject = obj;

                if (object_highlight && ImGui::IsItemHovered())
                    highlightedObject = obj;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        /*
        // Custom size: use all width, 5 items tall
        ImGui::Text("Full-width:");
        if (ImGui::BeginListBox("##Scene", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
        {
            for (int n = 0; n < IM_COUNTOF(items); n++)
            {
                bool is_selected = (item_selected_idx == n);
                ImGuiSelectableFlags flags = (item_highlighted_idx == n) ? ImGuiSelectableFlags_Highlight : 0;
                if (ImGui::Selectable(items[n], is_selected, flags))
                    item_selected_idx = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        */



        ImGui::End();
    }
}

void GUI_SceneEditor::GUIW_ObjectDetail(bool* b_open, GObject* selectedObject)
{
	if (*b_open)
	{
        ImGui::Begin("Details", b_open);

        if (selectedObject)
        {
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
        }

        ImGui::End();
	}
}

void GUI_SceneEditor::GUIW_Scene(bool* b_open, bool* b_viewportHovered, GLint texId)
{
    ImGui::Begin("Viewport");
    ImVec2 pos = ImGui::GetContentRegionAvail();
    ImGui::Image(texId, pos, ImVec2(0, 1), ImVec2(1, 0));
    *b_viewportHovered = ImGui::IsItemHovered();
    ImGui::End();
}

