#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "Entity.hpp"
#include <vector>
#include <list>
#include <algorithm>
#include <string>

class ISystem {
        public:
            virtual void update() = 0;
            virtual ~ISystem() = default;
            void tryAdd(Entity ID, std::string tag) {
                if (std::find(this->required.begin(), this->required.end(), tag) != this->required.end() && std::find(this->entityList.begin(), this->entityList.end(), ID) == this->entityList.end())
                    entityList.push_back(ID);
            };
            void tryDelete(Entity ID) {
                std::vector<Entity>::iterator it;
                std::cout << "size : " << this->entityList.size() << std::endl;
                if ((it = std::find(this->entityList.begin(), this->entityList.end(), ID)) != this->entityList.end()) {
                    entityList.erase(it);
                    std::cout << "size : " << this->entityList.size() << std::endl;
                }
            };
            std::string tag;
        protected:
            std::list<std::string> required;
            std::vector<Entity> entityList;
};

#endif /* !SYSTEMS_HPP */