#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "../Core/Entity.hpp"
#include <string>
#include <memory>

/**
 * Component's Interface.
 * Every Component needs to derivate from this Interface.
 * For now, it only contains an ID. It is used to handle Components generically.
 */ 
class IComponent {
    public:
        virtual ~IComponent() = default;
        uint8_t id = -1;
};

/**
 * Default Component.
 * A Crashed object is returned if we cannot resolve the type of the component for a given Entity.
 * It is used to detect error, but it shouldn't happen at all.
 */
class Crashed : public IComponent {
    public:
        Crashed() {
            this->id = -1;
        };
        ~Crashed() = default;

};

class Position : public IComponent {
    public:
        Position(int x = 0, int y = 0, int z = 0) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->id = 0;
        };
        ~Position() = default;
        int x, y, z;
};

class Velocity : public IComponent {
    public:
        Velocity(double x = 0, double y = 0, double z = 0) {
            this->Vx = x;
            this->Vy = y;
            this->Vz = z;
            this->id = 1;
        };
        ~Velocity() {};
        double Vx, Vy, Vz;
};

class Rotation : public IComponent {
    // ! Gotta use quaternions for this one I guess ?
    public:
        Rotation(int x = 0, int y = 0, int z = 0) {
            this->Rx = x;
            this->Ry = y;
            this->Rz = z;
            this->id = 2;
        };
        ~Rotation() {};
        int Rx, Ry, Rz;
};

class Rigidbody : public IComponent {
    public:
        explicit Rigidbody() {
            this->id = 3;
        };
        Rigidbody(bool gravity) {
            this->subjectToGravity = gravity;
            this->id = 3;
        };
        ~Rigidbody() {};
        bool subjectToGravity = true;
};

class Sprite : public IComponent {
    public:
        Sprite(const std::string& texture, int sizeX, int sizeY) {
            this->pathToTexture = texture;
            this->sizeX = sizeX;
            this->sizeY = sizeY;
            this->id = 4;
        };
        ~Sprite() {};
        std::string pathToTexture;
        int sizeX, sizeY;
};

class Model3D : public IComponent {
    public:
        Model3D(const std::string& model) {
            if (model.empty()) {
                // TODO: Implement 3D object loading;
            }
            this->id = 5;
        };
        ~Model3D() {};
        std::string pathToModel;
};

class Camera : public IComponent {
    public:
        Camera() {
            this->id = 6;
        };
        ~Camera() {

        };
        int x, y, z;
        std::unique_ptr<IComponent> lookAt; // TODO : Maybe change the type to a Character Type. Gotta dive into this once Renderer is done.
};

class Character : public IComponent {
    public:
        Character() {
            this->id = 7;
            // TODO : Define what are the Character's caracteristics (no pun intended).
        };
        ~Character() {};
};

#endif /* !COMPONENT_HPP */
