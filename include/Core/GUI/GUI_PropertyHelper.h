#pragma once

#include "Core/Objects/Components/Property.h"
#include "imgui.h"
#include <string>
#include <vector>
#include "Utility/DataTypes.h"

class GUI_PropertyHelper
{
public:
	static void DrawWidget(Property& pr);
private:
	static void WidgetBool(Property& pr);
	static void WidgetFloat(Property& pr);
	static void WidgetVec3f(Property& pr);
	static void WidgetColor(Property& pr);
	static void WidgetAssetModel(Property& pr);
	static void WidgetAssetMaterial(Property& pr);

	// Needs PushID/PopID
	// Needs cached data refresh
	template<typename T, typename AssetLoader>
	static bool WidgetAssetHandle(const char* comboId, AssetData<T>& asset, const std::vector<AssetID>& ids, AssetLoader loader)
	{
		bool changed = false;

		if (ImGui::BeginCombo(comboId, asset.handle.id.c_str(), ImGuiComboFlags_HeightRegular))
		{
			static ImGuiTextFilter filter;

			if (ImGui::IsWindowAppearing())
			{
				ImGui::SetKeyboardFocusHere();
				filter.Clear();
			}

			ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F);
			filter.Draw("##Filter", -FLT_MIN);

			std::string selected_id = asset.handle.id;

			for (const auto& id : ids)
			{
				bool selected = selected_id == id;

				if (filter.PassFilter(id.c_str()) &&
					ImGui::Selectable(id.c_str(), selected))
				{
					asset.handle.id = id;
					asset.cached_data = loader(asset.handle);
					selected_id = id;
					changed = true;
				}

				//if (selected)
				//	ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

    	return changed;
	}
};