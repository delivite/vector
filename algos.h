/*
 * algos.h
 *
 *  Created on: 19 Feb 2020
 *      Author: Troy
 */

#ifndef ALGOS_H_
#define ALGOS_H_

namespace sam {
template<typename iter>
void reverse(iter begin, iter end) {

	--end;				//Move the iterator 1 place back to keep within range
	while (begin != end) {

		std::swap(*begin, *end);

		begin++;
		end--;
	}
}

template<typename iter>
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

}				//namespace

#endif /* ALGOS_H_ */
