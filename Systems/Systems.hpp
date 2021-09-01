#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "../Entity.hpp"
#include <vector>
#include <list>
#include <algorithm>
#include <string>

class ISystem {
        public:
            // Update Method, where all logic will be. Systems gotta implement this method.
            virtual void update() = 0;

            virtual ~ISystem() = default;

            void tryAdd(Entity ID, std::string tag) {
                if (std::find(this->required.begin(), this->required.end(), tag) != this->required.end() && std::find(this->entityList.begin(), this->entityList.end(), ID) == this->entityList.end())
                    entityList.push_back(ID);
            };

            void tryDelete(Entity ID) {
                std::vector<Entity>::iterator it;
                if ((it = std::find(this->entityList.begin(), this->entityList.end(), ID)) != this->entityList.end())
                    entityList.erase(it);
            };

            std::string tag;
        protected:
            std::list<std::string> required;
            std::vector<Entity> entityList;
};

#endif /* !SYSTEMS_HPP */