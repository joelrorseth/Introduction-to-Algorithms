//
//  Introduction to Algorithms (Third Edition)
//  Cormen, Leiserson, Rivest, Stein
//
//  Maximum Subarray Algorithm (pg. 71, 72)
//  Worst case time complexity: O(n log(n))
//
//  Implemented by Joel Rorseth
//  Created on May 8, 2017
//

#include <iostream>
#include <vector>
#include <tuple>

//  Given an array of comparable elements, the algorithm recursively
//  determines the subarray that produces the largest sum. The largest
//  subarray must be contained in the left half, right half, or crossing 
//  over both. This fact is exploited recursively.


template <typename T>
std::tuple<int, int, int>  maximum_crossing_subarray
(std::vector<T> const & array, int low, int mid, int high) {

    int left_sum = INT_MIN, right_sum = INT_MIN;
    int sum = 0;
    int max_left, max_right;

    // Determine maximum subarray from [low, mid]
    // This is easy. Keep a running sum by accumulating all values 
    // sequentially, and mark new endpoint for range whenever sum
    // exceeds current greatest sum for this partition

    for (int i = mid; i >= low; --i) {        
        sum += array[i];

        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }
    
    sum = 0;

    // Determine maximum subarray from (mid, high]
    for (int j = mid + 1; j <= high; ++j) {   
        sum += array[j];
        
        if (sum > right_sum) {
            right_sum = sum;
            max_right = j;
        }
    }

    // Return two indexes and net sum for max crossed subarray range
    // Even if one partition was all negative numbers, the maximum
    // subarray would still incorporate both 'max' indexes found

    return std::make_tuple(max_left, max_right, left_sum + right_sum);
}


template <typename T>
std::tuple<int, int, int> maximum_subarray
(std::vector<T> const & array, int low, int high) {

    if (high == low) {
        return std::make_tuple(low, high, array[low]);
    } else {

        int mid = (low + high) / 2;

        // Retrieve ordered pairs representing result of the form
        // (left_pos, right_pos, sum_between_pos)

        auto left = maximum_subarray(array, low, mid);
        auto right = maximum_subarray(array, mid + 1, high);
        auto cross = maximum_crossing_subarray(array, low, mid, high);

        // For simplicity, extract each index and sum

        auto left_sum = std::get<2>(left);
        auto right_sum = std::get<2>(right);
        auto cross_sum = std::get<2>(cross);

        auto left_low = std::get<0>(left);
        auto right_low = std::get<0>(right);
        auto cross_low = std::get<0>(cross);

        auto left_high = std::get<1>(left);
        auto right_high = std::get<1>(right);
        auto cross_high = std::get<1>(cross);

        // Left subarray is maximum
        if (left_sum >= right_sum && left_sum >= cross_sum)
            return left;

        // Right subarray is maximum
        else if (right_sum >= left_sum && right_sum >= cross_sum)
            return right;

        // A cross between left and right side is maximum
        else
            return cross;
    }
}

// Convenience output formatter
template<typename T>
void print_array(std::vector<T> const & array) {

    for (auto e: array)
        std::cout << e << ' ';
    std::cout << '\n';
}

// Demonstration
int main(int argc, char * argv[]) {

    std::vector<int> a{-3, 5, 7, 12, -6, -7, 2, 4, -6, -9};

    std::cout << "Original array...\n\t";
    print_array(a);

    auto retval = maximum_subarray(a, 0, a.size() - 1);

    std::cout << "\nThe maximum subarray is [" << std::get<0>(retval) 
        << ',' << std::get<1>(retval) << "] with a sum of " << std::get<2>(retval)
        << std::endl;
}
