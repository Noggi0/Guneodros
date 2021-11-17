#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#define SDL_MAIN_HANDLED

#include "./Entity.hpp"
#include "../Components/Component.hpp"
#include "./SystemManager.hpp"
#include "./InputManager.hpp"
#include "./WindowManager.hpp"
#include <queue>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <memory>

class EntityManager  
{
	public:
        /**
         * EntityManager's constructor.
         * Initialize Entities' container and sets up the clock.
		 * Also initialize every manager we need to get the engine working.
         */
		EntityManager() {
			for (Entity entity = 0; entity < MAX_ENTITES; ++entity) {
				AvailableEntities.push(entity);
				this->componentMap[entity];
			}
			this->inputMgr = std::make_unique<InputManager>();
			this->sysMgr = std::make_unique<SystemManager>();
			this->windowMgr = std::make_unique<WindowManager>();
			this->elapsed = std::chrono::high_resolution_clock::now();
			this->isRunning = true;
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
			if (this->componentMap.size() != MAX_COMPONENT) {
				this->componentMap.at(ID).push_back(component);
				this->sysMgr->notifySystems(ID, component->tag);
			}
		};

		/**
		 * Creates a new window or throw an error if a window already exists. 
		 * Then sends a pointer to that window to the managers who need it.
		 * 
		 * @param title Title of the window
		 * @param width Width of the window
		 * @param height Height of the window
		 */
		void createWindow(std::string title, int width, int height, bool resizable) {
			this->windowMgr->createWindow(title, width, height, resizable);
			this->inputMgr->registerWindow(this->windowMgr->getWindow());
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
				this->inputMgr->update();
				this->sysMgr->update();
				this->elapsed = std::chrono::high_resolution_clock::now();
			}
			if (this->inputMgr->getCloseEvent()) {
				this->isRunning = false;
			}
		};

		/**
		 * Returns whether the key is pressed or not.
		 * @param key Name of the key to check.
		 */
		const bool isKeyPressed(char *key) {
			return this->inputMgr->isKeyPressed(key);
		}

		const Vec2<int> getMousePos() const {
			return this->inputMgr->getMousePosition();
		}

		/**
		 * Returns the time since last frame.
		 * @return deltaTime.
		 */
		const float getDeltaTime() const {
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
			
		};
	private:
		std::queue<Entity> AvailableEntities {};
		uint32_t AliveEntities;
		std::unique_ptr<SystemManager> sysMgr;
		std::unique_ptr<InputManager> inputMgr;
		std::unique_ptr<WindowManager> windowMgr;
		std::unordered_map<int, std::vector<IComponent *> > componentMap;
		float clock = 1 / 60.0f;
		float deltaTime;
		std::chrono::high_resolution_clock::time_point elapsed;
	public:
		bool isRunning;
};
#endif /* !ENTITY_MANAGER_HPP */