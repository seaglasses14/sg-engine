#include "Core/GUI/GUI_PropertyHelper.h"
#include "imgui.h"
#include "GUI_PropertyHelper.h"
#include <unordered_map>
#include <string>
#include "Data/Material.h"
#include "Core/AssetPipeline/AssetManager.h"

void GUI_PropertyHelper::DrawWidget(Property& pr)
{
	switch (pr.type)
	{
	case Bool:
		WidgetBool(pr);
		break;
	case Vec3f:
		WidgetVec3f(pr);
		break;
	case Color:
		WidgetColor(pr);
		break;
	case Asset_Model:
		WidgetAssetModel(pr);
		break;
	case Asset_Material:
		WidgetAssetMaterial(pr);
		break;
	default:
		break;
	}
}

void GUI_PropertyHelper::WidgetBool(Property &pr)
{
	ImGui::Spacing();
	if(ImGui::Checkbox(pr.label.c_str(), static_cast<bool*>(pr.data)))
	{
		pr.onChanged();
	}
	ImGui::Spacing();
}

void GUI_PropertyHelper::WidgetVec3f(Property &pr)
{
	ImGui::Spacing();
	if (ImGui::DragFloat3(pr.label.c_str(), static_cast<float*>(pr.data), 0.001f, 0.f, 0.f, "%.3f", ImGuiSliderFlags_ColorMarkers))
	{
		pr.onChanged();
	}
	ImGui::Spacing();
}

void GUI_PropertyHelper::WidgetColor(Property &pr)
{
	ImGui::Spacing();
	ImGui::ColorEdit3(pr.label.c_str(), static_cast<float*>(pr.data), ImGuiColorEditFlags_NoAlpha);
	ImGui::Spacing();
}
void GUI_PropertyHelper::WidgetAssetModel(Property& pr)
{
	ImGui::Spacing();
	ImGui::Text(pr.label.c_str());
	AssetData<Model>* model = static_cast<AssetData<Model>*>(pr.data);
	ImGui::SameLine();
	ImGui::PushID(pr.data);
	if (ImGui::BeginCombo("##ModelHandleCombo", model->handle.id.c_str(), ImGuiComboFlags_HeightRegular))
	{
		static ImGuiTextFilter filter;
		static std::string selected_model_id = model->handle.id;

		if (ImGui::IsWindowAppearing())
		{
			ImGui::SetKeyboardFocusHere();
			filter.Clear();
		}

		ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F);
		filter.Draw("##Filter", -FLT_MIN);
		std::vector<AssetID>& ids = AssetManager::Get().GetModelAssetIDs();
		for (std::string& id : ids)
		{
			const bool is_selected = selected_model_id == id;
			if (filter.PassFilter(id.c_str()))
				if (ImGui::Selectable(id.c_str(), is_selected))
				{
					model->handle.id = id;
					model->cached_data = AssetManager::Get().GetModel(model->handle);
					selected_model_id = id;
				}
		}
		ImGui::EndCombo();
	}
	ImGui::PopID();
	ImGui::Spacing();
}

void GUI_PropertyHelper::WidgetAssetMaterial(Property &pr)
{
	ImGui::Spacing();
	std::unordered_map<unsigned int, AssetData<Material>>* materials = static_cast<std::unordered_map<unsigned int, AssetData<Material>>*>(pr.data);
	
	for(auto& [key, value] : *materials)
	{
		std::string slotLabel = "Slot: " + std::to_string(key);
		ImGui::Text(slotLabel.c_str());
		ImGui::SameLine();
		ImGui::PushID(key);
		if (ImGui::BeginCombo("##MaterialHandleCombo", value.handle.id.c_str(), ImGuiComboFlags_HeightRegular))
		{
			static ImGuiTextFilter filter;
			static std::string selected_material_id = value.handle.id;

			if (ImGui::IsWindowAppearing())
			{
				ImGui::SetKeyboardFocusHere();
				filter.Clear();
			}

			ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F);
			filter.Draw("##Filter", -FLT_MIN);
			std::vector<AssetID>& ids = AssetManager::Get().GetMaterialAssetIDs();
			for (std::string& id : ids)
			{
				const bool is_selected = selected_material_id == id;
				if (filter.PassFilter(id.c_str()))
					if (ImGui::Selectable(id.c_str(), is_selected))
					{
						value.handle.id = id;
						value.cached_data = AssetManager::Get().GetMaterial(value.handle);
						selected_material_id = id;
					}
			}
			ImGui::EndCombo();
		}
		ImGui::PopID();
		ImGui::Spacing();
	}
}