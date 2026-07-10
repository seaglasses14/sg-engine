#pragma once

#include <string>
#include <unordered_set>
#include <variant>
#include <glm/glm.hpp>

enum ActionValueType
{
    BoolT,
    FloatT,
    Float2D
};
/*
template<typename... Ts>
struct VariantUnwrapper {
    std::variant<Ts...>& var;
    template <typename T>
    operator T() { return std::get<T>(var); }
};

template<typename... Ts>
VariantUnwrapper(std::variant<Ts...> &) -> VariantUnwrapper<Ts...>;
*/
using ActionValue = std::variant<
    bool, 
    float, 
    glm::vec2
>;

struct InputAction
{
	std::string id;
    ActionValueType type;
    std::unordered_set<int> activeBindings;
};