#include "FirstExample.h"
#include "ConfigManager/ConfigManager.h"
#include <iostream>

AFirstExample::AFirstExample()
{
    Config = UConfigManager::GetInstance();

    if (Config)
    {
        Config->OnNbVerticeChange.AddCallback(this, &AFirstExample::Update);
    }
}

AFirstExample::~AFirstExample()
{
}

void AFirstExample::Update()
{
    if (!Config)
        return;
    std::cout << Config->NbVertice << "\n";
}