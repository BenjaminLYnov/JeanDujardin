#include "WidgetManager.h"
#include <iostream>

UWidgetManager::UWidgetManager()
{
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

void UWidgetManager::CallOnChange()
{
    OnChange.Broadcast();
}