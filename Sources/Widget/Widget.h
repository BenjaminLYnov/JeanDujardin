#ifndef WIDGET_H
#define WIDGET_H

#include "Events/Deleguate.h"

#include <string>

// Classe de base abstraite pour les widgets
class UWidget
{
public:
    virtual ~UWidget() = default;
    virtual void Display() = 0; // Méthode virtuelle pure pour afficher le widget

    UDeleguate OnChange;
};

#endif