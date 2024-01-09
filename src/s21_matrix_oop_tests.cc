#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Constructor, test_1) {
  S21Matrix a;
  S21Matrix b(a);

  b.MutateRows(1);
  b.MutateCols(2);

  a.MutateRows(5);
  a.MutateCols(5);

  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;
  a(0, 3) = 5.0001;
  a(0, 4) = 10.0123;

  a(1, 0) = 2.0;
  a(1, 1) = 2.0;
  a(1, 2) = 4.0;
  a(1, 3) = 5.0001;
  a(1, 4) = 10.0123;

  a(2, 0) = 2.0;
  a(2, 1) = 2.0;
  a(2, 2) = 4.0;
  a(2, 3) = 5.0001;
  a(2, 4) = 10.0123;

  a(3, 0) = 2.0;
  a(3, 1) = 2.0;
  a(3, 2) = 4.0;
  a(3, 3) = 5.0001;
  a(3, 4) = 10.0123;

  a(4, 0) = 2.0;
  a(4, 1) = 2.0;
  a(4, 2) = 4.0;
  a(4, 3) = 5.0001;
  a(0, 4) = 10.0123;

  b = a;

  EXPECT_EQ(a.AccessRows(), 5);
  EXPECT_EQ(a.AccessCols(), 5);

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j));
    }
  }
}

TEST(Constructor, test_2) {
  S21Matrix a(0, -1);

  a.MutateRows(5);
  a.MutateCols(5);

  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;
  a(0, 3) = 5.0001;
  a(0, 4) = 10.0123;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;
  a(1, 3) = 8.0;
  a(1, 4) = 9.003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;
  a(2, 3) = 3.0;
  a(2, 4) = 2.003;

  a(3, 0) = 3.0;
  a(3, 1) = 5.0;
  a(3, 2) = 9.00003;
  a(3, 3) = 3.0;
  a(3, 4) = 10.003;

  a(4, 0) = 7.0;
  a(4, 1) = 8.0;
  a(4, 2) = 3.00003;
  a(4, 3) = 4.0;
  a(4, 4) = 8.003;

  EXPECT_EQ(a.AccessRows(), 5);
  EXPECT_EQ(a.AccessCols(), 5);

  S21Matrix b = a;

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j));
    }
  }
}

TEST(Constructor, test_3) {
  S21Matrix a = S21Matrix(1, 1);
  S21Matrix b = a;
  b.MutateCols(a.AccessCols() + 1);
  EXPECT_EQ(a.AccessCols() + 1, b.AccessCols());
}

TEST(Constructor, test_4) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(-1, 0);

  b = a;

  EXPECT_EQ(a.AccessCols(), b.AccessCols());
}

TEST(Constructor, test_5) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix tmp = a;

  S21Matrix b(std::move(a));

  EXPECT_THROW(b(5, 0), std::length_error);  // утечка в исключении

  EXPECT_EQ(tmp.AccessCols(), b.AccessCols());
}

TEST(Eq, test_6) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix tmp = a;
  S21Matrix b(std::move(a));
  EXPECT_EQ(tmp.AccessCols(), b.AccessCols());
  EXPECT_EQ(tmp.EqMatrix(b), true);
}

TEST(Eq, test_7) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix tmp = a;
  S21Matrix b(std::move(a));
  b(1, 2) = 6.000003;
  EXPECT_EQ(tmp.AccessCols(), b.AccessCols());
  EXPECT_EQ(tmp.EqMatrix(b), false);
}

TEST(Eq, test_8) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix tmp = a;
  S21Matrix b(std::move(a));
  EXPECT_EQ(tmp.AccessCols(), b.AccessCols());

  b.MutateRows(5);
  b.MutateCols(5);

  b(4, 1) = 6.000003;

  EXPECT_EQ(tmp.EqMatrix(b), false);
}

TEST(SumMatrix, test_9) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b.SumMatrix(a);

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) - a(i, j));
    }
  }
}

