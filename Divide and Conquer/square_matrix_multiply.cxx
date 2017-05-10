//
//  Introduction to Algorithms (Third Edition)
//  Cormen, Leiserson, Rivest, Stein
//
//  Matrix Multiplication Algorithm (pg. 75)
//  Worst case time complexity: O(n^3)
//
//  Implemented by Joel Rorseth
//  Created on May 9, 2017
//

#include <iostream>
#include <vector>

// Generalize matrices as 2D std::vector's
template <typename T>
using matrix = std::vector<std::vector<T>>;


// Matrix multiplication algorithm
template <typename T>
matrix<T> square_matrix_multiply(matrix<T> const & a, matrix<T> const & b) {

    // Definition:
    // c[i][j] = summation from k=1 to n(a[i][k] * b[k][j])

    auto n = a.size();
   
    // Matrix must be initialized with default values and size n
    matrix<T> c{{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {

            c[i][j] = 0;
            for (int k = 0; k < n; ++k)
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
        }
    }

    return c;
}


// Convenience output formatter
template <typename T>
void print_matrix(matrix<T> const & matrix) {

    for (auto i: matrix) {
        for (auto j: i)
            std::cout << j << '\t';
        std::cout << '\n';
    }

    std::cout << std::endl;
}

// Demonstration
int main(int argc, char * argv[]) {

    matrix<int> a{
        {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
    matrix<int> b{
        {0,2,4,6}, {8,10,12,14}, {16, 18, 20, 22}, {24,26,28,30}};

    std::cout << "Matrix a...\n";
    print_matrix(a);
    std::cout << "Matrix b...\n";
    print_matrix(b);

    std::cout << "Result of multiplying matrix a by b...\n";
    
    auto multiplied = square_matrix_multiply(a, b);
    print_matrix(multiplied);
}
