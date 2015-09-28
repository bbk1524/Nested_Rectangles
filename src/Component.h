#pragma once

class Entity;

//Also needs an init() method to work with Entity

class Component
{
public:
	Component(Entity* owner);
	virtual ~Component() = default;
	virtual void update() = 0;
	Entity* get_owner();
private:
	Entity* owner;
};