#ifndef CPP_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_
#define CPP_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

class S21Matrix {
 public:
  S21Matrix() noexcept = default;
  explicit S21Matrix(const int rows, const int cols) noexcept;
  S21Matrix(const S21Matrix& other) noexcept;
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix() noexcept;

  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant() const;
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double other);
  friend S21Matrix operator*(const double other, S21Matrix& tmp);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double other);
  double& operator()(int i, int j);
  double operator()(int i, int j) const;

  void MutateRows(int rows) noexcept;
  void MutateCols(int cols) noexcept;
  int AccessRows() const noexcept;
  int AccessCols() const noexcept;

 private:
  int rows_{0}, cols_{0};
  double** matrix_ = nullptr;

  void CreateMatrix() noexcept;
  void DeleteMatrix() noexcept;
  void CopyMatrix(const int rows, const int cols,
                  const S21Matrix& other) noexcept;
  void Minor(S21Matrix* A, int colums, int rows) const noexcept;
  double DeterminantMinor(int row, int colum) noexcept;
  void SumSubMatrix(const int tmp, const S21Matrix& other) noexcept;
  S21Matrix CalcCompHelper() noexcept;
  double DetermHelper() const noexcept;
};

#endif  // CPP_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_