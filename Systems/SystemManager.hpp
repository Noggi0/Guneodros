#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include "../Entity.hpp"
#include "Systems.hpp"
#include <vector>

class SystemManager {
    public:
        SystemManager() {
            this->systemList.reserve(10);
        };
        void addSystem(ISystem *system) {
            this->systemList.push_back(system);
        };
        void update() {
            for (auto it = this->systemList.begin(); it != this->systemList.end(); ++it) {
                (*it)->update();
            }
        };
        void notifyDelete(Entity ID) {
            for (auto it = this->systemList.begin(); it != this->systemList.end(); ++it) {
                (*it)->tryDelete(ID);
            }
        }
        void notifySystems(Entity ID, std::string tag) {
            for (auto it = this->systemList.begin(); it != this->systemList.end(); ++it) {
                (*it)->tryAdd(ID, tag);
            }
        };
        ~SystemManager() {
        };
    private:
        std::vector<ISystem *> systemList;
};
#endif /* !SYSTEM_MANAGER_HPP */
