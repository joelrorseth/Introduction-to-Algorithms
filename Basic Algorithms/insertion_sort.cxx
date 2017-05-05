//
//  Introduction to Algorithms (Third Edition)
//  Cormen, Leiserson, Rivest, Stein
//
//  Insertion Sort (pg. 18)
//  Worst case time complexity: O(n^2)
//
//  Implemented by Joel Rorseth
//  Created on May 4, 2017
//

#include <iostream>
#include <vector>

template <typename T>
void insertion_sort(std::vector<T> & list) {

    // Start with second element since first is sorted
    // Each iteration, determine where to place 'key'

    for (int j = 1; j < list.size(); ++j) {
        
        auto key = list[j];
        int i = j - 1;

        // If 'key' is less than current element, decrement
        while (i > 0 && list[i] > key) {

            // Copy larger number to higher position
            list[i + 1] = list[i];
            --i;
        }

        // 'key' can now be placed here
        list[i + 1] = key;
    }
}

// Demonstration
int main(int argc, char * argv[]) {

    std::vector<int> a{1,9,2,6,5,4,7,3,8};

    // Print vector contents
    std::cout << "Before sorting...\n"
        << "Vector a = { ";
    for (auto num: a)
        std::cout << num << ", ";
    std::cout << "}" << std::endl;

    // Call the insertion sort
    insertion_sort(a);

    // Print vector again
    std::cout << "After sorting...\n" 
        << "Vector a = { ";
    for (auto num: a)
        std::cout << num << ", ";
    std::cout << "}" << std::endl;
}
