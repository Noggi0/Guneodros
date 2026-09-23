#ifndef __GUNEODROS_RENDER_SYSTEM_HPP__
#define __GUNEODROS_RENDER_SYSTEM_HPP__

#include "Systems.hpp"
#include "../Core/World.hpp"
#include "../Core/TextureManager.hpp"

// When finished, rename it to Render2D

/*
    SpriteRenderer should have a handle to the targeted Window. DONE
    SpriteRenderer should use the draw calls for each entity. DONE
    SpriteRenderer should optimize how the sprites are managed (like not loading the texture at every draw call) DONE
 */

class SpriteRenderer : public ISystem {
    public:
        explicit SpriteRenderer(SDL_Window *window) {
            this->signature.set(Components::TypeToID::Position);
            this->signature.set(Components::TypeToID::Sprite);

            this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (!this->renderer)
                throw std::runtime_error(std::string("Could not create SpriteRenderer.") + SDL_GetError());
        };
        void update(World &world, float) override {
            SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255); // black
            SDL_RenderClear(this->renderer);
            for (const auto &entity : this->entityList) {
                const auto &position = world.get<Position>(entity);
                const auto &sprite = world.get<Sprite>(entity);

                SDL_Texture *texture = this->textures.loadTexture(this->renderer, sprite.pathToTexture);
                if (!texture)
                    continue;

                SDL_Rect rect = { static_cast<int>(position.x), static_cast<int>(position.y), sprite.sizeX, sprite.sizeY };
                SDL_RenderCopy(this->renderer, texture, nullptr, &rect);
            }
            SDL_RenderPresent(this->renderer);
        };
        ~SpriteRenderer() {
            this->textures.clear();
            SDL_DestroyRenderer(this->renderer);
        };

        SpriteRenderer(const SpriteRenderer&) = delete;
        SpriteRenderer &operator=(const SpriteRenderer&) = delete;

    private:
        SDL_Renderer *renderer;
        TextureManager textures;
};

#endif /* __GUNEODROS_RENDER_SYSTEM_HPP__ */