TEST(SumMatrix, test_10) {
  S21Matrix a(3, 4);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b.MutateRows(5);

  EXPECT_THROW(b.SumMatrix(a), std::length_error);

  b.MutateRows(3);

  a.SumMatrix(b * 2);

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ((a(i, j) - b(i, j) * 2), b(i, j));
    }
  }
}

TEST(SumMatrix, test_11) {
  S21Matrix a(1, 15);
  S21Matrix b(1, 15);
  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      a(i, j) = i + j * 1.73;
    }
  }

  for (int i = 0; i < b.AccessRows(); i++) {
    for (int j = 0; j < b.AccessCols(); j++) {
      b(i, j) = i * 0.25 + j;
    }
  }

  a.SumMatrix(b);

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) + (i + j * 1.73));
    }
  }
}

TEST(SubMatrix, test_12) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b.SubMatrix(a);

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) + a(i, j));
    }
  }
}

TEST(SumMatrix, test_13) {
  S21Matrix a(3, 4);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b.MutateRows(5);

  EXPECT_THROW(b.SubMatrix(a), std::length_error);

  b.MutateRows(3);

  a.SubMatrix(b * 2);

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ((a(i, j) + b(i, j) * 2), b(i, j));
    }
  }
}

TEST(SumMatrix, test_14) {
  S21Matrix a(3, 4);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b.MutateRows(5);

  EXPECT_THROW(b.SubMatrix(a), std::length_error);

  b.MutateRows(3);

  a.SubMatrix(b * 2);

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ((a(i, j) + b(i, j) * 2), b(i, j));
    }
  }
}

TEST(MulNumber, test_15) {
  S21Matrix a(3, 4);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);

  b.MutateRows(0);
  EXPECT_THROW(b.MulNumber(3), std::length_error);

  b = a;
  b.MulNumber(3);

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }
}

TEST(MulMatrix, test_16) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);

  b.MulMatrix(a);

  EXPECT_DOUBLE_EQ(b(0, 0), 74);
  EXPECT_DOUBLE_EQ(b(0, 1), 34);
  EXPECT_DOUBLE_EQ(b(0, 2), 20.000059999999998);
  EXPECT_DOUBLE_EQ(b(1, 0), 149.00036);
  EXPECT_DOUBLE_EQ(b(1, 1), 77.000149999999991);
  EXPECT_DOUBLE_EQ(b(1, 2), 74.000149999999991);
  EXPECT_DOUBLE_EQ(b(2, 0), 79);
  EXPECT_DOUBLE_EQ(b(2, 1), 49);
  EXPECT_DOUBLE_EQ(b(2, 2), 78.000149999999991);
}

TEST(MulMatrix, test_17) {
  S21Matrix a(1, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  S21Matrix b(3, 1);
  b(0, 0) = 2.0;
  b(1, 0) = 11.0;
  b(2, 0) = 12.0;

  a.MulMatrix(b);

  EXPECT_DOUBLE_EQ(a(0, 0), 74);
}

TEST(MulMatrix, test_18) {
  S21Matrix a(1, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  S21Matrix b(3, 1);
  b(0, 0) = 2.0;
  b(1, 0) = 11.0;
  b(2, 0) = 12.0;

  a.MulMatrix(b);

  EXPECT_DOUBLE_EQ(a(0, 0), 74);
}

TEST(MulMatrix, test_19) {
  S21Matrix a(4, 3);
  S21Matrix b(4, 3);
  S21Matrix result_full(4, 3);
  double res = 5.123f;

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      a(i, j) = 1.21030120f;
      b(i, j) = res * a(i, j);
    }
  }

  EXPECT_THROW(a.MulMatrix(b), std::length_error);
  b.MutateRows(3);

  result_full = a * b;

  for (int i = 0; i < result_full.AccessRows(); i++) {
    for (int j = 0; j < result_full.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(result_full(i, j), 22.512955999024761);
    }
  }
}

