#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include "Entity.hpp"
#include "Component.hpp"
#include "SystemManager.hpp"
#include <queue>
#include <unordered_map>
#include <vector>

class EntityManager  
{
	public:
		EntityManager() {
			for (Entity entity = 0; entity < MAX_ENTITES; ++entity) {
				AvailableEntities.push(entity);
				this->componentMap[entity];
			}
			this->sysMgr = new SystemManager;
		};
		Entity getAliveEntities() {
			return this->AliveEntities;
		};
		Entity NewEntity () {
			if (AvailableEntities.size() > 0) {
				Entity ID = AvailableEntities.front();
				AvailableEntities.pop();
				AliveEntities++;
				return ID;
			} else {
				std::cout << "Too many entities" << std::endl;
				return (-1);
			}
		};
		void DeleteEntity(Entity ID) {
			if (ID > MAX_ENTITES)
				std::cout << "This entity does not exist" << std::endl;
			else {
				AvailableEntities.push(ID);
				AliveEntities -= 1;
				int mapSize = this->componentMap.size();
				this->componentMap.at(ID) = this->componentMap.at(mapSize -1);
				this->componentMap.erase(mapSize);
				this->sysMgr->notifyDelete(ID);
			}
		};
		void AddComponent(Entity ID, IComponent *component) {
			if (this->componentMap.size() != MAX_COMPONENT)
				this->componentMap.at(ID).push_back(component);
			this->sysMgr->notifySystems(ID, component->tag);
		};
		void registerSystem(ISystem *sys) {
			this->sysMgr->addSystem(sys);
		};
		void update() {
			this->sysMgr->update();
		};
		template <class T>
		T &getComponent(Entity ID, std::string tag) {
			for (int i = 0; i < this->componentMap.at(ID).size(); ++i) {
				if (this->componentMap.at(ID).at(i)->tag == tag) {
					T* toReturn = static_cast<T*>(this->componentMap.at(ID).at(i));
					return *toReturn;
				}
			}
			IComponent *err = new Crashed();
			//return *static_cast<T*>(err);
		}
		~EntityManager() {
			this->sysMgr->~SystemManager();
		};
	private:
		std::queue<Entity> AvailableEntities {};
		uint32_t AliveEntities;
		std::unordered_map<int, std::vector<IComponent *>> componentMap;
		SystemManager *sysMgr;
};
#endif /* !ENTITY_MANAGER_HPP */