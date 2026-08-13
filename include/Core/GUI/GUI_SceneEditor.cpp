#include "Core/GUI/GUI_SceneEditor.h"
#include "imgui.h"
#include "Core/Objects/Components/Component.h"
#include "Core/Log.h"
#include <string>
#include "Core/GUI/GUI_PropertyHelper.h"
#include "GUI_SceneEditor.h"
#include "Core/Input/InputManager.h"

void GUI_SceneEditor::Draw()
{
    GUIW_MenuBar();
    GUIW_SceneViewer(&b_open_SceneViewer);
    GUIW_ObjectDetail(&b_open_ObjectDetail, selectedObject);
    GUIW_InputBindings(&b_open_InputBindings);
    ImGui::Begin("Viewport");
}

void GUI_SceneEditor::DrawViewport(GLint texId)
{
    GUIW_Scene(&b_open_Scene, &b_viewportHovered, texId);
}

GUI_SceneEditor::GUI_SceneEditor(GLFWwindow* pWindow, Scene* pScene)
{
    window = pWindow;
    scene = pScene;
}

void GUI_SceneEditor::GUIW_MenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools"))
        {
            if (ImGui::MenuItem("Input Bindings")) { b_open_InputBindings = true; }
            /*
            if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) {} // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "Ctrl+X")) {}
            if (ImGui::MenuItem("Copy", "Ctrl+C")) {}
            if (ImGui::MenuItem("Paste", "Ctrl+V")) {}
            */
            ImGui::EndMenu();

        }
        ImGui::EndMainMenuBar();
    }
}