TEST(Transpose, test_20) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  S21Matrix result_full(3, 3);
  S21Matrix result1;
  S21Matrix result2;

  a(0, 0) = 0;
  a(0, 1) = 1;
  a(1, 0) = 2;
  a(1, 1) = 8;
  a(2, 0) = 7;
  a(2, 1) = 3;

  b(0, 0) = 5;
  b(0, 1) = 1;
  b(0, 2) = 2;
  b(1, 0) = 3;
  b(1, 1) = 7;
  b(1, 2) = 3;

  result1 = a * b;

  result_full(0, 0) = 3;
  result_full(0, 1) = 34;
  result_full(0, 2) = 44;
  result_full(1, 0) = 7;
  result_full(1, 1) = 58;
  result_full(1, 2) = 28;
  result_full(2, 0) = 3;
  result_full(2, 1) = 28;
  result_full(2, 2) = 23;

  result2 = result1.Transpose();
  EXPECT_EQ(result_full.EqMatrix(result2), true);
}

TEST(Transpose, test_21) {
  S21Matrix a(3, 5);
  S21Matrix result;

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(0, 3) = 4;
  a(0, 4) = 5;
  a(1, 0) = 6;
  a(1, 1) = 7;
  a(1, 2) = 8;
  a(1, 3) = 9;
  a(1, 4) = 10;
  a(2, 0) = 11;
  a(2, 1) = 12;
  a(2, 2) = 13;
  a(2, 3) = 14;
  a(2, 4) = 15;

  result = a.Transpose();

  EXPECT_EQ(result.AccessRows(), 5);
  EXPECT_EQ(result.AccessCols(), 3);

  EXPECT_DOUBLE_EQ(a(0, 0), result(0, 0));
  EXPECT_DOUBLE_EQ(a(0, 1), result(1, 0));
  EXPECT_DOUBLE_EQ(a(0, 2), result(2, 0));
  EXPECT_DOUBLE_EQ(a(0, 3), result(3, 0));
  EXPECT_DOUBLE_EQ(a(0, 4), result(4, 0));

  EXPECT_DOUBLE_EQ(a(1, 0), result(0, 1));
  EXPECT_DOUBLE_EQ(a(1, 1), result(1, 1));
  EXPECT_DOUBLE_EQ(a(1, 2), result(2, 1));
  EXPECT_DOUBLE_EQ(a(1, 3), result(3, 1));
  EXPECT_DOUBLE_EQ(a(1, 4), result(4, 1));

  EXPECT_DOUBLE_EQ(a(2, 0), result(0, 2));
  EXPECT_DOUBLE_EQ(a(2, 1), result(1, 2));
  EXPECT_DOUBLE_EQ(a(2, 2), result(2, 2));
  EXPECT_DOUBLE_EQ(a(2, 3), result(3, 2));
  EXPECT_DOUBLE_EQ(a(2, 4), result(4, 2));
}

TEST(Transpose, test_22) {
  S21Matrix a(0, 5);
  EXPECT_THROW(a.Transpose(), std::length_error);
}

