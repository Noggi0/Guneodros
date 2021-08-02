#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include "Entity.hpp"
#include "Components/Component.hpp"
#include "Systems/SystemManager.hpp"
#include <queue>
#include <unordered_map>
#include <vector>
#include <chrono>

class EntityManager  
{
	public:
        /**
         * EntityManager's constructor.
         * Initialize Entities' container and sets up the clock.
         */
		EntityManager() {
			for (Entity entity = 0; entity < MAX_ENTITES; ++entity) {
				AvailableEntities.push(entity);
				this->componentMap[entity];
			}
			this->sysMgr = new SystemManager;
			this->elapsed = std::chrono::high_resolution_clock::now();
		};

		/**
		 * @return the number of entities currently in use.
		 */
		Entity getAliveEntities() {
			return this->AliveEntities;
		};

		/**
		 * Creates a new emtpy Entity.
		 * @return the created Entity.
		 */
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

		/**
		 * Deletes the designated Entity.
		 * @param ID Entity to delete.
		 */
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

		/**
		 * Adds a new component to the given Entity.
		 * @param ID Entity.
		 * @param component Component to be added.
		 */
		void AddComponent(Entity ID, IComponent *component) {
			if (this->componentMap.size() != MAX_COMPONENT)
				this->componentMap.at(ID).push_back(component);
			this->sysMgr->notifySystems(ID, component->tag);
		};

		/**
		 * Registers a new System to the SystemManager.
		 * @param sys System to be added.
		 */
		void registerSystem(ISystem *sys) {
			this->sysMgr->addSystem(sys);
		};

		/**
		 * Updates every system.
		 */
		void update() {
			if ((this->deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->elapsed).count()) > this->clock) {
				this->sysMgr->update();
				this->elapsed = std::chrono::high_resolution_clock::now();
			}
		};

		/**
		 * Returns the time since last frame.
		 * @return deltaTime - float.
		 */
		float getDeltaTime() const {
			return this->deltaTime;
		};

		/**
		 * Check and returns the Component attached to the given Entity.
		 * @tparam T Type of the target Component.
		 * @param ID Entity to be checked.
		 * @param tag Tag of the target Component.
		 * @return Reference to the Component. Please check if the component is not of type Crashed if it's not required by the system.
		 */
		template <class T>
		T &getComponent(Entity ID, std::string tag) {
			for (std::size_t i = 0; i < this->componentMap.at(ID).size(); ++i) {
				if (this->componentMap.at(ID).at(i)->tag == tag) {
					T* toReturn = static_cast<T*>(this->componentMap.at(ID).at(i));
					return *toReturn;
				}
			}
			IComponent *err = new Crashed();
			return *static_cast<T*>(err);
		};
		
		/**
		 * EntityManager's destructor.
		 */
		~EntityManager() {
			this->sysMgr->~SystemManager();
		};
	private:
		std::queue<Entity> AvailableEntities {};
		uint32_t AliveEntities;
		std::unordered_map<int, std::vector<IComponent *>> componentMap;
		SystemManager *sysMgr;
		float clock = 1 / 60.0f;
		float deltaTime;
		std::chrono::_V2::high_resolution_clock::time_point elapsed;
};
#endif /* !ENTITY_MANAGER_HPP */