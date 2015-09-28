#include "Entity.h"
#include "Component.h"

#include <memory>


//How the heck am I supposed to pass stuff to the 
//init functions?
//In my final, I passed in a Game* and an x,y,angle

//I want to use the standard system of each component having only data, and making "Systems" which read and write to the components on update
Entity::Entity(std::string type)
{
	//if (type == "A")
	//{
	//	add_component<ComponentA>(56);
	//}

	//if (type == "B")
	//{
	//	add_component<ComponentB>(4, 3);
	//}

	//if (type == "AB")
	//{
	//	add_component<ComponentA>(2);
	//	add_component<ComponentB>(this->get_component<ComponentA>()->a + 1, 1);
	//}
}

void Entity::update()
{
	for (auto& c : components)
	{
		c->update();
	}
}