TEST(Transpose, test_23) {
  S21Matrix a(2, 2);
  S21Matrix b(0, 5);
  S21Matrix result(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  result(0, 0) = 4.0;
  result(0, 1) = -3.0;
  result(1, 0) = -2.0;
  result(1, 1) = 1.0;

  b = a.CalcComplements();

  for (int i = 0; i < b.AccessRows(); i++) {
    for (int j = 0; j < b.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(b(i, j), result(i, j));
    }
  }
}

TEST(Transpose, test_24) {
  S21Matrix a(2, 1);
  S21Matrix b(0, 5);
  S21Matrix result(2, 2);

  a(0, 0) = 1;
  a(1, 0) = 3;

  EXPECT_THROW(a.CalcComplements(), std::length_error);

  a.MutateRows(1);
  a.MutateCols(1);

  EXPECT_DOUBLE_EQ(a.CalcComplements()(0, 0), 1);
}

TEST(Transpose, test_25) {
  S21Matrix a(5, 5);
  S21Matrix b(0, 5);
  S21Matrix result(5, 5);

  double res1 = 0.0;
  double res2 = 0.0;

  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;
  a(0, 3) = 5.0001;
  a(0, 4) = 10.0123;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;
  a(1, 3) = 8.0;
  a(1, 4) = 9.003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;
  a(2, 3) = 3.0;
  a(2, 4) = 2.003;

  a(3, 0) = 3.0;
  a(3, 1) = 5.0;
  a(3, 2) = 9.00003;
  a(3, 3) = 3.0;
  a(3, 4) = 10.003;

  a(4, 0) = 7.0;
  a(4, 1) = 8.0;
  a(4, 2) = 3.00003;
  a(4, 3) = 4.0;
  a(4, 4) = 8.003;

  b = a.CalcComplements();

  result(0, 0) = 539.5924786;
  result(0, 1) = -1350.4021189;
  result(0, 2) = -1140.4050000;
  result(0, 3) = -1169.5906778;
  result(0, 4) = 1890.0014400;

  result(1, 0) = -568.1006721;
  result(1, 1) = 502.4746836;
  result(1, 2) = 791.9354081;
  result(1, 3) = 2456.5039660;
  result(1, 4) = -1530.0435600;

  result(2, 0) = 1464.1752928;
  result(2, 1) = -1249.2578551;
  result(2, 2) = -488.3028072;
  result(2, 3) = -2368.6530088;
  result(2, 4) = 1335.0457200;

  result(3, 0) = 468.0843532;
  result(3, 1) = -366.4284224;
  result(3, 2) = 900.4813991;
  result(3, 3) = -1512.0276994;
  result(3, 4) = 375.0439201;

  result(4, 0) = -987.4974783;
  result(4, 1) = 1894.8517495;
  result(4, 2) = -467.4700000;
  result(4, 3) = 1182.5081333;
  result(4, 4) = -585.0291601;

  res1 = (a(0, 0) * b(0, 0)) + (a(0, 1) * b(0, 1)) + (a(0, 2) * b(0, 2)) +
         (a(0, 3) * b(0, 3)) + (a(0, 4) * b(0, 4));
  res2 = a.Determinant();

  EXPECT_EQ(b.EqMatrix(result), true);
  EXPECT_EQ(res1, res2);
}

TEST(Determinant, test_26) {
  S21Matrix a(1, 2);
  EXPECT_THROW(a.Determinant(), std::length_error);
  a.MutateCols(1);
  a(0, 0) = 1.0;
  EXPECT_DOUBLE_EQ(a.Determinant(), 1.0);
}

TEST(operator, test_26) {
  S21Matrix a(1, 2);
  EXPECT_THROW(a.Determinant(), std::length_error);
  a.MutateCols(1);
  a(0, 0) = 1.0;
  EXPECT_DOUBLE_EQ(a.Determinant(), 1.0);
}

TEST(InverseMatrix, test_27) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix result(3, 3);

  a(0, 0) = 2.0;
  a(0, 1) = 5.0;
  a(0, 2) = 7.0;
  a(1, 0) = 6.0;
  a(1, 1) = 3.0;
  a(1, 2) = 4.0;
  a(2, 0) = 5.0;
  a(2, 1) = -2.0;
  a(2, 2) = -3.0;

  b(0, 0) = 1.0;
  b(0, 1) = -1.0;
  b(0, 2) = 1.0;
  b(1, 0) = -38.0;
  b(1, 1) = 41.0;
  b(1, 2) = -34.0;
  b(2, 0) = 27.0;
  b(2, 1) = -29.0;
  b(2, 2) = 24.0;

  result = a.InverseMatrix();

  for (int i = 0; i < b.AccessRows(); i++) {
    for (int j = 0; j < b.AccessCols(); j++)
      EXPECT_DOUBLE_EQ(b(i, j), result(i, j));
  }
}

