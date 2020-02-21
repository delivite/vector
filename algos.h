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
//Return the maximum element of the vector
iter max_value(iter first, iter last) {

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
//Return the minimum element of the vector
iter min_value(iter first, iter last) {

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
//Return the zero-index of the maximum value
int max_elem(iter first, iter last) {
	int count{};
	int max_index{};
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
//Return the zero-index of the minimum value
int min_elem(iter first, iter last) {
	int count{};
	int min_index{};
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

}				//namespace

#endif /* ALGOS_H_ */
