#ifndef WIDGET_H
#define WIDGET_H

#pragma once

#include <string>

// Classe de base abstraite pour les widgets
class UWidget {
public:
    virtual ~UWidget() = default;
    virtual void Display() = 0;  // Méthode virtuelle pure pour afficher le widget
};

#endif