TEST(InverseMatrix, test_28) {
  S21Matrix a(1, 1);
  S21Matrix b(1, 1);
  S21Matrix result(1, 1);

  a(0, 0) = 2.0;
  b(0, 0) = 0.5;

  result = a.InverseMatrix();

  EXPECT_DOUBLE_EQ(b(0, 0), result(0, 0));
}

TEST(InverseMatrix, test_29) {
  S21Matrix a(3, 3);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(0, 2) = 3.0;
  a(1, 0) = 4.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.0;
  a(2, 0) = 7.0;
  a(2, 1) = 8.0;
  a(2, 2) = 9.0;
  EXPECT_THROW(a.InverseMatrix(), std::length_error);
  S21Matrix b(0, 0);
  EXPECT_THROW(b.InverseMatrix(), std::length_error);
}

TEST(SumOperator, test_30) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b = b + a;

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) - a(i, j));
    }
  }

  b = b - a;
  b += a;

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) - a(i, j));
    }
  }
}

TEST(SubOperator, test_31) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b = b - a;

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) + a(i, j));
    }
  }

  b = b + a;
  b -= a;

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) + a(i, j));
    }
  }
}

TEST(MulNumOperator, test_32) {
  S21Matrix a(3, 4);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  S21Matrix tmp = b;
  b = b * 3;
  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }

  b = tmp;
  b = 3 * b;
  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }

  b = tmp;
  b *= 3;
  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }
}

TEST(EqOperator, test_33) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  EXPECT_EQ(a.AccessCols(), b.AccessCols());

  EXPECT_EQ(b == a, true);
}

TEST(EqOperator, test_34) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b(0, 0) = a(0, 0) - 1.00001;
  b(1, 2) = a(1, 2) - 0.00001;
  b(2, 2) = a(2, 2) + 0.00001;

  EXPECT_EQ(b == a, false);
}

TEST(BrktOperator, test_35) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  const S21Matrix b(a);

  for (int i = 0; i < a.AccessRows(); i++) {
    for (int j = 0; j < a.AccessCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j));
    }
  }

  EXPECT_THROW(b(-1, 0), std::length_error);
}

void InitMatrix(S21Matrix *matrix, double num) {
  for (int i = 0; i < matrix->AccessRows(); i++) {
    for (int j = 0; j < matrix->AccessCols(); j++) {
      (*matrix)(i, j) = num;
    }
  }
}

void InitMatrix2(S21Matrix *matrix, double num) {
  for (int i = 0; i < matrix->AccessRows(); i++) {
    for (int j = 0; j < matrix->AccessCols(); j++) {
      (*matrix)(i, j) = num;
      num++;
    }
  }
}

void InitMatrix3(S21Matrix *matrix) {
  double num = 1;
  for (int i = 0; i < matrix->AccessRows(); i++) {
    for (int j = 0; j < matrix->AccessCols(); j++) {
      if (i == 0 && j > 0)
        (*matrix)(i, j) = 3;
      else
        (*matrix)(i, j) = num;
      num++;
    }
  }
}