void GUI_SceneEditor::GUIW_SceneViewer(bool *b_open)
{
    if (*b_open)
    {
        ImGui::Begin("Scene", b_open);

        if (ImGui::Button("Add Object"))
        {
            ImGui::OpenPopup("Select Object");
        }
        //ImGui::SetItemTooltip("Add new object to scene");
        if (ImGui::BeginPopup("Select Object"))
        {
            int selectedNewObject = -1;
            const char* names[] = { "Empty", "Cube", "DirectLight" };
            
            if(ImGui::MenuItem("Empty"))
            {
                selectedNewObject = 0;
            }
            if(ImGui::MenuItem("Cube"))
            {
                selectedNewObject = 1;
            }
            if (ImGui::BeginMenu("Lights"))
            {
                if(ImGui::MenuItem("DirectLight"))
                {
                    selectedNewObject = 2;
                }
                ImGui::EndMenu();
            }

            GObject* newObj = nullptr;
            switch (selectedNewObject)
            {
                case 0:
                    newObj = scene->CreateEmpty("Empty");
                    break;
                case 1:
                    newObj = scene->CreateCube("Cube");
                    break;
                case 2:
                    newObj = scene->CreateDirectLight("DirectLight");
                    break;
                default:
                    break;
            }
            if(newObj)
            {
                selectedObject = newObj;
                StartRenamingObject(newObj);
            }
            ImGui::EndPopup();
        }

        if (ImGui::BeginListBox("##Scene", ImVec2(-FLT_MIN, 20 * ImGui::GetTextLineHeightWithSpacing())))
        {
            for (GObject* obj : scene->objects)
            {
                if(editingObject == obj)
                {
                    if(isStartingRenaming)
                    {
                        ImGui::SetKeyboardFocusHere();
                        isStartingRenaming = false;
                    }
                    ImGui::PushID(obj);
                    ImGui::SetNextItemWidth(-FLT_MIN);


                    if(ImGui::InputText("##Rename", renameBuffer, sizeof(renameBuffer), ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue))
                    {
                        StopRenamingObject(obj);
                    }
                    
                    if(ImGui::IsItemDeactivated()) //&& !ImGui::IsItemActive())
                    {
                        StopRenamingObject(obj);
                    }
                    
                    ImGui::PopID();
                }
                else
                {
                    const bool is_selected = (selectedObject == obj);

                    if (ImGui::Selectable(obj->label.c_str(), is_selected))
                        selectedObject = obj;

                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                    
                    if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                    {
                        StartRenamingObject(obj);
                    }

                    ContextMenu(obj);
                }
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
                    static bool first = true;
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

void GUI_SceneEditor::GUIW_InputBindings(bool *b_open)
{
    if(*b_open)
    {
        ImGui::SetNextWindowSize(ImVec2(500, 440));
        if(ImGui::Begin("Input Bindings", b_open))
        {
            auto& IM = InputManager::Get();
            if(ImGui::BeginTabBar("##InputBindingsTabs", ImGuiTabBarFlags_None))
            {
                if(ImGui::BeginTabItem("InputMaps"))
                {
                    ImGui::BeginGroup();
                    
                    InputCodeComboBox(selected_combo_inputInfo);
                    ImGui::SameLine();
                    ImGui::BeginDisabled(selected_combo_inputInfo.label.empty());
                    if(ImGui::Button("Add New"))
                    {
                        IM.inputMapping.AddInputBinding(selected_combo_inputInfo.code);
                    }
                    ImGui::EndDisabled();
                    ImGui::SameLine();
                    ImGui::BeginDisabled(selected_mapping_inputInfo.label.empty());
                    if(ImGui::Button("Remove Selected"))
                    {
                        IM.inputMapping.RemoveInputBinding(selected_mapping_inputInfo.code);
                    }
                    ImGui::EndDisabled();

                    ImGui::Separator();

                    ImGui::BeginChild("InputCodes", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
                    
                    for(auto& [code, actions] : IM.inputMapping.bindings)
                    {
                        InputInfo info = InputRegistry::GetInputInfo(code);
                        if(ImGui::Selectable(info.label.c_str(), selected_mapping_inputInfo == info, ImGuiSelectableFlags_SelectOnNav))
                        {
                            selected_mapping_inputInfo = info;
                        }
                    }

                    ImGui::EndChild();
                    ImGui::EndGroup();
                    /*
                    ImGui::SameLine();
                    ImGui::BeginGroup();
                    ImGui::EndGroup();
                    */
                    ImGui::EndTabItem();
                }
                
                if(ImGui::BeginTabItem("Input Actions"))
                {
                    
                    ImGui::EndTabBar();
                }

                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    }
}

void GUI_SceneEditor::GUIW_Scene(bool* b_open, bool* b_viewportHovered, GLint texId)
{
    //ImGui::Begin("Viewport");
    ImGui::Image(texId, ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
    *b_viewportHovered = ImGui::IsItemHovered();
    auto& IM = InputManager::Get();
    if(*b_viewportHovered)
    {
        // Swap with an event fired on button pressed that checks for the stored viewportHovered variable
        if(IM.IsMouseKeyDown(GLFW_MOUSE_BUTTON_RIGHT) && IM.mode == InputMode::Editor)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            IM.mode = InputMode::SceneViewer;
            //IM.GetInputState().firstMouse = true;
            //IM.RefreshPerFrameValue();
            ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
            ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoKeyboard;
        }
    }
    if(IM.mode == InputMode::SceneViewer && IM.IsMouseKeyUp(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        IM.mode = InputMode::Editor;
        ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
        ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoKeyboard;
    }
    ImGui::End();
}

void GUI_SceneEditor::StartRenamingObject(GObject* obj)
{
    isStartingRenaming = true;
    editingObject = obj;
    strncpy(renameBuffer, obj->label.c_str(), sizeof(renameBuffer));
    renameBuffer[sizeof(renameBuffer) - 1] = '\0';
}

void GUI_SceneEditor::StopRenamingObject(GObject* obj)
{
    if(renameBuffer[0] != '\0')
        scene->SetObjectLabel(obj, renameBuffer);
    editingObject = nullptr;
    isStartingRenaming;
}

bool GUI_SceneEditor::InputCodeComboBox(InputInfo& selected_combo_inputInfo)
{
    bool changed = false;

    if(ImGui::BeginCombo("##InputCodeComboBox", selected_combo_inputInfo.label.c_str(), ImGuiComboFlags_HeightRegular))
    {
        static ImGuiTextFilter filter;
        if (ImGui::IsWindowAppearing())
        {
            ImGui::SetKeyboardFocusHere();
            filter.Clear();
        }
        ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F);
		filter.Draw("##Filter", -FLT_MIN);
        
        const auto& infos = InputRegistry::GetInputs();
        for (const auto& info : infos)
        {
            bool selected = selected_combo_inputInfo == info;

            if (filter.PassFilter(info.label.c_str()) &&
                ImGui::Selectable(info.label.c_str(), selected))
            {
                selected_combo_inputInfo = info;
                changed = true;
            }
        }
        ImGui::EndCombo();
    }
    return changed;
}

void GUI_SceneEditor::ContextMenu(GObject *obj)
{
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::Selectable("Rename"))
        {
            StartRenamingObject(obj);
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}
