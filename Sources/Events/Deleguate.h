#ifndef DELEGUATE_H
#define DELEGUATE_H

#include <functional>

class UDeleguate
{
public:
    using Callback = std::function<void()>;

    UDeleguate() = default;

    void Broadcast();

    template <typename T, typename Method>
    void AddCallback(T *Obj, Method MethodToBind)
    {
        Callbacks.push_back([=]()
                            { (Obj->*MethodToBind)(); });
    }

private:
    std::vector<Callback> Callbacks;
};

#endif