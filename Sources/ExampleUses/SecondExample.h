#ifndef SECONDEXAMPLE_H
#define SECONDEXAMPLE_H

class UConfigManager;

class ASecondExample
{
public:
    ASecondExample();
    ~ASecondExample();

    void OnUpdateZoom();
    void OnUpdateEnableShadow();

private:
    UConfigManager *Config;
};

#endif