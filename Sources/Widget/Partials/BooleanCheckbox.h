#ifndef BOOLEANCHECKBOX_H
#define BOOLEANCHECKBOX_H

#pragma once
#include "../Widget.h"

class UBooleanCheckbox : public UWidget
{
public:
    UBooleanCheckbox(const std::string label, bool *value);
    
    void Display() override;
    std::string label;
    bool *value;

private:
};

#endif