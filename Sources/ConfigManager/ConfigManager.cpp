#include "ConfigManager.h"

#include "Widget/Partials/FloatSlider.h"
#include "Widget/Partials/BooleanCheckbox.h"
#include "lib/Math/KMath.h"
#include <iostream>

UConfigManager *UConfigManager::Instance{nullptr};
std::mutex UConfigManager::Mutex;

UConfigManager::UConfigManager()
{
    InitCamera();
    InitPlane();
    // InitNbVertice();
    // InitZoom();
    // InitEnableShadow();
}

// PROTECTED

void UConfigManager::InitCamera()
{
    CreateAndAddWidgetFloat("CameraLocationX", CameraLocationX, -50.0f, 50.0f);
    CreateAndAddWidgetFloat("CameraLocationY", CameraLocationY, -50.0f, 50.0f);
    CreateAndAddWidgetFloat("CameraLocationZ", CameraLocationZ, -50.0f, 50.0f);

    CreateAndAddWidgetFloat("CameraRotationPitch", CameraRotationPitch, -1.0f * F_PI, 1.0f * F_PI);
    CreateAndAddWidgetFloat("CameraRotationRoll", CameraRotationRoll, -1.0f * F_PI, 1.0f * F_PI);
    CreateAndAddWidgetFloat("CameraRotationYaw", CameraRotationYaw, -1.0f * F_PI, 1.0f * F_PI);
}

void UConfigManager::InitPlane()
{
    CreateAndAddWidgetFloat("PlaneRotationPitch", PlaneRotationPitch, -1.0f * F_PI, 1.0f * F_PI);
    CreateAndAddWidgetFloat("PlaneRotationRoll", PlaneRotationRoll, -1.0f * F_PI, 1.0f * F_PI);
    CreateAndAddWidgetFloat("PlaneRotationYaw", PlaneRotationYaw, -1.0f * F_PI, 1.0f * F_PI);

    CreateAndAddWidgetFloat("PlaneScaleX", PlaneScaleX, 0.0f, 10.0f);
    CreateAndAddWidgetFloat("PlaneScaleY", PlaneScaleY, 0.0f, 10.0f);
    CreateAndAddWidgetFloat("PlaneScaleZ", PlaneScaleZ, 0.0f, 10.0f);
}