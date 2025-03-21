#pragma once

#include <iostream>
#include <vector>
#include "game.h"
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
using namespace std;

class Component;
class Entity;

using ComponentID = size_t;

inline ComponentID getComponentID()
{
	static ComponentID lastID = 0;
	return lastID++;

}

template <typename T> inline ComponentID getComponentID() noexcept
{
	static ComponentID typeID = getComponentID();
	return typeID();
}
constexpr size_t maxComponents = 32;

using ComponentBitSet = bitset<maxComponents>;
using ComponentArray = array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}

 
};

class Entity
{
public:
	bool active = true;
};