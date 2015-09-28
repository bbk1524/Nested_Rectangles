#pragma once
#include <string>
#include <vector>
#include <memory>

#include "Component.h"

class Entity
{
public:
	Entity(std::string type);
	~Entity() = default;
	void update();

	//Don't assign this to anything in callers!!!
	//Unless it will be around for the life of the object!
	template<typename T>
	T* get_component()
	{
		for (auto& c : components)
		{
			T* result = dynamic_cast<T*>(c.get());
			if (result != nullptr) { return result; }
		}
		return nullptr;
	}

	template <typename T, typename ...Args>
	//pass this the args for component.init(), and it will forward them
	void add_component(Args&&... args)
	{
		auto pB = std::make_unique<T>(this);
		pB->init(std::forward<Args>(args)...);
		components.push_back(std::move(pB));
	}
private:
	std::vector<std::unique_ptr<Component>> components;
	//bool is_valid{ false };
};