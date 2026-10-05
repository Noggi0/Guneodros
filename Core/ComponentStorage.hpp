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
        virtual void remove(EntityIndex entity) = 0;
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
    T &emplace(EntityIndex entity, Args&&... args) {
        if (entity >= sparse.size())
            throw std::out_of_range("Entity ID exceeds maximum entities");
        if (sparse[entity] != EMPTY)
            throw std::logic_error("Entity already has this component");

        const std::size_t index = data.size();
        entities.push_back(entity);
        
        try {
            data.emplace_back(std::forward<Args>(args)...);
        } catch (...) {
            entities.pop_back();
            throw;
        }

        sparse[entity] = index;
        return data.back();
    }

    const T* tryGet(EntityIndex entity) const {
        if (entity >= sparse.size() || sparse[entity] == EMPTY)
            return nullptr;
        return &data[sparse[entity]];
    }

    T* tryGet(EntityIndex entity) {
        if (entity >= sparse.size() || sparse[entity] == EMPTY)
            return nullptr;
        return &data[sparse[entity]];
    }

    const T& get(EntityIndex entity) const {
        auto component = tryGet(entity);
        if (!component)
            throw std::out_of_range("Entity does not have this component");
        return *component;
    }

    T& get(EntityIndex entity) {
        auto component = tryGet(entity);
        if (!component)
            throw std::out_of_range("Entity does not have this component");
        return *component;
    }

    bool has(EntityIndex entity) const {
        return entity < sparse.size() && sparse[entity] != EMPTY;
    }

    void remove(EntityIndex entity) override {
        if (entity >= sparse.size() || sparse[entity] == EMPTY)
            return;
            
        const std::size_t index = sparse[entity];
        const std::size_t lastIndex = data.size() - 1;

        if (index != lastIndex) {
            std::swap(data[index], data[lastIndex]);
            std::swap(entities[index], entities[lastIndex]);
            sparse[entities[index]] = index;
        }
        data.pop_back();
        entities.pop_back();
        sparse[entity] = EMPTY;
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
    std::span<const EntityIndex> getEntities() const noexcept {
        return entities;
    }

private:
    std::vector<std::size_t> sparse;
    std::vector<EntityIndex> entities;
    std::vector<T> data;
};

#endif /* COMPONENTSTORAGE_HPP */
