#ifndef COMPONENTSTORAGE_HPP
#define COMPONENTSTORAGE_HPP

#include "Entity.hpp"
#include <vector>
#include <memory>
#include <span>
#include <stdexcept>
#include <utility>
#include <type_traits>

constexpr std::size_t EMPTY = -1;

class IComponentStorage {
    public:
        virtual ~IComponentStorage() = default;
        virtual void remove(Entity ID) = 0;
};


template<typename T>
class ComponentStorage : public IComponentStorage {
    static_assert(std::is_nothrow_move_assignable<T>::value, "Component type must support noexcept move assignment");
    static_assert(std::is_nothrow_move_constructible<T>::value, "Component type must support noexcept move construction");
public:
    ComponentStorage() : sparse(MAX_ENTITIES, EMPTY) {
    }

    // ComponentStorages are owned through unique_ptrs in ComponentRegistry
    // so we delete copy/move constructors and assignment operators to prevent accidental copies or moves.
    ComponentStorage(const ComponentStorage&) = delete;
    ComponentStorage& operator=(const ComponentStorage&) = delete;
    ComponentStorage(ComponentStorage&&) = delete;
    ComponentStorage& operator=(ComponentStorage&&) = delete;

    template<typename... Args>
    T &emplace(Entity ID, Args&&... args) {
        if (ID >= sparse.size())
            throw std::out_of_range("Entity ID exceeds maximum entities");
        if (sparse[ID] != EMPTY)
            throw std::logic_error("Entity already has this component");

        const std::size_t index = data.size();
        entities.push_back(ID);
        
        try {
            data.emplace_back(std::forward<Args>(args)...);
        } catch (...) {
            entities.pop_back();
            throw;
        }

        sparse[ID] = index;
        return data.back();
    }

    const T* tryGet(Entity ID) const {
        if (ID >= sparse.size() || sparse[ID] == EMPTY)
            return nullptr;
        return &data[sparse[ID]];
    }

    T* tryGet(Entity ID)  {
        if (ID >= sparse.size() || sparse[ID] == EMPTY)
            return nullptr;
        return &data[sparse[ID]];
    }

    const T& get(Entity ID) const {
        auto component = tryGet(ID);
        if (!component)
            throw std::out_of_range("Entity does not have this component");
        return *component;
    }

    T& get(Entity ID)  {
        auto component = tryGet(ID);
        if (!component)
            throw std::out_of_range("Entity does not have this component");
        return *component;
    }

    bool has(Entity ID) const {
        return ID < sparse.size() && sparse[ID] != EMPTY;
    }

    void remove(Entity ID) override {
        if (ID >= sparse.size() || sparse[ID] == EMPTY)
            return;
            
        const std::size_t index = sparse[ID];
        const std::size_t lastIndex = data.size() - 1;

        if (index != lastIndex) {
            std::swap(data[index], data[lastIndex]);
            std::swap(entities[index], entities[lastIndex]);
            sparse[entities[index]] = index;
        }
        data.pop_back();
        entities.pop_back();
        sparse[ID] = EMPTY;
    }

    void clear() noexcept {
        sparse.assign(MAX_ENTITIES, EMPTY);
        entities.clear();
        data.clear();
    }

    std::size_t size() const noexcept {
        return data.size();
    }

    // Get a read-only view of the entities that have this component type.
    std::span<const Entity> getEntities() const noexcept {
        return entities;
    }

private:
    std::vector<std::size_t> sparse;
    std::vector<Entity> entities;
    std::vector<T> data;
};

#endif // COMPONENTSTORAGE_HPP