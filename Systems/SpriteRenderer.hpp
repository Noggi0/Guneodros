#ifndef __GUNEODROS_RENDER_SYSTEM_HPP__
#define __GUNEODROS_RENDER_SYSTEM_HPP__

#include "Systems.hpp"
#include "../Core/EntityManager.hpp"
#include "../Core/TextureManager.hpp"

extern EntityManager Engine;

// When finished, rename it to Render2D

/*
    Render2D should have a handle to the targeted Window. DONE
    Render2D should use the draw calls for each entity.
    Render2D should optimize how the sprites are managed (like not loading the texture at every draw call)
 */

class SpriteRenderer : public ISystem {
    public:
        SpriteRenderer() {
            this->signature.set(Components::TypeToID::Position);
            this->signature.set(Components::TypeToID::Sprite);

            this->window = Engine.getWindow();
            this->renderer = SDL_CreateRenderer(Engine.getWindow(), -1, SDL_RENDERER_ACCELERATED);
            if (!this->renderer)
                throw std::runtime_error(std::string("Could not create SpriteRenderer.") + SDL_GetError());
        };
        void update() override {
            SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255); // black
            SDL_RenderClear(this->renderer);
            for (const auto &entity : this->entityList) {
                const auto &position = Engine.getComponent<Position>(entity, Components::TypeToID::Position);
                const auto &sprite = Engine.getComponent<Sprite>(entity, Components::TypeToID::Sprite);

                SDL_Texture *texture = this->textures.loadTexture(this->renderer, sprite.pathToTexture);

                SDL_Rect rect = { position.x, position.y, sprite.sizeX, sprite.sizeY };
                SDL_RenderCopy(this->renderer, texture, nullptr, &rect);
            }
            SDL_RenderPresent(this->renderer);
        };
        ~SpriteRenderer() {
            SDL_DestroyRenderer(this->renderer);
        };

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        TextureManager textures;
};

#endif /* __GUNEODROS_RENDER_SYSTEM_HPP__ */