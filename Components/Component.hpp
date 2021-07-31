#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "../Entity.hpp"
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
        Rigidbody() {
            this->tag = "Rigidbody";
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

#endif /* !COMPONENT_HPP */
