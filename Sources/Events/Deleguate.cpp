#include "Deleguate.h"

void UDeleguate::Broadcast()
{
    for (auto &CallbackToCall : Callbacks)
        CallbackToCall();
}