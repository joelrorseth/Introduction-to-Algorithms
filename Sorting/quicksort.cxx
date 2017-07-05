//
//  Introduction to Algorithms (Third Edition)
//  Cormen, Leiserson, Rivest, Stein
//
//  Quicksort (pg. 171)
//  Worst case time complexity: O(n^2)
//  Average case time complexity: O(n lgn) with small constants
//
//  Implemented by Joel Rorseth
//  Created on July 5, 2017
//

#include <iostream>
#include <vector>
#include <algorithm>


//  Rearrange the array in place and determine a pivot index
template <typename T>
int partition(std::vector<T> & list, int start, int end) {

	T x = list[end];
	int i = start - 1;

	for (int j = start; j < end; ++j)
		if (list[j] <= x) {
			++i;
			std::swap(list[i], list[j]);
		}

	std::swap(list[i + 1], list[end]);
	return i + 1;
}


//  Partition the array A into two subarrays A[p..q-1] and A[q+1..r]
//  such that: elements in A[p..q-1] <= A[q] <= elements in A[q+1..r]
//  Recurse until sort is trivial (zero or one elements per partition)

template <typename T>
void quicksort(std::vector<T> & list, int start, int end) {

	if (start < end) {

		// Calculate partition index aka the 'pivot'
		int pivot = partition(list, start, end);

		// Recursively sort each half about the pivot
		quicksort(list, start, pivot - 1);
		quicksort(list, pivot + 1, end);
	}
}


// Demonstration
int main(int argc, char * argv[]) {

    std::vector<int> a{1,9,2,6,5,4,7,3,8};

    // Print vector contents
    std::cout << "Before sorting...\n\tstd::vector a = { ";
    for (auto num: a)
        std::cout << num << ", ";
    std::cout << "}" << std::endl;

    // Call quicksort with start and end index positions
    // This is an assumption stated in the book
    quicksort(a, 0, a.size() - 1);

    // Print vector again
    std::cout << "After sorting...\n\tstd::vector a = { ";
    for (auto num: a)
        std::cout << num << ", ";
    std::cout << "}" << std::endl;
}
