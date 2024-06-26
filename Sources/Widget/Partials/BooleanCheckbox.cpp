#include "BooleanCheckbox.h"
#include "imgui.h"

UBooleanCheckbox::UBooleanCheckbox(const std::string &label, bool *value)
    : label(label)
    , value(value) 
{}

void UBooleanCheckbox::Display()
{
    if (ImGui::Checkbox(label.c_str(), value))
    {
        OnChange.Broadcast();
    }
}