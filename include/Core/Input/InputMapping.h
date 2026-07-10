#pragma once

#include <unordered_map>
#include <vector>
#include "Core/Input/InputAction.h"

class InputMapping
{
public:
    InputMapping();

    void AddInputBinding(int key);
    void AddActionToInput(int key, InputAction* action);

    //Add size limits to both map and vectors
    //Maybe swap vector with unordered_set, or add check for InputAction already in vector
    std::unordered_map<int, std::vector<InputAction*>> bindings;
};