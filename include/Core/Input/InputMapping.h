#pragma once

#include <unordered_map>
#include <vector>
#include "Core/Input/InputAction.h"
#include "Core/Input/InputRegistry.h"

class InputMapping
{
public:
    InputMapping();

    void AddInputBinding(InputCode key);
    void RemoveInputBinding(InputCode key);
    void AddActionToInput(InputCode key, InputAction* action);
    void RemoveActionFromInput(InputCode key, InputAction* action);

    //Add size limits to both map and vectors
    //Maybe swap vector with unordered_set, or add check for InputAction already in vector
    std::unordered_map<InputCode, std::vector<InputAction*>> bindings;
};