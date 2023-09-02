# Matrix Library (matrix.h)

This project involves the implementation of a `matrix.h` library, which provides essential matrix operations. The library is implemented in C language and follows the specified function prototypes.

## Implemented Functions

The `matrix.h` library implements the following functions:

1. `s21_create_matrix` - Create a matrix with a given number of rows and columns.
2. `s21_remove_matrix` - Clean and destroy a matrix, freeing allocated memory.
3. `s21_eq_matrix` - Compare two matrices for equality.
4. `s21_sum_matrix` - Add two matrices.
5. `s21_sub_matrix` - Subtract one matrix from another.
6. `s21_mult_number` - Multiply a matrix by a scalar number.
7. `s21_mult_matrix` - Multiply two matrices.
8. `s21_transpose` - Transpose a matrix.
9. `s21_calc_complements` - Calculate the matrix of algebraic complements.
10. `s21_determinant` - Calculate the determinant of a matrix.
11. `s21_inverse_matrix` - Find the inverse of a matrix.

## Usage Example

```c
#include "matrix.h"
#include <stdio.h>

int main() {
    matrix_t mat1, mat2, result;
    double determinant;

    // Create matrices
    if (s21_create_matrix(3, 3, &mat1) != SUCCESS || s21_create_matrix(3, 3, &mat2) != SUCCESS) {
        fprintf(stderr, "Matrix creation failed\n");
        return 1;
    }

    // Fill matrices with data (omitted for brevity)

    // Perform matrix operations
    s21_sum_matrix(&mat1, &mat2, &result);
    s21_sub_matrix(&mat1, &mat2, &result);
    s21_mult_number(&mat1, 2.0, &result);
    s21_mult_matrix(&mat1, &mat2, &result);
    s21_transpose(&mat1, &result);

    // Calculate determinant and inverse
    if (s21_determinant(&mat1, &determinant) == SUCCESS) {
        printf("Determinant: %lf\n", determinant);
    } else {
        printf("Determinant calculation failed\n");
    }

    if (s21_inverse_matrix(&mat1, &result) != SUCCESS) {
        fprintf(stderr, "Matrix inversion failed\n");
    }

    // Clean up and remove matrices
    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);

    return 0;
}
```

## Getting Started

To use the `matrix.h` library, include the header file and link against the library in your project. Ensure you initialize matrices using `s21_create_matrix`, perform operations, and release resources with `s21_remove_matrix` when finished.

## Conclusion

The `matrix.h` library provides essential matrix operations for C projects. It follows the specified function prototypes and can be used to perform various matrix calculations.

For more details on each function and its usage, refer to the header file and the example provided.