#include "InputMapping.h"

InputMapping::InputMapping()
{
}

void InputMapping::AddInputBinding(InputCode key)
{
    if(key < 0)
        return;
    if(!bindings.contains(key))
    {
        bindings[key] = std::vector<InputAction*>();
    }
}

void InputMapping::RemoveInputBinding(InputCode key)
{
    // This check is not needed here
    if(key < 0)
        return;
    if(bindings.contains(key))
    {
        //bindings[key].clear();
        bindings.erase(key);
    }
}

void InputMapping::AddActionToInput(InputCode key, InputAction* action)
{
    if(key < 0)
        return;
    bindings[key].push_back(action);
}

void InputMapping::RemoveActionFromInput(InputCode key, InputAction *action)
{
    // This check is not needed here
    if(key < 0)
        return;
    if(bindings.contains(key))
    {
        auto& actions = bindings[key];
        auto it = std::find(actions.begin(), actions.end(), action);
        if(it != actions.end())
        {
            actions.erase(it);
        }
    }
}
