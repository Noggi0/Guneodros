#ifndef COMPONENT_REGISTRY_HPP
#define COMPONENT_REGISTRY_HPP

#include "../Components/Component.hpp"
#include "ComponentStorage.hpp"
#include "ComponentView.hpp"
#include "ViewsState.hpp"
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <utility>
#include <typeindex>

class ComponentRegistry {
    public:
        ComponentRegistry() = default;

        ComponentRegistry(ComponentRegistry &other) = delete;
        ComponentRegistry &operator=(ComponentRegistry &other) = delete;
        ComponentRegistry(ComponentRegistry &&other) = delete;
        ComponentRegistry &operator=(ComponentRegistry &&other) = delete;

        template<typename T, typename... Args>
        T &emplace(EntityIndex entity, Args&&... args) {
            if (this->viewsState.hasActiveViews())
                throw std::logic_error("Cannot modify components while views are active");
            return ensureStorage<T>().emplace(entity, std::forward<Args>(args)...);
        }

        template<typename T>
        const T* tryGet(EntityIndex entity) const {
            if (auto *storage = getStorage<T>())
                return storage->tryGet(entity);
            return nullptr;
        }

        template<typename T>
        T* tryGet(EntityIndex entity) {
            if (auto *storage = getStorage<T>())
                return storage->tryGet(entity);
            return nullptr;
        }

        template<typename T>
        const T& get(EntityIndex entity) const {
            const T* component = tryGet<T>(entity);
            if (!component)
                throw std::out_of_range("Entity does not have this component");
            return *component;
        }

        template<typename T>
        T& get(EntityIndex entity) {
            T* component = tryGet<T>(entity);
            if (!component)
                throw std::out_of_range("Entity does not have this component");
            return *component;
        }

        template<typename T>
        void remove(EntityIndex entity) {
            if (this->viewsState.hasActiveViews())
                throw std::logic_error("Cannot destroy entity while views are active");
            if (auto *storage = getStorage<T>())
                storage->remove(entity);
        }

        template<typename T>
        void clear() {
            if (this->viewsState.hasActiveViews())
                throw std::logic_error("Cannot destroy entity while views are active");
            if (auto *storage = getStorage<T>())
                storage->clear();
        }

        void destroyEntity(EntityIndex entity) {
            if (this->viewsState.hasActiveViews())
                throw std::logic_error("Cannot destroy entity while views are active");
            for (const auto &entry : componentStorages)
                entry.second->remove(entity);
        }

        template<typename T>
        std::size_t size() const {
            if (auto *storage = getStorage<T>())
                return storage->size();
            return 0;
        }

        template<typename... Components>
        ComponentView<Components...> view(const EntityManager &entities) {
            return ComponentView<Components...>(viewsState, entities, getStorage<std::remove_const_t<Components>>()...);
        }

        template<typename... Components>
        ComponentView<const Components...> view(const EntityManager &entities) const {
            return ComponentView<const Components...>(viewsState, entities, getStorage<std::remove_const_t<Components>>()...);
        }

        bool hasActiveViews() const {
            return this->viewsState.hasActiveViews();
        }

    private:
        template<typename T>
        ComponentStorage<T> &ensureStorage() {
            if (auto *storage = getStorage<T>())
                return *storage;
            
            auto storage = std::make_unique<ComponentStorage<T>>();
            auto [it, ok] = componentStorages.emplace(std::type_index(typeid(T)), std::move(storage));

            if (!ok)
                throw std::runtime_error("Failed to create component storage for type");

            return *static_cast<ComponentStorage<T>*>(it->second.get());
        }

        template<typename T>
        const ComponentStorage<T> *getStorage() const {
            auto it = componentStorages.find(std::type_index(typeid(T)));
            if (it == componentStorages.end())
                return nullptr;
            return static_cast<const ComponentStorage<T>*>(it->second.get());
        }

        template<typename T>
        ComponentStorage<T> *getStorage() {
            auto it = componentStorages.find(std::type_index(typeid(T)));
            if (it == componentStorages.end())
                return nullptr;
            return static_cast<ComponentStorage<T>*>(it->second.get());
        }

        std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> componentStorages;
        mutable ViewsState viewsState;
};

#endif /* !COMPONENT_REGISTRY_HPP */
