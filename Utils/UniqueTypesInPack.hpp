#ifndef UNIQUE_TYPES_IN_PACK_HPP
#define UNIQUE_TYPES_IN_PACK_HPP

#include <type_traits>

template<typename... Types>
struct UniqueTypesInPack : std::true_type {};

template<typename First, typename... Rest>
struct UniqueTypesInPack<First, Rest...>
    : std::bool_constant<(!std::is_same_v<First, Rest> && ...) &&
    UniqueTypesInPack<Rest...>::value> {};

#endif // UNIQUE_TYPES_IN_PACK_HPP