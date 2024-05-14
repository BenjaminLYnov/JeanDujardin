#include "ConfigManager.h"
#include <iostream>
#include "Widget/Partials/FloatSlider.h"
#include "Widget/Partials/BooleanCheckbox.h"

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
    std::unique_ptr<UFloatSlider> FS = std::make_unique<UFloatSlider>("Nombre de vertice", &NbVertice, 0.0f, 100.0f);
    FS->OnChange.AddCallback(this, &UConfigManager::CallNbVerticeChange);
    AddWidget(std::move(FS));
}

void UConfigManager::InitZoom()
{
    std::unique_ptr<UFloatSlider> FS = std::make_unique<UFloatSlider>("Zoom", &Zoom, 0.0f, 100.0f);
    FS->OnChange.AddCallback(this, &UConfigManager::CallZoomChange);
    AddWidget(std::move(FS));
}

void UConfigManager::InitEnableShadow()
{
    std::unique_ptr<UBooleanCheckbox> FS = std::make_unique<UBooleanCheckbox>("Enable Shadows", &bEnableShadow);
    FS->OnChange.AddCallback(this, &UConfigManager::CallEnableShadowChange);
    AddWidget(std::move(FS));
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
