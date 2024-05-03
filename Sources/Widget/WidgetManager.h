#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#pragma once

#include "Widget.h"
#include <vector>
#include <memory>

class UWidgetManager
{
public:
    UWidgetManager();

    std::vector<std::unique_ptr<UWidget>> Widgets;

    template <typename WidgetType, typename... Args>
    void AddWidget(Args &&...args)
    {
        Widgets.emplace_back(std::make_unique<WidgetType>(std::forward<Args>(args)...));
    }

    void DisplayWidgets();

private:
};

#endif