TEST(Operation, eqMatrix) {
  S21Matrix matrix1;
  matrix1.MutateRows(3);
  matrix1.MutateCols(3);
  S21Matrix matrix2 = S21Matrix(3, 3);
  InitMatrix(&matrix1, 48.4765765);
  InitMatrix(&matrix2, 48.4765765);
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(Operation, eqMatrix2) {
  S21Matrix matrix1 = S21Matrix(3, 3);
  S21Matrix matrix2 = S21Matrix(3, 3);
  InitMatrix(&matrix1, 48.5765765);
  InitMatrix(&matrix2, 48.4765765);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(Operation, eqMatrix3) {
  S21Matrix matrix1 = S21Matrix(3, 4);
  S21Matrix matrix2 = S21Matrix(3, 3);
  InitMatrix(&matrix1, 48.5765765);
  InitMatrix(&matrix2, 48.5765765);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(Operation, sumMatrix) {
  S21Matrix matrix1 = S21Matrix(5, 5);
  S21Matrix matrix2 = S21Matrix(5, 5);
  S21Matrix sum = S21Matrix(5, 5);
  InitMatrix(&matrix1, 18.4765765);
  InitMatrix(&matrix2, 15.0765765);
  InitMatrix(&sum, 33.553153);
  matrix1.SumMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(sum));
}

TEST(Operation, sumMatrix2) {
  S21Matrix matrix1 = S21Matrix(5, 5);
  S21Matrix matrix2 = S21Matrix(5, 5);
  S21Matrix sum = S21Matrix(5, 5);
  InitMatrix(&matrix1, 25.7765765);
  InitMatrix(&matrix2, 15.0765765);
  InitMatrix(&sum, 33.4765765);
  matrix1.SubMatrix(matrix2);
  EXPECT_FALSE(matrix1.EqMatrix(sum));
}

TEST(Operation, subMatrix) {
  S21Matrix matrix1 = S21Matrix(5, 5);
  S21Matrix matrix2 = S21Matrix(5, 5);
  S21Matrix sub = S21Matrix(5, 5);
  InitMatrix(&matrix1, 50.6765765);
  InitMatrix(&matrix2, 15.0765765);
  InitMatrix(&sub, 35.6000000);
  matrix1.SubMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(sub));
}

TEST(Operation, subMatrix2) {
  S21Matrix matrix1 = S21Matrix(5, 5);
  S21Matrix matrix2 = S21Matrix(5, 5);
  S21Matrix sub = S21Matrix(5, 5);
  InitMatrix(&matrix1, 50.6765765);
  InitMatrix(&matrix2, 15.0765765);
  InitMatrix(&sub, 11.5765765);
  matrix1.SubMatrix(matrix2);
  EXPECT_FALSE(matrix1.EqMatrix(sub));
}

TEST(Operation, mulMatrix) {
  S21Matrix matrix1 = S21Matrix(5, 4);
  S21Matrix matrix2 = S21Matrix(4, 6);
  S21Matrix mul = S21Matrix(5, 6);
  InitMatrix(&matrix1, -1);
  InitMatrix(&matrix2, 4);
  InitMatrix(&mul, -16);
  matrix1.MulMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(mul));
}

TEST(Operation, mulNumber) {
  S21Matrix matrix1 = S21Matrix(5, 4);
  S21Matrix mul = S21Matrix(5, 4);
  InitMatrix(&matrix1, -1);
  InitMatrix(&mul, -16);
  matrix1.MulNumber(16);
  EXPECT_TRUE(matrix1.EqMatrix(mul));
}

TEST(Operation, mulNumber2) {
  S21Matrix matrix1 = S21Matrix(5, 4);
  S21Matrix mul = S21Matrix(5, 4);
  InitMatrix(&matrix1, -1);
  InitMatrix(&mul, -16);
  S21Matrix result = S21Matrix(16 * matrix1);
  EXPECT_TRUE(result.EqMatrix(mul));
}

TEST(Operation, transpose) {
  S21Matrix matrix = S21Matrix(7, 3);
  S21Matrix res = S21Matrix(3, 7);
  InitMatrix(&matrix, -1);
  InitMatrix(&res, -1);
  S21Matrix transpose = matrix.Transpose();
  EXPECT_TRUE(transpose.EqMatrix(res));
}

TEST(Operation, calcComplements) {
  S21Matrix matrix = S21Matrix(3, 3);
  S21Matrix dop = S21Matrix(3, 3);
  InitMatrix2(&matrix, 1);
  dop(0, 0) = -3.0;
  dop(0, 1) = 6.0;
  dop(0, 2) = -3.0;
  dop(1, 0) = 6.0;
  dop(1, 1) = -12;
  dop(1, 2) = 6;
  dop(2, 0) = -3;
  dop(2, 1) = 6;
  dop(2, 2) = -3;
  S21Matrix res = matrix.CalcComplements();
  EXPECT_TRUE(res.EqMatrix(dop));
}

