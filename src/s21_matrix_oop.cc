#include "s21_matrix_oop.h"

S21Matrix::S21Matrix(const int rows, const int cols) noexcept
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows > 0 && cols > 0) {
    CreateMatrix();
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(nullptr) {
  if (other.matrix_) {
    CreateMatrix();
    CopyMatrix(other.rows_, other.cols_, other);
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

S21Matrix::~S21Matrix() noexcept { DeleteMatrix(); }

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  bool error = true;
  if (other.cols_ == cols_ && other.rows_ == rows_ && matrix_ &&
      other.matrix_) {
    for (int i = 0; i < rows_ && error; ++i) {
      for (int j = 0; j < cols_ && error; ++j) {
        if (!(std::abs(other.matrix_[i][j] - matrix_[i][j]) < 1e-7))
          error = false;
      }
    }
  } else {
    error = false;
  }
  return error;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_ || !matrix_ ||
      !other.matrix_) {
    throw std::length_error("different matrix dimensions or no matrix exists");
  }
  SumSubMatrix(1, other);
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_ || !matrix_ ||
      !other.matrix_) {
    throw std::length_error("different matrix dimensions or no matrix exists");
  }
  SumSubMatrix(-1, other);
}

void S21Matrix::MulNumber(const double num) {
  if (!matrix_) {
    throw std::length_error("no matrix exists");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_ || !matrix_ || !other.matrix_) {
    throw std::length_error(
        "the number of columns of the first matrix is not equal to the "
        "number "
        "of rows of the second matrix or no matrix exists");
  }
  S21Matrix tmp = S21Matrix(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  cols_ = other.cols_;
  std::swap(matrix_, tmp.matrix_);
}

S21Matrix S21Matrix::Transpose() {
  if (!matrix_) {
    throw std::length_error("no matrix exists");
  }
  S21Matrix tmp = S21Matrix(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      tmp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return tmp;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_ || !matrix_) {
    throw std::length_error("the matrix is not square or no matrix exists");
  }
  S21Matrix result_matrix = CalcCompHelper();
  return result_matrix;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_ || !matrix_) {
    throw std::length_error("the matrix is not square or no matrix exists");
  }
  return DetermHelper();
}

S21Matrix S21Matrix::InverseMatrix() {
  if (!matrix_) {
    throw std::length_error("no matrix exists");
  }
  double det = Determinant();
  S21Matrix tmp;
  S21Matrix matrix_resul;
  if (fabs(det) < 1e-7) {
    throw std::length_error("matrix determinant is 0");
  }
  if (rows_ == 1) {
    matrix_resul = S21Matrix(1, 1);
    matrix_resul.matrix_[0][0] = 1 / matrix_[0][0];

  } else {
    tmp = CalcComplements();
    matrix_resul = tmp.Transpose();
    matrix_resul.MulNumber(1.0 / det);
  }
  return matrix_resul;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix tmp = S21Matrix(*this);
  tmp += other;
  return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix tmp = S21Matrix(*this);
  tmp -= other;
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix tmp = S21Matrix(*this);
  tmp *= other;
  return tmp;
}

S21Matrix S21Matrix::operator*(const double other) {
  S21Matrix tmp = S21Matrix(*this);
  tmp *= other;
  return tmp;
}

S21Matrix operator*(const double other, S21Matrix& tmp) {
  tmp *= other;
  return tmp;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    DeleteMatrix();
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    DeleteMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    CreateMatrix();
    CopyMatrix(rows_, cols_, other);
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double other) {
  MulNumber(other);
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (rows_ <= i || cols_ <= j || i < 0 || j < 0 || !matrix_) {
    throw std::length_error("index is outside the matrix or no matrix exists");
  }
  return matrix_[i][j];
}

double S21Matrix::operator()(int i, int j) const {
  if (rows_ <= i || cols_ <= j || i < 0 || j < 0 || !matrix_) {
    throw std::length_error("index is outside the matrix or no matrix exists");
  }
  return matrix_[i][j];
}

