#include "WidgetManager.h"

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