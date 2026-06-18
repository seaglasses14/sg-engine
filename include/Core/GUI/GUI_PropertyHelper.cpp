#include "Core/GUI/GUI_PropertyHelper.h"
#include "imgui.h"
#include "GUI_PropertyHelper.h"

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
	case AssetHandle_Model:
		WidgetAssetHandleModel(pr);
		break;
	default:
		break;
	}
}

void GUI_PropertyHelper::WidgetBool(Property &pr)
{
	if(ImGui::Checkbox(pr.label.c_str(), static_cast<bool*>(pr.data)))
	{
		pr.onChanged();
	}
}

void GUI_PropertyHelper::WidgetVec3f(Property &pr)
{
	if (ImGui::DragFloat3(pr.label.c_str(), static_cast<float*>(pr.data), 0.001f, 0.f, 0.f, "%.3f", ImGuiSliderFlags_ColorMarkers))
	{
		pr.onChanged();
	}
}

void GUI_PropertyHelper::WidgetColor(Property &pr)
{
	ImGui::ColorPicker3(pr.label.c_str(), static_cast<float*>(pr.data), ImGuiColorEditFlags_NoAlpha);
}
void GUI_PropertyHelper::WidgetAssetHandleModel(Property& pr)
{
	ImGui::Text("AssetHandle Model");
}
