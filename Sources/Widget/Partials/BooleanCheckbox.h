#ifndef BOOLEANCHECKBOX_H
#define BOOLEANCHECKBOX_H

#include "Widget/Widget.h"

class UBooleanCheckbox : public UWidget
{
public:
    UBooleanCheckbox(const std::string &label, bool *value);
    
    void Display() override;
    std::string label;
    bool *value;

private:
};

#endif