#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

enum status { OK, INCORRECT_MATRIX_ERROR, CALCULATION_ERROR };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Create Matrix (s21_create_matrix)
int s21_create_matrix(int rows, int columns, matrix_t *result);
// Remove Matrix (s21_remove_matrix)
void s21_remove_matrix(matrix_t *A);
// Compare Matrices (s21_eq_matrix)
int s21_eq_matrix(matrix_t *A, matrix_t *B);
// Matrix Addition (s21_sum_matrix) and Subtraction (s21_sub_matrix)
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Multiply Matrix by Number (s21_mult_number)
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
// Multiply Two Matrices (s21_mult_matrix)
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Transpose a Matrix (s21_transpose)
int s21_transpose(matrix_t *A, matrix_t *result);
// Calculate Matrix Minors and Matrix of Algebraic Complements
// (s21_calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result);
// Calculate Matrix Determinant (s21_determinant)
int s21_determinant(matrix_t *A, double *result);
// Find the Inverse of a Matrix (s21_inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
// Auxiliary Functions
int s21_matrix_is_true(matrix_t *A);
// void s21_print_matrix(matrix_t *A);
double s21_matrix_two_to_two(matrix_t *A);
int s21_calc_addition(matrix_t *A, matrix_t *result);
void s21_calc_processing(matrix_t *A, matrix_t *minor, int skip_row,
                         int skip_column);
double s21_determinant_addition(matrix_t *A);
