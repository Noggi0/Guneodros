#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Entity.hpp"
#include <string>

class IComponent {
    public:
        virtual ~IComponent() = default;
        std::string tag;
};

class Crashed : public IComponent {
    public:
        Crashed() {
            this->tag = "Crashed";
        };
        ~Crashed(){};
};

class Position : public IComponent {
    public:
        Position() {
            this->tag = "Position";
        };
        ~Position() {};
        int x, y, z = 0;
};

class Velocity : public IComponent {
    public:
        Velocity() {
            this->tag = "Velocity";
        };
        ~Velocity() {};
        double Vx, Vy, Vz = 0.0;
};
#endif /* !COMPONENT_HPP */
