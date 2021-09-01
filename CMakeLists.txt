cmake_minimum_required(VERSION 3.19)
project(ECS)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(Components)
include_directories(Systems)

add_executable(ECS
        Components/Component.hpp
        Systems/Movement.hpp
        Systems/SystemManager.hpp
        Systems/Systems.hpp
        Entity.hpp
        EntityManager.hpp
        main.cpp)
