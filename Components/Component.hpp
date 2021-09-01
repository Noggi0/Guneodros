#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "../Entity.hpp"
#include <string>
#include <memory>

/**
 * Component's Interface.
 * Every Component needs to derivate from this Interface.
 * For now, it only contains a tag. It is used to handle Components generically.
 */ 
class IComponent {
    public:
        virtual ~IComponent() = default;
        std::string tag;
};


/**
 * Default Component.
 * A Crashed object is returned if we cannot resolve the type of the component for a given Entity.
 * It is used to detect error, but it shouldn't happen at all.
 */
class Crashed : public IComponent {
    public:
        Crashed() {
            this->tag = "Crashed";
        };
        ~Crashed(){};
};

class Position : public IComponent {
    public:
        Position(int x = 0, int y = 0, int z = 0) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->tag = "Position";
        };
        ~Position() {};
        int x, y, z;
};

class Velocity : public IComponent {
    public:
        Velocity(double x = 0, double y = 0, double z = 0) {
            this->Vx = x;
            this->Vy = y;
            this->Vz = z;
            this->tag = "Velocity";
        };
        ~Velocity() {};
        double Vx, Vy, Vz;
};

class Rotation : public IComponent {
    public:
        Rotation(int x = 0, int y = 0, int z = 0) {
            this->Rx = x;
            this->Ry = y;
            this->Rz = z;
            this->tag = "Rotation";
        };
        ~Rotation() {};
        int Rx, Ry, Rz;
};

class Rigidbody : public IComponent {
    public:
        explicit Rigidbody() {
            this->tag = "Rigidbody";
        };
        Rigidbody(bool gravity) {
            this->subjectToGravity = gravity;
        };
        ~Rigidbody() {};
        bool subjectToGravity = true;
};

class Sprite : public IComponent {
    public:
        Sprite(std::string texture) {
            if (texture.empty()) {
                // TODO: Implement Sprite and Texture loading;
            }
            this->tag = "Sprite";
        };
        ~Sprite() {};
        std::string pathToTexture;
};

class Model3D : public IComponent {
    public:
        Model3D(std::string model) {
            if (model.empty()) {
                // TODO: Implement 3D object loading;
            }
            this->tag = "Model3D";
        };
        ~Model3D() {};
        std::string pathToModel;
};

class Camera : public IComponent {
    public:
        Camera() {

        };
        ~Camera() {

        };
        int x, y, z;
        std::unique_ptr<IComponent> lookAt; // TODO : Maybe change the type to a Character Type. Gotta dive into this once Renderer is done.
};

class Character : public IComponent {
    public:
        Character() {
            // TODO : Define what are the Character's caracteristics (no pun intended).
        };
        ~Character() {

        };
};

#endif /* !COMPONENT_HPP */
