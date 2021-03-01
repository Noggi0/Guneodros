#ifndef MOVEMENT_HPP_
#define MOVEMENT_HPP_

#include "Systems.hpp"
#include "EntityManager.hpp"

extern EntityManager EM;

class Movement : public ISystem {
    public:
        Movement() {
            this->required.push_back("Position");
            this->required.push_back("Velocity");
        };
        void update() {
            for (auto it = this->entityList.begin(); it != this->entityList.end(); ++it) {
                auto &Pos = EM.getComponent<Position>((*it), "Position");
                auto &Vel = EM.getComponent<Velocity>((*it), "Velocity");

                Pos.x += Vel.Vx;
                //std::cout << Pos.x << std::endl;
            }
        };
        ~Movement() {

        };

    protected:
    private:
};

#endif /* !MOVEMENT_HPP_ */
