#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "../Core/Entity.hpp"
#include <string>
#include <memory>

class Position {
    public:
        Position(float x = 0, float y = 0, float z = 0) {
            this->x = x;
            this->y = y;
            this->z = z;
        };
        float x, y, z;
};

class Velocity {
    public:
        Velocity(double x = 0, double y = 0, double z = 0) {
            this->Vx = x;
            this->Vy = y;
            this->Vz = z;
        };
        double Vx, Vy, Vz;
};

class Rotation {
    // ! Gotta use quaternions for this one I guess ?
    public:
        Rotation(int x = 0, int y = 0, int z = 0) {
            this->Rx = x;
            this->Ry = y;
            this->Rz = z;
        };
        int Rx, Ry, Rz;
};

class Rigidbody {
    public:
        Rigidbody(bool gravity = true) {
            this->subjectToGravity = gravity;
        };
        bool subjectToGravity;
};

class Sprite {
    public:
        Sprite(const std::string& texture, int sizeX, int sizeY) {
            this->pathToTexture = texture;
            this->sizeX = sizeX;
            this->sizeY = sizeY;
        };
        std::string pathToTexture;
        int sizeX, sizeY;
};

class BoxCollider
{
    public:
        BoxCollider(int x = 0, int y = 0, int width = 0, int height = 0) {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
        };
        int x, y, width, height;
        bool triggered = false;
};

#endif /* !COMPONENT_HPP */
