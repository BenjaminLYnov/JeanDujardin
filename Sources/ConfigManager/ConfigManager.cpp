#include "ConfigManager.h"

#include "Widget/Partials/FloatSlider.h"
#include "Widget/Partials/BooleanCheckbox.h"

#include <iostream>

UConfigManager *UConfigManager::Instance{nullptr};
std::mutex UConfigManager::Mutex;

UConfigManager::UConfigManager()
{
    InitNbVertice();
    InitZoom();
    InitEnableShadow();
}

// PROTECTED

void UConfigManager::InitNbVertice()
{
    std::unique_ptr<UFloatSlider> Widget = std::make_unique<UFloatSlider>("Nombre de vertice", &NbVertice, 0.0f, 100.0f);
    InitWidget(std::move(Widget), this, &UConfigManager::CallNbVerticeChange);
}

void UConfigManager::InitZoom()
{
    std::unique_ptr<UFloatSlider> Widget = std::make_unique<UFloatSlider>("Zoom", &Zoom, 0.0f, 100.0f);
    InitWidget(std::move(Widget), this, &UConfigManager::CallZoomChange);
}

void UConfigManager::InitEnableShadow()
{
    std::unique_ptr<UBooleanCheckbox> Widget = std::make_unique<UBooleanCheckbox>("Enable Shadows", &bEnableShadow);
    InitWidget(std::move(Widget), this, &UConfigManager::CallEnableShadowChange);
}

// PRIVATE

void UConfigManager::CallNbVerticeChange()
{
    OnNbVerticeChange.Broadcast();
}

void UConfigManager::CallZoomChange()
{
    OnZoomChange.Broadcast();
}

void UConfigManager::CallEnableShadowChange()
{
    OnEnableShadowChange.Broadcast();
}
