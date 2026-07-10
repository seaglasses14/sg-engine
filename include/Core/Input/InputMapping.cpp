#include "InputMapping.h"

InputMapping::InputMapping()
{
}

void InputMapping::AddInputBinding(int key)
{
    if(bindings.find(key) == bindings.end())
    {
        bindings[key] = std::vector<InputAction*>();
    }
}

void InputMapping::AddActionToInput(int key, InputAction* action)
{
    bindings[key].push_back(action);
}
