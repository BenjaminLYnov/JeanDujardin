#include "WidgetManager.h"
#include <iostream>
#include "Widget/Partials/FloatSlider.h"
#include "Widget/Partials/BooleanCheckbox.h"

UWidgetManager::UWidgetManager()
{
}

UWidgetManager::~UWidgetManager()
{
    // Delete all widgets ?
}

void UWidgetManager::DisplayWidgets()
{
    for (const auto &Widget : Widgets)
    {
        Widget->Display();
    }
}

void UWidgetManager::AddWidget(std::unique_ptr<UWidget> NewWidget)
{
    if (!NewWidget)
        return;
    Widgets.emplace_back(std::move(NewWidget));
}

void UWidgetManager::CreateAndAddWidgetFloat(const std::string Name, float &Value, const float Min, const float Max)
{
    std::unique_ptr<UFloatSlider> Widget = std::make_unique<UFloatSlider>(Name, &Value, Min, Max);
    AddWidget(std::move(Widget));
}

void UWidgetManager::CallOnChange()
{
    OnChange.Broadcast();
}