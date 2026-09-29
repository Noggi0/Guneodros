#ifndef WORLD_HPP
#define WORLD_HPP

#include "EntityManager.hpp"
#include "ComponentRegistry.hpp"
#include "SystemManager.hpp"

class World {
    public:
        Entity createEntity() {
            if (this->components.hasActiveViews())
                throw std::logic_error("Cannot create entity while views are active");
            Entity ID = this->entities.createEntity();
            return ID;
        };

        void destroyEntity(Entity ID) {
            this->requireEntity(ID);
            this->components.destroyEntity(ID);
            this->entities.destroyEntity(ID);
        };

        bool isAlive(Entity ID) const {
            return this->entities.isAlive(ID);
        };

        Entity getAliveEntities() const {
            return this->entities.getAliveEntities();
        };

        template <class T, class... Args>
        T &emplace(Entity ID, Args&&... args) {
            this->requireEntity(ID);
            T &component = this->components.emplace<T>(ID, std::forward<Args>(args)...);
            return component;
        };

        template <class T>
        T *tryGet(Entity ID) {
            return this->isAlive(ID) ? this->components.tryGet<T>(ID) : nullptr;
        };

        template <class T>
        const T *tryGet(Entity ID) const {
            return this->isAlive(ID) ? this->components.tryGet<T>(ID) : nullptr;
        };

        template <class T>
        bool has(Entity ID) const {
            return this->tryGet<T>(ID) != nullptr;
        };

        template <class T>
        T &get(Entity ID) {
            auto *component = this->tryGet<T>(ID);
            if (!component)
                throw std::out_of_range("Entity does not have this component");
            return *component;
        };

        template <class T>
        const T &get(Entity ID) const {
            auto *component = this->tryGet<T>(ID);
            if (!component)
                throw std::out_of_range("Entity does not have this component");
            return *component;
        };

        template <class T>
        void remove(Entity ID) {
            this->requireEntity(ID);
            this->components.remove<T>(ID);
        };

        template <class T, class... Args>
        T &addSystem(Args&&... args) {
            auto system = std::make_unique<T>(std::forward<Args>(args)...);
            T &result = *system;
            this->systems.addSystem(std::move(system));
            return result;
        };

        void update(float deltaTime) {
            this->systems.update(*this, deltaTime);
        };

        template <class... Components>
        auto view() {
            static_assert(sizeof...(Components) > 0, "At least one component type must be specified");
            return this->components.view<Components...>();
        };

        template <class... Components>
        auto view() const {
            static_assert(sizeof...(Components) > 0, "At least one component type must be specified");
            return this->components.view<Components...>();
        };

    private:
        void requireEntity(Entity ID) const {
            if (!this->isAlive(ID))
                throw std::out_of_range("This entity does not exist");
        };

        EntityManager entities;
        ComponentRegistry components;
        SystemManager systems;
};

#endif /* !WORLD_HPP */
