#ifndef FIRSTEXAMPLE_H
#define FIRSTEXAMPLE_H

#pragma once

class UConfigManager;

class AFirstExample
{
public:
    AFirstExample();
    ~AFirstExample();

    void Update();

private:

    UConfigManager *Config;


};

#endif