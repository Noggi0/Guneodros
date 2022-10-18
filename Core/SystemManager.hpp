#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include "./Entity.hpp"
#include "../Systems/Systems.hpp"
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
            for (auto &system : this->systemList) {
                system->update();
            }
        };

        /**
         * @brief Notifies every registered system that an entity or a component attached to an entity has been destroyed,
         * and tries to remove it from their EntityList.
         * 
         * @param ID Entity to delete.
         */
        void notifyEntityDeleted(Entity ID) {
            for (auto &system : this->systemList) {
                system->tryDeleteEntity(ID);
            }
        };

        /**
         * @brief Notifies every registered system that a component have been added to an Entity.
         * If the Entity matches the requirements for a System, then the Entity is added to the System's EntityList.
         * 
         * @param ID Entity.
         * @param signature new Entity's signature.
         */
        void notifyEntityModified(Entity ID, const Signature& signature) {
            for (auto &system : this->systemList) {
                system->updateEntityList(ID, signature);
            }
        };

        ~SystemManager() {
        };
    private:
        std::vector<ISystem *> systemList;
};
#endif /* !SYSTEM_MANAGER_HPP */
