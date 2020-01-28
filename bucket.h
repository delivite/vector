/*
 * bucket.h
 *
 *  Created on: 28 Jan 2020
 *      Author: Samuel Chinedu
 */

#ifndef BUCKET_H_
#define BUCKET_H_

#include<iostream>
#include<cstdlib>
#include<initializer_list>

namespace my {

template<typename T>
class bucket {
	int m_size { 0 };
	T *m_list = new T[10];
	int m_position { 0 };
	int m_capacity { 10 };

private:
	void new_array(int new_size) {
		//Expands the capacity of the vector
		T temp[m_size];
		for (int i = 0; i < m_size; i++) {
			temp[i] = m_list[i];
		}

		delete[] m_list;

		m_list = new T[new_size]; //Re-allocates the pointer.

		for (int i = 0; i < m_size; i++) {
			m_list[i] = temp[i];
		}
		m_capacity = new_size;
	}

public:
	class iterator;

public:

	bucket() = default; //Default constructor
	bucket(const bucket &other) = default;
	bucket& operator=(const bucket &other) = default;

	bucket(int size) {
		//Parameterized constructor to create a vector of size elements.
		m_list = new T[size];
		m_size = size;

		m_capacity = m_size;
	}

	bucket(int size, int init) {
		//Parameterized constructor - Creates size array and initialize the elements with init.
		m_list = new T[size];
		for (T i = 0; i < size; i++) {
			m_list[i] = init;
		}
		m_size = size;
		m_capacity = m_size;
	}


	bucket(std::initializer_list<T> list) {
		for (T value : list) {
			add(value);
		}
	}


	~bucket() {
		delete[] m_list;
	}


	void pop_last() {
		m_size--;
		m_position--;
	}


	void add(T value) {
		m_list[m_position] = value;
		m_position++;

		if (m_position > m_size) {
			m_size++;
		}

		if (m_position >= m_capacity) {
			new_array(m_capacity + 8);
		}
	}


	void insert(std::initializer_list<T> list) {
		for (T x : list) {
			add(x);
		}
	}


	int capacity() {
		return m_capacity;
	}


	int size() {
		return m_size;
	}


	T& at(int position) {
		return m_list[position];
	}


	std::ostream& operator<<(std::ostream &out) const {
		out << m_list[m_position];
		return out;
	}


	T& operator[](int index) const {
		return m_list[index];
	}


	iterator begin() {
		return iterator(0, *this);
	}


	iterator end() {
		return iterator(m_size, *this);
	}


	void reverse() {
		//Reverse the elements of the array
		T *begin = m_list;
		T *end = &m_list[m_size - 1];

		while (begin < end) {

			T temp = *begin;
			*begin = *end;
			*end = temp;

			begin++;
			end--;
		}
	}
};


template<typename T>
class bucket<T>::iterator {
	int m_index;
	bucket &m_bucket;

public:
	iterator(int pos, bucket &container) :
			m_index(pos), m_bucket(container) {
	}


	T& operator*() {

		return m_bucket.at(m_index);
	}


	iterator& operator++() {
		m_index++;
		return *this;
	}


	iterator& operator++(int) {
		++m_index;
		return *this;
	}

	iterator& operator--(int) {
		--m_index;
		return *this;
	}

	iterator& operator--() {
		m_index--;
		return *this;
	}

	bool operator!=(const iterator &copy) const {
		return m_index != copy.m_index;
	}

	bool const& operator<(const iterator &other) const {
		return (m_index < other.m_index);
	}
};

}

#endif /* BUCKET_H_ */
