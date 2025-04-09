#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#define SDL_MAIN_HANDLED

#include "./Entity.hpp"
#include "../Components/Component.hpp"
#include "./SystemManager.hpp"
#include "./InputManager.hpp"
#include "./WindowManager.hpp"
#include "./Logger.hpp"
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
            this->componentMap.reserve(MAX_ENTITIES);
            for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
				AvailableEntities.push(entity);
                this->componentMap[entity];
				this->componentMap.at(entity).reserve(MAX_COMPONENT);
				this->entitiesSignature[entity];
			}
			this->inputMgr = std::make_unique<InputManager>();
			this->sysMgr = std::make_unique<SystemManager>();
			this->windowMgr = std::make_unique<WindowManager>();
			this->elapsed = std::chrono::high_resolution_clock::now();
			this->isRunning = true;
			Logger::logInfo("EntityManager initialized");
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
		Entity newEntity () {
            if (AvailableEntities.empty()) {
                Logger::logError("Too many entities");
                return -1;
            }

            Entity ID = AvailableEntities.front();
            AvailableEntities.pop();
            AliveEntities++;
            return ID;
		};

		/**
		 * Deletes the designated Entity.
		 * @param ID Entity to delete.
		 */
		void deleteEntity(Entity ID) {
			if (ID > MAX_ENTITIES) {
                Logger::logError("This entity does not exist");
                return;
            }

            AvailableEntities.push(ID);
            AliveEntities -= 1;
            int mapSize = this->componentMap.size();
            this->componentMap.at(ID) = this->componentMap.at(mapSize -1);
            this->componentMap.erase(mapSize);
            this->sysMgr->notifyEntityDeleted(ID);
		};

		/**
		 * Adds a new component to the given Entity.
		 * @param ID Entity.
		 * @param component Component to be added.
		 */
		void addComponent(Entity ID, IComponent *component) {
			if (this->componentMap.at(ID).size() >= MAX_COMPONENT)
                return;

            this->componentMap.at(ID).push_back(component);
            this->entitiesSignature.at(ID).set(component->id, true);
            this->sysMgr->notifyEntityModified(ID, this->entitiesSignature.at(ID));

            // Logger::logInfo("Entity signature: " + this->entitiesSignature.at(ID).to_string() );
		};

		/**
		 * TODO: CHANGE THAT !! On perd la contiguité des components de l'entité en question.
		 * Gotta test, its probably fixed with the iter_swap changes.
		 * Removes a component from the given Entity.
		 * @param ID Entity.
		 * @param component Component to be removed.
		 */
		void removeComponent(Entity ID, IComponent *component) {
			auto componentPosition = std::find(this->componentMap.at(ID).begin(), this->componentMap.at(ID).end(), component);
			
			if (componentPosition != this->componentMap.at(ID).end()) {
				std::iter_swap(componentPosition, this->componentMap.at(ID).end());
				//this->componentMap.at(ID).erase(componentPosition);
				this->sysMgr->notifyEntityModified(ID, this->entitiesSignature.at(ID));
				this->entitiesSignature.at(ID).set(component->id, false);
                this->sysMgr->notifyEntityModified(ID, this->entitiesSignature.at(ID));
			}
			Logger::logInfo("Component " + std::to_string(component->id) + " removed from entity " + std::to_string(ID));
		}

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

		SDL_Window *getWindow() {
        	return this->windowMgr->getWindow();
		};

		/**
		 * Registers a new System to the SystemManager.
		 * @param sys System to be added.
		 */
		void registerSystem(ISystem *sys) {
			this->sysMgr->addSystem(std::move(sys));
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
		const bool isKeyPressed(char *key) const {
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
		 * @param componentID ID of the target Component.
		 * @return Reference to the Component. Please check if the component is not of type Crashed if it's not required by the system.
		 */
		template <class T>
		T &getComponent(Entity ID, Components::TypeToID componentID) const {
			for (std::size_t i = 0; i < this->componentMap.at(ID).size(); ++i) {
				if (this->componentMap.at(ID).at(i)->id == componentID) {
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
		std::unordered_map<Entity, std::vector<IComponent *>> componentMap;
		std::unordered_map<Entity, Signature> entitiesSignature;
		float clock = 1 / 60.0f;
		float deltaTime;
		std::chrono::high_resolution_clock::time_point elapsed;
	public:
		bool isRunning;
};
#endif /* !ENTITY_MANAGER_HPP */