#include "Component.h"
#include "Entity.h"
Component::Component(Entity* owner)
	: owner(owner)
{}

Entity* Component::get_owner()
{
	return owner;
}
