#ifndef FLOATSLIDER_H
#define FLOATSLIDER_H

#pragma once
#include "../Widget.h"

class UFloatSlider : public UWidget
{
public:
    UFloatSlider(const std::string label, float *value, float min, float max);

    void Display() override;

    std::string label;
    float *value;
    float min;
    float max;

private:
    // float Previous

};

#endif