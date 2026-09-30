#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include "./Entity.hpp"
#include "../Systems/Systems.hpp"
#include "../Utils/Guard.hpp"
#include <vector>
#include <memory>
#include <utility>
#include <stdexcept>

class SystemManager {
    public:
        SystemManager() = default;
        
        /**
         * Registers a new System.
         * @param system System to add.
         */ 
        void addSystem(std::unique_ptr<ISystem> system) {
            if (this->isUpdating)
                throw std::logic_error("Cannot add system while updating");
            this->systemList.push_back(std::move(system));
        };

        /**
         * Runs update on every System registered.
         */
        void update(World &world, float deltaTime) {
            Guard guard(this->isUpdating);
            
            for (auto &system : this->systemList) {
                system->update(world, deltaTime);
            }
        };

        ~SystemManager() = default;
    private:
        std::vector<std::unique_ptr<ISystem>> systemList;
        bool isUpdating = false;
};
#endif /* !SYSTEM_MANAGER_HPP */