TEST(Operation, inverseMatrix) {
  S21Matrix matrix = S21Matrix(3, 3);
  InitMatrix3(&matrix);
  S21Matrix dop = S21Matrix(3, 3);
  dop(0, 0) = -1.0 / 2.0;
  dop(0, 1) = -1.0 / 2.0;
  dop(0, 2) = 1.0 / 2.0;
  dop(1, 0) = 1.0;
  dop(1, 1) = -2.0;
  dop(1, 2) = 1.0;
  dop(2, 0) = -1.0 / 2.0;
  dop(2, 1) = 13.0 / 6.0;
  dop(2, 2) = -7.0 / 6.0;
  S21Matrix res = matrix.InverseMatrix();
  EXPECT_TRUE(res.EqMatrix(dop));
}

TEST(Operation, operatorSum) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 3;
  dop(1, 0) = 5;
  dop(1, 1) = 7;
  S21Matrix sum = matrix1 + matrix2;
  EXPECT_TRUE(sum == dop);
}

TEST(Operation, operatorSum2) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 3;
  dop(1, 0) = 5;
  dop(1, 1) = 7;
  matrix1 += matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(dop));
}

TEST(Operation, operatorSub) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 1;
  dop(1, 0) = 1;
  dop(1, 1) = 1;
  S21Matrix sum = matrix1 - matrix2;
  EXPECT_TRUE(sum == dop);
}

TEST(Operation, operatorSub2) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 1;
  dop(1, 0) = 1;
  dop(1, 1) = 1;
  matrix1 -= matrix2;
  EXPECT_TRUE(matrix1 == dop);
}

TEST(Operation, operatorMulMatrix) {
  S21Matrix matrix1(5, 4);
  S21Matrix matrix2(4, 6);
  S21Matrix dop(5, 6);
  InitMatrix(&matrix1, -1);
  InitMatrix(&matrix2, 4);
  InitMatrix(&dop, -16);
  S21Matrix mul = matrix1 * matrix2;
  EXPECT_TRUE(mul == dop);
}

TEST(Operation, operatorMulMatrix2) {
  S21Matrix matrix1(5, 4);
  S21Matrix matrix2(4, 6);
  S21Matrix dop(5, 6);
  InitMatrix(&matrix1, -1);
  InitMatrix(&matrix2, 4);
  InitMatrix(&dop, -16);
  matrix1 *= matrix2;
  EXPECT_TRUE(matrix1 == dop);
}

TEST(Operation, operatorMulNumber) {
  S21Matrix matrix(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix(&matrix, 1);
  InitMatrix(&dop, 4);
  S21Matrix mul = matrix * 4;
  EXPECT_TRUE(mul == dop);
}

TEST(Operation, operatorMulNumber2) {
  S21Matrix matrix(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix(&matrix, 1);
  InitMatrix(&dop, 4);
  matrix *= 4;
  EXPECT_TRUE(matrix == dop);
}

TEST(GetAndSet, setSize) {
  S21Matrix matrix1(3, 6);
  S21Matrix matrix2(5, 4);
  matrix2.MutateRows(3);
  matrix2.MutateCols(6);
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(GetAndSet, getRows) {
  S21Matrix matrix(4, 7);
  int rows = matrix.AccessRows();
  EXPECT_TRUE(rows == 4);
}

TEST(GetAndSet, getCols) {
  S21Matrix matrix(4, 7);
  int cols = matrix.AccessCols();
  EXPECT_TRUE(cols == 7);
}

TEST(Construct, moveMatrix) {
  S21Matrix matrix(4, 5);
  InitMatrix2(&matrix, 1);
  S21Matrix dop(matrix);
  S21Matrix result(std::move(matrix));
  EXPECT_TRUE(result == dop);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}