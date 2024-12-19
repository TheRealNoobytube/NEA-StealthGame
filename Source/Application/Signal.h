#pragma once
#include <functional>
#include "Data Structures/List.h"

//Not all functions have the same exact type signature.
//The variadic template solves this by allowing us to pass in any number of datatypes into the Signal
//This means we don't have to create new methods for every single possible kind of function
template <typename ... Args>

class Signal {
private:
	List<std::function<void(Args...)>> slots;  //stores all of the functions that will be called when emit is called

public:

	//adds the passed in function to the list of slots
	void connect(std::function<void(Args...)> function) {
		slots.add(function);

	}

	//removes the passed in function from the list of slots
	void remove(std::function<void(Args...)> function) {
		int functionIndex = slots.find(function);
		slots.remove(functionIndex);
	}

	void emit(Args... args) {
		for (int i = 0; i < slots.getSize(); i++) { //go through every slot, and if the function still exists, call it
			if (slots.get(i) != nullptr) {
				slots.get(i)(args...);
			}
			else {
				slots.remove(i); //otherwise the nullptr is removed from the list
			}
		}
	}
};