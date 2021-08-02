#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include "../Entity.hpp"
#include "Systems.hpp"
#include <vector>

class SystemManager {
    public:
        SystemManager() {
        };
        
        /**
         * Registers a new System.
         * @param system System to add.
         */ 
        void addSystem(ISystem *system) {
            this->systemList.push_back(system);
        };

        /**
         * Runs update on every System registered.
         */
        void update() {
            for (auto it = this->systemList.begin(); it != this->systemList.end(); ++it) {
                (*it)->update();
            }
        };

        /**
         * @brief Notifies every registered system that an entity or a component attached to an entity has been destroyed,
         * and tries to remove it from their EntityList.
         * 
         * @param ID Entity to delete.
         */
        void notifyDelete(Entity ID) {
            for (auto it = this->systemList.begin(); it != this->systemList.end(); ++it) {
                (*it)->tryDelete(ID);
            }
        };

        /**
         * @brief Notifies every registered system that a component have been added to an Entity.
         * If the Entity matches the requirements for a System, then the Entity is added to the System's EntityList.
         * 
         * @param ID Entity.
         * @param tag Component's tag added to the Entity.
         */
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
