//
// Created by vince on 02/04/2025.
//

#ifndef AABB_HPP
#define AABB_HPP

#include "../Components/Component.hpp"

bool aabb_collides(BoxCollider first, BoxCollider second)
{
    return (first.x < second.x + second.width &&
		first.x + first.width > second.x &&
		first.y < second.y + second.height &&
		first.y + first.height > second.y);
}

#endif //AABB_HPP
