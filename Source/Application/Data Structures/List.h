#pragma once
#include <math.h>
#include <stdexcept>
#include <iostream>

//no cpp file because template classes are difficult to create when the class is split into two files

template <typename T>

class List {
public:

	List(int initialSize = 2) {
		
		this->size = 0;
		this->maxSize = initialSize;
		this->array = new T[maxSize];
	}
	
	~List() {
		delete[] this->array;
	}

	//needed to add elements to the private array. when too many elements are in the array, we grow the array
	void add(T element) {
		if (size == maxSize) {
			growArray();
		}

		this->array[size] = element;
		size++;
	}

	T remove() {
		return remove(size - 1);
	}

	//needed to remove elements from the private array. when the array is bigger than it needs to be, we shrink the array
	T remove(int index) {
		if (index > size) {
			std::cout << "INDEX " << index << " OUT OF RANGE";
			throw std::out_of_range("tried to remove element out of bounds");
		}

		T temp = this->array[index];
		this->array[index] = nullptr;
		size--;

		//cleans array by preventing any nullptr values between elements, so all elements are contiguous
		for (int i = index + 1; i < maxSize; i++) {
			if (isNullptr(this->array[i])) {
				T temp = this->array[i];
				this->array[i] = nullptr;
				this->array[i - 1] = temp;
			}
		}


		if (size <= maxSize / 2) {
			if (maxSize > 2) {
				shrinkArray();
			}
			
		}

		return temp;
	}

	int find(T criteria) {
		for (int i = 0; i < size; i++) {
			if (this->array[i] == criteria) {
				return i;
			}
		}

		return -1; //if the thing we're looking for isn't inside the list
	}

	T get(int index) {
		//prevent program from going out of bounds of the array
		if (index >= size) {
			std::cout << "INDEX " << index << " OUT OF RANGE";
			throw std::out_of_range("tried to get element out of bounds");
		}

		return this->array[index];
	}

	int getSize() {
		return this->size;
	}

	int getMaxSize() {
		return this->maxSize;
	}

	void clear() {
		delete[] this->array;
		this->maxSize = 2;
		this->array = new T[maxSize];
		this->size = 0;
	}

	bool isEmpty() {
		return size == 0;
	}

private:
	//dont want to give direct access to the array, could lead to security problems
	T* array = NULL;
	int maxSize = 2;
	int size = 0;


	void growArray() {
		T* newArray = new T[maxSize * 2];

		//move all the contents from the old array to the new array
		for (int i = 0; i < maxSize; i++) {
			newArray[i] = this->array[i];
		}

		delete[] this->array; //we have to manually delete any variable dyanamically allocated to memory

		this->array = newArray;
		maxSize *= 2;
	}

	void shrinkArray() {
		T* newArray = new T[size];

		//move all the contents from the old array to the new array
		for (int i = 0; i < size; i++) {
			newArray[i] = this->array[i];
		}

		delete[] this->array;

		this->array = newArray;

		maxSize = size;
	}


	//cant check if a value in the array is nullptr because no all Lists will have a pointer template
	//so instead we use helper functions. if the value isn't a pointer, then that means the value still exists, and therefore always return false
	//in c++, any objecty that isn't a nullptr has a boolean value of true, so we can just return the inverse of the object to give the appropriate value 
	bool isNullptr(T* item) {
		return !item;
	}

	bool isNullptr(T item) {
		return false;
	}
	

};