#include "BooleanCheckbox.h"
#include "imgui.h"

UBooleanCheckbox::UBooleanCheckbox(const std::string label, bool *value)
    : label(std::move(label)), value(value) {}

void UBooleanCheckbox::Display()
{
    ImGui::Checkbox(label.c_str(), value);
}