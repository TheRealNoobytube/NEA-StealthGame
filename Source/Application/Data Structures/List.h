#pragma once
#include <math.h>
#include <stdexcept>

//no cpp file because template classes are difficult to create when the class is split into two files
//sacrifices organization and c++ intellisense in order to minimize headaches trying to find an elegant solution

template <typename T>

class List {
public:
	List(int initialSize = 2) {
		
		this->maxSize = initialSize;
		this->array = new T[maxSize];
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
			throw std::out_of_range("tried to remove element out of bounds");
		}

		T temp = this->array[index];
		this->array[index] = NULL;
		size--;

		//cleans array by preventing any NULL values between elements, so all elements are contiguous
		for (int i = index + 1; i < maxSize; i++) {
			if (this->array[i] != NULL) {
				T temp = this->array[i];
				this->array[i] = NULL;
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
			throw std::out_of_range("tried to remove element out of bounds");
		}

		return this->array[index];
	}

	int getSize() {
		return this->size;
	}

	int getMaxSize() {
		return this->maxSize;
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


};