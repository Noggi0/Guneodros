#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include "./Entity.hpp"
#include "../Systems/Systems.hpp"
#include <vector>
#include <memory>
#include <utility>

class SystemManager {
    public:
        SystemManager() {
        };
        
        /**
         * Registers a new System.
         * @param system System to add.
         */ 
        void addSystem(std::unique_ptr<ISystem> system) {
            this->systemList.push_back(std::move(system));
        };

        /**
         * Runs update on every System registered.
         */
        void update(World &world, float deltaTime) {
            for (auto &system : this->systemList) {
                system->update(world, deltaTime);
            }
        };

        ~SystemManager() {
        };
    private:
        std::vector<std::unique_ptr<ISystem>> systemList;
};
#endif /* !SYSTEM_MANAGER_HPP */
