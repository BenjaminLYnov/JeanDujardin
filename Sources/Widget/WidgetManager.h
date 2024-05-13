#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#pragma once

#include "Widget.h"
#include <vector>
#include <memory>
#include "Events/Deleguate.h"

class UWidgetManager
{
public:
    UWidgetManager();

    void DisplayWidgets();

    UDeleguate OnChange;

    void AddWidget(std::unique_ptr<UWidget> NewWidget);

    template <typename WidgetType, typename... Args>
    void AddWidget(Args &&...args)
    {
        std::unique_ptr<UWidget> NewWidget = std::make_unique<WidgetType>(std::forward<Args>(args)...);

        if (!NewWidget)
            return;

        NewWidget->OnChange.AddCallback(this, &UWidgetManager::CallOnChange);
        Widgets.emplace_back(std::move(NewWidget));
    }

private:
    std::vector<std::unique_ptr<UWidget>> Widgets;

    void CallOnChange();
};

#endif