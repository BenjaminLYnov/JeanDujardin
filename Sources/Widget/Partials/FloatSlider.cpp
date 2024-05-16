#include "FloatSlider.h"
#include "imgui.h"
#include <iostream>

UFloatSlider::UFloatSlider(const std::string &label, float *value, float min, float max)
    : label(label)
    , value(value)
    , min(min)
    , max(max) 
{}

void UFloatSlider::Display() 
{
    if (ImGui::SliderFloat(label.c_str(), value, min, max))
    {
       OnChange.Broadcast();
    }
}