void S21Matrix::MutateRows(int rows) noexcept {
  if (rows != rows_ && rows >= 0) {
    S21Matrix tmp = *this;
    DeleteMatrix();
    cols_ = tmp.cols_;
    rows_ = rows;
    CreateMatrix();
    CopyMatrix(rows, cols_, tmp);
  }
}

void S21Matrix::MutateCols(int cols) noexcept {
  if (cols != cols_ && cols >= 0) {
    S21Matrix tmp = *this;
    DeleteMatrix();
    rows_ = tmp.rows_;
    cols_ = cols;
    CreateMatrix();
    CopyMatrix(rows_, cols, tmp);
  }
}

int S21Matrix::AccessRows() const noexcept { return rows_; }

int S21Matrix::AccessCols() const noexcept { return cols_; }

void S21Matrix::CreateMatrix() noexcept {
  if (rows_ > 0 && cols_ > 0) {
    matrix_ = new double* [rows_] {};
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_]{};
    }
  }
}

void S21Matrix::DeleteMatrix() noexcept {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      if (matrix_[i]) {
        delete[] matrix_[i];
      }
    }
    delete[] matrix_;
  }
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::CopyMatrix(const int rows, const int cols,
                           const S21Matrix& other) noexcept {
  bool flag_rows = true;
  bool flag_cols = true;
  for (int i = 0; i < rows && flag_rows && other.rows_ > 0; ++i) {
    for (int j = 0; j < cols && flag_cols && other.cols_ > 0; ++j) {
      if (i == other.rows_) {
        flag_rows = false;
      } else if (j == other.cols_) {
        flag_cols = false;
      } else {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::Minor(S21Matrix* A, int colums, int rows) const noexcept {
  A->MutateRows(rows_ - 1);
  A->MutateCols(cols_ - 1);
  for (int i = 0, c = 0, r = 0; i < A->rows_; ++i) {
    if (rows == i) {
      r = 1;
    }
    for (int j = 0; j < A->cols_; ++j) {
      if (colums == j) {
        c = 1;
      }
      A->matrix_[i][j] = matrix_[i + r][j + c];
    }
    c = 0;
  }
}

double S21Matrix::DeterminantMinor(int row, int colum) noexcept {
  double result = 0;
  S21Matrix temp = S21Matrix();
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else {
    Minor(&temp, colum, row);
    result = temp.Determinant();
  }
  return result;
}

void S21Matrix::SumSubMatrix(const int tmp, const S21Matrix& other) noexcept {
  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j] * tmp;
    }
  }
}

S21Matrix S21Matrix::CalcCompHelper() noexcept {
  double result_tmp = 0;
  double tmp_0_0 = 0;
  double tmp_0_1 = 0;
  S21Matrix result_matrix = S21Matrix{*this};
  if (rows_ == 2) {
    tmp_0_0 = matrix_[0][0];
    tmp_0_1 = matrix_[0][1];
    matrix_[0][0] = matrix_[1][1];
    matrix_[0][1] = matrix_[1][0];
    matrix_[1][0] = tmp_0_1;
    matrix_[1][1] = tmp_0_0;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        result_tmp = pow(-1, (i + j)) * matrix_[i][j];
        result_matrix(i, j) = result_tmp;
      }
    }
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        result_tmp = 0;
        result_tmp = pow(-1, (i + j)) * DeterminantMinor(i, j);
        result_matrix(i, j) = result_tmp;
      }
    }
  }
  return result_matrix;
}

double S21Matrix::DetermHelper() const noexcept {
  double result = 0;
  int sign = 1;
  S21Matrix temp_d = S21Matrix();
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    for (int i = 0; i < cols_; ++i) {
      Minor(&temp_d, i, 0);
      result += sign * matrix_[0][i] * temp_d.DetermHelper();
      sign *= -1;
    }
  }
  return result;
}
