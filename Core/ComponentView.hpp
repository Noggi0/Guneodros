#ifndef COMPONENT_VIEW_HPP
#define COMPONENT_VIEW_HPP

#include "../Components/Component.hpp"
#include "Entity.hpp"
#include "ComponentStorage.hpp"
#include "ViewsState.hpp"
#include "../Utils/UniqueTypesInPack.hpp"
#include <span>
#include <iterator>
#include <tuple>
#include <array>
#include <algorithm>

class ViewsGuard {
public:
    explicit ViewsGuard(ViewsState &state) : state(&state) {
        this->state->viewAcquired();
    }

    ViewsGuard(const ViewsGuard &other) noexcept : state(other.state) {
        if (this->state)
            this->state->viewAcquired();
    }

    ViewsGuard(ViewsGuard &&other) noexcept : state(other.state) {
        other.state = nullptr;
    }

    ~ViewsGuard() {
        if (this->state)
            this->state->viewReleased();
    }
private:
    ViewsState *state;
};


template<typename... Components>
class ComponentView {
    static_assert(sizeof...(Components) > 0, "At least one component type must be specified");
    static_assert(UniqueTypesInPack<std::remove_const_t<Components>...>::value, "All component types must be unique");

    template<typename T>
    using StoragePointer = std::conditional_t<
        std::is_const_v<T>,
        const ComponentStorage<std::remove_const_t<T>>*,
        ComponentStorage<T>*
    >;
public:
    using Reference = std::tuple<Entity, Components&...>;

    ComponentView(ViewsState &viewsState, StoragePointer<Components>... storages) : viewsState(viewsState), storages({storages...}) {};

    class Iterator {
    public:
        Iterator(const ComponentView& view, std::span<const Entity> entities) : guard(view.viewsState), view(&view), entities(entities), index(0) {
            this->skipUnmatchedEntities();
        };

        Reference operator*() const {
            return this->view->getComponentsForEntity(this->entities[this->index]);
        };

        Iterator& operator++() {
            ++this->index;
            this->skipUnmatchedEntities();
            return *this;
        };

        bool operator==(std::default_sentinel_t) const {
            return this->index >= entities.size();
        };
    
    private:
        void skipUnmatchedEntities() {
            while (this->index < this->entities.size() && !this->view->matches(this->entities[this->index])) {
                ++this->index;
            }
        }
        ViewsGuard guard;
        const ComponentView* view;
        std::span<const Entity> entities;
        std::size_t index;
    };

    Iterator begin() const {
        return Iterator(*this, this->selectCandidateEntities());
    };

    std::default_sentinel_t end() const {
        return {};
    };

private:
    std::span<const Entity> selectCandidateEntities() const {
        return std::apply([](auto *... storage)
                -> std::span<const Entity> {
                if (((storage == nullptr) || ...))
                    return {};

                std::array<std::span<const Entity>, sizeof...(Components)> candidates {
                    storage->getEntities()...
                };

                auto smallest = std::min_element(
                    candidates.begin(), candidates.end(),
                    [](auto first, auto second) {
                        return first.size() < second.size();
                    });

                return *smallest;
            }, this->storages);
    }

    bool matches(Entity ID) const {
        return std::apply([ID](auto *... storage) {
            return ((storage->has(ID)) && ...);
        }, this->storages);
    }

    Reference getComponentsForEntity(Entity ID) const {
        return std::apply([ID](auto *... storage) {
            return Reference(ID, storage->get(ID)...);
        }, this->storages);
    }
    ViewsState &viewsState;
    std::tuple<StoragePointer<Components>...> storages;
};

#endif // COMPONENT_VIEW_HPP