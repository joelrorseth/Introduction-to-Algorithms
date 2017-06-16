//
//  Introduction to Algorithms (Third Edition)
//  Cormen, Leiserson, Rivest, Stein
//
//  Recursive Matrix Multiplication Algorithm (pg. 77)
//  Worst case time complexity: O(n^3)
//
//  Implemented by Joel Rorseth
//  Created on May 21, 2017
//

#include <iostream>
#include <vector>

// Note: For simplicity, this algorithm will only work for n x n
// matrices where n is a power of 2. This is to make sure that after
// each division where n>=2, n is still an integer.

template <typename T>
using matrix = std::vector<std::vector<T>>;

// Convenience output formatter
template <typename T>
void print_matrix(matrix<T> const & matrix) {
    
    for (auto row: matrix) {
        for (auto element: row)
            std::cout << element << '\t';
        std::cout << '\n';
    }
    
    std::cout << std::endl;
}



// Matrix sum convenience function
template <typename T>
void sum_matrix(matrix<T> & c, const matrix<T> & a, const matrix<T> & b, int row_c, int col_c) {
    
    for(int i = 0; i < a.size(); i++)
        for(int j = 0; j < a.size(); j++)
            c[i + row_c][j + col_c] = a[i][j] + b[i][j];
}


// Matrix multiplication algorithm
template <typename T>
matrix<T> square_matrix_multiply_recursive(const matrix<T> & a, const matrix<T> & b,
        int row_a, int col_a, int row_b, int col_b, int size) {
    
    matrix<T> c;
    
    // Create a size x size empty matrix, initialized with correct number of 0's
    for (int i = 0; i < size; ++i) {
        std::vector<T> temp;
        
        for (int j = 0; j < size; ++j)
            temp.push_back(0);
        c.push_back(temp);
    }
    
    
    // All 2^n matrices will eventually divide into 1x1 matrices (base case)
    if (size == 1)
        c[0][0] = a[row_a][col_a] * b[row_b][col_b];

    else {
        
        // To divide matrix into four parts, divide rows and columns into halves
        int new_size = size / 2;
        
        // Divide the matrix into four quadrants, and recursively calculate the product of
        // each of these quadrants. Eventually, the size will reduce to a small enough scale to
        // perform the calulation with sum_matrix()
        
        sum_matrix(c,
                  square_matrix_multiply_recursive(a, b, row_a, col_a, row_b, col_b, new_size),
                  square_matrix_multiply_recursive(a, b, row_a, col_a + new_size, row_b + new_size, col_b, new_size),
                  0, 0);
        
        sum_matrix(c,
                  square_matrix_multiply_recursive(a, b, row_a, col_a, row_b, col_b + new_size, new_size),
                  square_matrix_multiply_recursive(a, b, row_a, col_a + new_size, row_b + new_size, col_b + new_size, new_size),
                  0, new_size);
        
        sum_matrix(c,
                  square_matrix_multiply_recursive(a, b, row_a + new_size, col_a, row_b, col_b, new_size),
                  square_matrix_multiply_recursive(a, b, row_a + new_size, col_a + new_size, row_b + new_size, col_b, new_size),
                  new_size, 0);
        
        sum_matrix(c,
                  square_matrix_multiply_recursive(a, b, row_a + new_size, col_a, row_b, col_b + new_size, new_size),
                  square_matrix_multiply_recursive(a, b, row_a + new_size, col_a + new_size, row_b + new_size, col_b + new_size, new_size),
                  new_size, new_size);
    }
    
    return c;
}


// Demonstration
int main(int argc, char * argv[]) {
    
    const matrix<int> a{
        {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
    const matrix<int> b{
        {0,2,4,6}, {8,10,12,14}, {16, 18, 20, 22}, {24,26,28,30}};
    
    std::cout << "Matrix a...\n";
    print_matrix(a);
    std::cout << "Matrix b...\n";
    print_matrix(b);
    
    std::cout << "Result of multiplying matrix a by b...\n";
    
    auto multiplied = square_matrix_multiply_recursive(a, b, 0, 0, 0, 0, a.size());
    print_matrix(multiplied);
}
