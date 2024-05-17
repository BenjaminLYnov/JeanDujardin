#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "Widget/WidgetManager.h"
#include "Events/Deleguate.h"

#include <mutex>

class UConfigManager : public UWidgetManager
{
public:
    UConfigManager(UConfigManager &other) = delete;  // Suppression du constructeur de copie
    void operator=(const UConfigManager &) = delete; // Suppression de l'opérateur d'assignation

    static UConfigManager *GetInstance()
    {
        std::lock_guard<std::mutex> lock(Mutex);
        if (Instance == nullptr)
        {
            Instance = new UConfigManager();
        }
        return Instance;
    }


    float CameraLocationX = 0;
    float CameraLocationY = 0;
    float CameraLocationZ = -15;

    float CameraRotationPitch = 0.78; // PI/4
    float CameraRotationRoll = 0;
    float CameraRotationYaw = 0;

    float CameraScaleX = 1;
    float CameraScaleY = 1;
    float CameraScaleZ = 1;

    float PlaneLocationX = 0;
    float PlaneLocationY = 0;
    float PlaneLocationZ = 0;

    float PlaneRotationPitch = 0;
    float PlaneRotationRoll = 0;
    float PlaneRotationYaw = 0;

    float PlaneScaleX = 1;
    float PlaneScaleY = 1;
    float PlaneScaleZ = 1;

    float PlaneSize = 10.f;

    // Les variablees
    // float NbVertice = 0;
    // // float AnotherThing = new float(0);
    // float AnotherThing = 0;
    // float Zoom = 0;
    // // bool* bEnableShadow = new bool(true);
    // bool bEnableShadow = true;

    // UDeleguate OnNbVerticeChange;
    // UDeleguate OnZoomChange;
    // UDeleguate OnEnableShadowChange;

protected:
    UConfigManager(); // Constructeur privé

    template <typename T, typename Method>
    void InitWidget(std::unique_ptr<UWidget> Widget, T *Obj, Method MethodToBind)
    {
        Widget->OnChange.AddCallback(this, MethodToBind);
        AddWidget(std::move(Widget));
    };

    // virtual void InitNbVertice();
    // virtual void InitZoom();
    // virtual void InitEnableShadow();

    virtual void InitCamera();
    virtual void InitPlane();

private:
    static UConfigManager *Instance;
    static std::mutex Mutex;

    // void CallNbVerticeChange();
    // void CallZoomChange();
    // void CallEnableShadowChange();
};

#endif