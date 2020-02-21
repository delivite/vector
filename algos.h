/*
 * algos.h
 *
 *  Created on: 19 Feb 2020
 *      Author: Troy
 */

#ifndef ALGOS_H_
#define ALGOS_H_
#include <algorithm>

namespace sam {
template<typename iter>
//Reverse the elements of the vector
void reverse(iter begin, iter end) {

	while (begin < end) {
		--end;
		std::swap(*begin, *end);

		++begin;
	}
}

template<typename iter>
//Find the maximum value in the container
iter max_value(iter first, iter last) {
	if (first == last) {
		return last;
	}
	iter max = first;

	while (first != last) {
		if (*max < *first) {
			max = first;
		}

		first++;
	}
	return max;
}

template<typename iter>
//Find the minimum value in the container
iter min_value(iter first, iter last) {
	if (first == last) {
		return last;
	}
	iter min = first;

	while (first != last) {
		if (*min > *first) {
			min = first;
		}

		first++;
	}
	return min;
}

template<typename iter>
//Return the zero-index position of the maximum value
//Return -1 if container is empty
int max_elem(iter first, iter last) {
	int count { };
	int max_index { };
	if (first == last) {
		return -1;
	}
	iter max = first;

	while (first != last) {

		if (*max < *first) {
			max = first;
			max_index = count;
		}
		++count;
		++first;
	}
	return max_index;
}

template<typename iter>
//Return the zero-index position of the minimum value
//Return -1 if container is empty
int min_elem(iter first, iter last) {
	int count { };
	int min_index { };
	if (first == last) {
		return -1;
	}
	iter min = first;

	while (first != last) {

		if (*min > *first) {
			min = first;
			min_index = count;
		}
		++count;
		++first;
	}
	return min_index;
}

template<typename T, typename iter>
//Return the zero-index position of the first found value (if found)
int find(iter first, iter last, const T value) {
	int count { };
	int index { };
	while (first < last) {
		if (*first == value) {
			index = count;
			break;
		}
		++first;
		++count;
	}
	return index;
}

template<typename T, typename iter>
//Return true if value is found in the container
bool is_found(iter first, iter last, const T value) {
	while (first < last) {
		if (*first == value) {
			return true;
		}
		++first;
	}
	return false;
}

template<typename T, typename iter>
//Return the number of times a value is found in a container
int count_elements(iter first, iter last, const T value) {
	int count { };
	while (first < last) {
		if (*first == value) {
			++count;

		}
		++first;
	}

	return (count > 0) ? count : 0;
}

}				//namespace

#endif /* ALGOS_H_ */
