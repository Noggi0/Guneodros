//
// Created by vince on 03/03/2025.
//

#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <iostream>

class TextureManager {
    public:
        TextureManager() = default;
        SDL_Texture* loadTexture(SDL_Renderer *renderer, const std::string& fileName) {
            if (textures.find(fileName) == textures.end()) {
                SDL_Texture* newTexture = IMG_LoadTexture(renderer, fileName.c_str());
                if (!newTexture) {
                    std::cout << "Failed to load texture: " << fileName << std::endl;
                    textures.insert(std::pair<std::string, SDL_Texture*>(fileName, nullptr));
                    return nullptr;
                }
                textures[fileName] = newTexture;
            }
            return textures[fileName];
        };
        SDL_Texture* getTexture(const std::string& fileName) {
            return textures[fileName];
        };
        ~TextureManager() {
            for (auto&[_, texture] : textures) {
                SDL_DestroyTexture(texture);
            }
            textures.clear();
        };
    private:
        std::unordered_map<std::string, SDL_Texture *> textures;
};

#endif //TEXTUREMANAGER_HPP
