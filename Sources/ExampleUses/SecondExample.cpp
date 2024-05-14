#include "SecondExample.h"
#include "ConfigManager/ConfigManager.h"
#include <iostream>

ASecondExample::ASecondExample()
{
   Config = UConfigManager::GetInstance();

    if (Config)
    {
        Config->OnZoomChange.AddCallback(this, &ASecondExample::OnUpdateZoom);
        Config->OnEnableShadowChange.AddCallback(this, &ASecondExample::OnUpdateEnableShadow);
    }
}

ASecondExample::~ASecondExample()
{

}

void ASecondExample::OnUpdateZoom()
{
    if (!Config)
        return;
    std::cout << Config->Zoom << "\n";
}

void ASecondExample::OnUpdateEnableShadow()
{
    if (!Config)
        return;
    std::cout << Config->bEnableShadow << "\n";
}