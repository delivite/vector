/*
 * bucket.h
 *
 *  Created on: 28 Jan 2020
 *      Author: Samuel Chinedu
 */

#ifndef BUCKET_H_
#define BUCKET_H_

#include<iostream>
#include<typeinfo>
#include<initializer_list>
#include <exception>
#include <algorithm>

namespace sam {

template<typename T>
class bucket {
public:
	class iterator;

public:

	//Default Constructor
	bucket() {
		std::cout << "Constructor" << std::endl;
	}

	//Parameterized constructor with all elements initialized to 0
	explicit bucket(const int size) :
			m_size(size), m_pArray(new T[size] { }), m_capacity(m_size) {
		//To avoid conversion from argument type to class, this constructor is marked explicit
	}

	//Parameterized constructor with all elements initialized to second argument
	bucket(const int size, const T &init) :
			m_size(size), m_pArray(new T[size] { }), m_capacity(m_size) {

		for (int i = 0; i < size; i++) {
			m_pArray[i] = init;
		}
	}

	//Constructor with initializer list
	bucket(std::initializer_list<T> list) {
		for (T value : list) {
			add_element(value);
		}
	}

	//Copy Constructor
	bucket(const bucket &other) :
			m_size(other.m_size), m_position(other.m_position), m_capacity(
					other.m_capacity) {
		for (int i = 0; i < m_size; i++) {
			m_pArray[i] = other.m_pArray[i];
		}
	}

	//Copy Assignment Constructor
	bucket& operator=(const bucket &orig) {
		if (this == &orig) {
			return *this;
		}

		if (orig.m_size <= m_capacity) { //Just copy the elements if size is less than allocated capacity.
			//Memory allocation not needed.
			for (int i = 0; i < orig.m_size; i++) {
				m_pArray[i] = orig.m_pArray[i];
			}
			m_size = orig.m_size;
			m_position = orig.m_position;
			m_capacity = orig.m_capacity;

			return *this;
		}

		T *list = new T[orig.m_size];//Allocate memory on the heap if we are out of reserved space
		for (int i = 0; i < orig.m_size; i++) {
			list[i] = orig.m_pArray[i];
		}

		delete[] m_pArray;
		m_pArray = list;

		m_size = orig.m_size;
		m_position = orig.m_position;
		m_capacity = orig.m_capacity;
		return *this;
	}

	//Move constructor
	bucket(bucket &&orig) :
			m_size(orig.m_size), m_pArray(orig.m_pArray), m_position(
					orig.m_position), m_capacity(orig.m_capacity) {
		orig.m_pArray = nullptr;
		orig.m_size = 0;
		orig.m_capacity = 0;
		orig.m_position = 0;
	}

	//Move Assignment Constructor
	bucket& operator=(bucket &&orig) {
		delete[] m_pArray;
		m_pArray = orig.m_pArray;
		m_size = orig.m_size;
		m_capacity = orig.m_capacity;
		m_position = orig.m_position;

		orig.m_pArray = nullptr;
		orig.m_size = 0;
		orig.m_capacity = 0;
		orig.m_position = 0;

		return *this;
	}

	//Destructor
	~bucket() {
		delete[] m_pArray;
	}

	//Equivalent to std::vector<T>::push_back()
	void add_element(const T &value) {
		m_pArray[m_position] = value;
		m_position++;

		if (m_position > m_size) {
			m_size++;
		}

		if (m_position >= m_capacity) {
			resize_vector(m_capacity * 2);
		}
	}

	void insert_element(std::initializer_list<T> list) {
		for (T x : list) {
			add_element(x);
		}
	}

	T& at(int index) {
		if (!is_in_range(index)) {
			throw std::out_of_range("Error: Index is out 00range");
		} else
			return m_pArray[index];
	}

	const T& at(int inde) const {
		if (!is_in_range(inde)) {
			throw std::out_of_range("Error: Index is out Weird");
		} else
			return m_pArray[inde];
	}

	const T& operator[](int index) const {
		return m_pArray[index];
	}

	T& operator[](int index) {
		return m_pArray[index];
	}

	void pop_last() {
		m_size--;
		m_position--;
	}

	void resize(const int new_size) {
		if (new_size < m_capacity || new_size < 0) {
			return;
		} else
			resize_vector(new_size);
	}

	int capacity() const {
		return m_capacity;
	}

	int size() const {
		return m_size;
	}

	iterator begin() {
		return iterator(m_pArray);
	}

	iterator end() {
		return iterator(&m_pArray[m_size]);
	}

private: //Private member variables
	int m_size { 0 };
	T *m_pArray = new T[10] { }; //Allocate an array of free memory and initialize the elements to 0
	int m_position { 0 };
	int m_capacity { 10 };

private: //Private member functions
	//Resize the vector
	void resize_vector(const int new_size, T def = T()) {
		std::cout << "Let's create a new vector" << std::endl;
		T temp[m_size];
		for (int i = 0; i < m_size; i++) {
			temp[i] = m_pArray[i];
		}

		delete[] m_pArray;

		m_pArray = new T[new_size];

		for (int i = 0; i < m_size; i++) {
			m_pArray[i] = temp[i];
		}
		m_capacity = new_size;
	}

	//Range checking function
	bool is_in_range(const int index) {
		if (index < 0 || index >= m_size) {
			return false;
		}
		return true;
	}
};


template<typename T>
void reverse(bucket<T> &orig) {
	//Reverse the elements of the array
	auto begin = orig.begin();
	auto end = --orig.end();//Move the iterator 1 place back to keep within range

	std::cout << typeid(begin).name() << std::endl;

	while (begin < end) {

		std::swap(*begin, *end);

		begin++;
		end--;
	}
}


template<class T>
std::ostream& operator<<(std::ostream &out, const bucket<T> &orig) {
	out << orig.m_pArray[orig.m_position];
	return out;
}

template<typename T>
class bucket<T>::iterator{

	T* pIndex;

public:
	iterator(T* pos) :
			pIndex(pos) {
	}

/*	iterator &operator=(const iterator &other){
		pIndex = other.pIndex;
		return *this;
	}*/

	T &operator*() const{

		return *pIndex;
	}

	iterator& operator++() {
		pIndex++;
		return *this;
	}

	iterator& operator++(int) {
		++pIndex;
		return *this;
	}

	iterator& operator--(int) {
		--pIndex;
		return *this;
	}

	iterator& operator--() {
		pIndex--;
		return *this;
	}

	bool operator!=(const iterator &copy) const {
		return pIndex != copy.pIndex;
	}

	bool /*const&*/operator<(const iterator &other) const {
		return (pIndex < other.pIndex);
	}

	bool /*const&*/operator<=(const iterator &other) const {
		return (pIndex <= other.pIndex);
	}

	bool /*const&*/operator>(const iterator &other) const {
		return (pIndex > other.pIndex);
	}
};

}

#endif /* BUCKET_H_ */
