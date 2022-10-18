#ifndef __GUNEODROS_RENDER_SYSTEM_HPP__
#define __GUNEODROS_RENDER_SYSTEM_HPP__

#include "Systems.hpp"
#include "../Core/EntityManager.hpp"

extern EntityManager Engine;

class RenderSystem : public ISystem {
    public:
        RenderSystem() {
            this->signature.set(Components::TypeToID::Position);
            this->signature.set(Components::TypeToID::Sprite);
        };
        void update() override {
            for (const auto &entity : this->entityList) {
                const auto &position = Engine.getComponent<Position>(entity, Components::TypeToID::Position);
                const auto &sprite = Engine.getComponent<Sprite>(entity, Components::TypeToID::Sprite);
                std::cout << "Entity " << entity << " has Position: " << position.x << " " << position.y << " and Sprite: " << sprite.pathToTexture << std::endl;
            }
        };
        ~RenderSystem() = default;
};

#endif /* __GUNEODROS_RENDER_SYSTEM_HPP__ */