#include "FloatSlider.h"
#include "imgui.h"

UFloatSlider::UFloatSlider(const std::string label, float *value, float min, float max)
    : label(std::move(label)), value(value), min(min), max(max) {}

void UFloatSlider::Display() 
{
    ImGui::SliderFloat(label.c_str(), value, min, max);
}