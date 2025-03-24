#pragma once
#include <SDL.h>
class ColliderComponent;
class Collision
{
public:
	//axis aligned bounding box 
	// (lay A.x + A.w va so sanh voi B.x + B.w (va tuong tu))
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);

};