#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = INCORRECT_MATRIX_ERROR;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
      }
      status = OK;
    }
  }
  return status;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  if (A->rows) A->rows = 0;
  if (A->columns) A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = FAILURE;
  if (s21_matrix_is_true(A) == 0 && s21_matrix_is_true(B) == 0) {
    if (A->rows == B->rows && A->columns == B->columns) {
      status = SUCCESS;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) status = FAILURE;
        }
      }
    }
  }
  return status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = CALCULATION_ERROR;
  if (s21_matrix_is_true(A) == 0 && s21_matrix_is_true(B) == 0) {
    if (A->rows == B->rows && A->columns == B->columns) {
      status = s21_create_matrix(A->rows, A->columns, result);
      if (status == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      }
    }
  }
  return status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = CALCULATION_ERROR;
  if (s21_matrix_is_true(A) == 0 && s21_matrix_is_true(B) == 0) {
    if (A->rows == B->rows && A->columns == B->columns) {
      status = s21_create_matrix(A->rows, A->columns, result);
      if (status == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      }
    }
  }
  return status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = INCORRECT_MATRIX_ERROR;
  if (s21_matrix_is_true(A) == 0) {
    status = s21_create_matrix(A->rows, A->columns, result);
    if (status == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = CALCULATION_ERROR;
  if (s21_matrix_is_true(A) == 0 && s21_matrix_is_true(B) == 0) {
    if (B->rows == A->columns) {
      status = s21_create_matrix(A->rows, B->columns, result);
      if (status == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            for (int n = 0; n < B->rows; n++) {
              result->matrix[i][j] += A->matrix[i][n] * B->matrix[n][j];
            }
          }
        }
      }
    }
  }
  return status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = INCORRECT_MATRIX_ERROR;
  if (s21_matrix_is_true(A) == 0) {
    status = s21_create_matrix(A->columns, A->rows, result);
    if (status == OK) {
      for (int i = 0; i < A->columns; i++) {
        for (int j = 0; j < A->rows; j++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    }
  }
  return status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = INCORRECT_MATRIX_ERROR;
  if (s21_matrix_is_true(A) == 0) {
    status = CALCULATION_ERROR;
    if (A->rows == A->columns) {
      status = s21_create_matrix(A->rows, A->columns, result);
      if (status == OK) {
        status = s21_calc_addition(A, result);
      }
    }
  }
  return status;
}

int s21_determinant(matrix_t *A, double *result) {
  int status = INCORRECT_MATRIX_ERROR;
  if (s21_matrix_is_true(A) == 0) {
    status = CALCULATION_ERROR;
    if (A->rows == A->columns) {
      status = OK;
      *result = A->matrix[0][0];
      if (A->rows > 1) *result = s21_determinant_addition(A);
    }
  }
  return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = INCORRECT_MATRIX_ERROR;
  if (s21_matrix_is_true(A) == 0) {
    status = CALCULATION_ERROR;
    if (A->rows == A->columns) {
      matrix_t tmp_first = {0};
      double determinant_of_transpose = 0;
      s21_determinant(A, &determinant_of_transpose);
      if (fabs(determinant_of_transpose) > 1e-7) {
        status = s21_calc_complements(A, &tmp_first);
        if (status == 0) {
          matrix_t tmp_second = {0};
          status = s21_transpose(&tmp_first, &tmp_second);
          if (status == 0) {
            s21_mult_number(&tmp_second, 1.0 / determinant_of_transpose,
                            result);
          }
          s21_remove_matrix(&tmp_second);
        }
      }
      s21_remove_matrix(&tmp_first);
    }
  }
  return status;
}

double s21_determinant_addition(matrix_t *A) {
  double result = 0;
  if (A->rows == 2) {
    result = s21_matrix_two_to_two(A);
  } else {
    for (int j = 0; j < A->columns; j++) {
      matrix_t minor = {0};
      s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
      s21_calc_processing(A, &minor, 0, j);
      result += A->matrix[0][j] * pow(-1, j) * s21_determinant_addition(&minor);
      s21_remove_matrix(&minor);
    }
  }
  return result;
}

int s21_calc_addition(matrix_t *A, matrix_t *result) {
  int status = CALCULATION_ERROR;
  if (A->rows > 1) {
    status = OK;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t minor = {0};
        double determinant = 0;
        s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
        s21_calc_processing(A, &minor, i, j);
        s21_determinant(&minor, &determinant);
        result->matrix[i][j] = pow(-1, (i + j)) * determinant;
        s21_remove_matrix(&minor);
      }
    }
  }
  return status;
}

void s21_calc_processing(matrix_t *A, matrix_t *result, int skip_row,
                         int skip_column) {  // расчет минора
  int not_to_skip_row = 0, not_to_skip_column = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == skip_row) continue;
    not_to_skip_column = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == skip_column) continue;
      result->matrix[not_to_skip_row][not_to_skip_column] = A->matrix[i][j];
      not_to_skip_column++;
    }
    not_to_skip_row++;
  }
}

double s21_matrix_two_to_two(matrix_t *A) {
  double result =
      A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  return result;
}

int s21_matrix_is_true(matrix_t *A) {
  int status = INCORRECT_MATRIX_ERROR;
  if (A != NULL && A->matrix != NULL && A->columns > 0 && A->rows > 0) {
    status = OK;
  }
  return status;
}