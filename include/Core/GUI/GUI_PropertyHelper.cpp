#include "GUI_PropertyHelper.h"
#include <unordered_map>

#include "Data/Material.h"
#include "Core/AssetPipeline/AssetManager.h"
#include "Core/Log.h"

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
	
	WidgetAssetHandle(
		"##ModelHandleCombo",
		*model,
		AssetManager::Get().GetModelAssetIDs(),
		[](const AssetHandle<Model>& h)
		{
			return AssetManager::Get().GetModel(h);
		}
	);

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

		WidgetAssetHandle(
			"##MaterialHandleCombo", 
			value, 
			AssetManager::Get().GetMaterialAssetIDs(), 
			[](const AssetHandle<Material>& h)
			{
				return AssetManager::Get().GetMaterial(h);
			});
		//LOG_INFO("Changed material handle");

		ImGui::PopID();
		ImGui::Spacing();
	}
}