#ifndef FIRSTEXAMPLE_H
#define FIRSTEXAMPLE_H

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