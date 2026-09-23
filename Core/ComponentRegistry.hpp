#ifndef COMPONENT_REGISTRY_HPP
#define COMPONENT_REGISTRY_HPP

#include "../Components/Component.hpp"
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <utility>

class ComponentRegistry {
    public:
        template <class T, class... Args>
        T &emplace(Entity ID, Args&&... args) {
            auto component = std::make_unique<T>(std::forward<Args>(args)...);
            if (component->id >= MAX_COMPONENT)
                throw std::out_of_range("Invalid component type");
            auto &components = this->componentMap[ID];
            for (const auto &existing : components) {
                if (existing->id == component->id)
                    throw std::logic_error("Entity already has this component");
            }
            T &result = *component;
            components.push_back(std::move(component));
            return result;
        };

        template <class T>
        const T *tryGet(Entity ID) const {
            auto it = this->componentMap.find(ID);
            if (it == this->componentMap.end())
                return nullptr;
            for (const auto &component : it->second) {
                if (auto *result = dynamic_cast<const T*>(component.get()))
                    return result;
            }
            return nullptr;
        };

        template <class T>
        T *tryGet(Entity ID) {
            return const_cast<T*>(std::as_const(*this).tryGet<T>(ID));
        };

        template <class T>
        void remove(Entity ID) {
            auto it = this->componentMap.find(ID);
            if (it == this->componentMap.end())
                return;
            auto &components = it->second;
            components.erase(std::remove_if(components.begin(), components.end(),
                [](const auto &component) {
                    return dynamic_cast<T*>(component.get()) != nullptr;
                }), components.end());
        };

        Signature getSignature(Entity ID) const {
            Signature signature;
            auto it = this->componentMap.find(ID);
            if (it != this->componentMap.end()) {
                for (const auto &component : it->second)
                    signature.set(component->id);
            }
            return signature;
        };

        void destroyEntity(Entity ID) {
            this->componentMap.erase(ID);
        };

    private:
        std::unordered_map<Entity, std::vector<std::unique_ptr<IComponent>>> componentMap;
};

#endif /* !COMPONENT_REGISTRY_HPP */
