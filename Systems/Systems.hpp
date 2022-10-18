#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "../Core/Entity.hpp"
#include <vector>
#include <list>
#include <algorithm>
#include <string>

class ISystem {
        public:
            // Update Method, where all logic will be. Systems gotta implement this method.
            ISystem() {
                this->entityList.reserve(MAX_ENTITIES);
            };

            virtual void update() = 0;

            virtual ~ISystem() = default;

            void updateEntityList(Entity ID, const Signature& entitySignature) {
                auto it = std::find(this->entityList.begin(), this->entityList.end(), ID);
                // Entity doesn't exist in EntityList
                if (it == this->entityList.end()) {
                    // Entity matches the requirements for the System ==> add
                    if ((entitySignature & this->signature) == this->signature)
                        this->entityList.push_back(ID);
                } else {
                    // Entity is in EntityList and doesn't match the requirements for the System anymore ==> delete
                    if ((entitySignature & this->signature) != this->signature)
                        this->entityList.erase(it);
                }
            };

            void tryDeleteEntity(Entity ID) {
                std::vector<Entity>::iterator it;
                if ((it = std::find(this->entityList.begin(), this->entityList.end(), ID)) != this->entityList.end())
                    entityList.erase(it);
            };
        protected:
            std::vector<Entity> entityList;
            Signature signature;
};

#endif /* !SYSTEMS_HPP */