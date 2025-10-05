#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> a(5);
  TDynamicMatrix<int> b(a);
  EXPECT_EQ(a, b);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1;
  a[0][1] = 2;
  a[1][0] = 3;
  a[1][1] = 4;
  TDynamicMatrix<int> b(a);

  EXPECT_EQ(b, a);

  b[0][0] = 10;

  EXPECT_EQ(a[0][0], 1);
  EXPECT_EQ(b[0][0], 10);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> a(3);

  EXPECT_EQ(3, a.size());
}
TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1;
  a[0][1] = 2;
  a[1][0] = 3;
  a[1][1] = 4;
  EXPECT_EQ(a[0][0], 1);
  EXPECT_EQ(a[0][1], 2);
  EXPECT_EQ(a[1][0], 3);
  EXPECT_EQ(a[1][1], 4);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> a(2);
  ASSERT_ANY_THROW(a[-2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> a(2);
  ASSERT_ANY_THROW(a[10]);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1;
  a[0][1] = 2;
  a[1][0] = 3;
  a[1][1] = 4;
  TDynamicMatrix<int> b(a);
  b = b;
  cout << b[0][0] << ' ' << a[0][0] << endl;
  cout << b[0][1] << ' ' << a[0][1] << endl;

  cout << b[1][0] << ' ' << a[1][0] << endl;

  cout << b[1][1] << ' ' << a[1][1] << endl;

  EXPECT_EQ(b[0][0], a[0][0]);
  EXPECT_EQ(b[0][1], a[0][1]);
  EXPECT_EQ(b[1][0], a[1][0]);
  EXPECT_EQ(b[1][1], a[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1;
  a[0][1] = 2;
  a[1][0] = 3;
  a[1][1] = 4;
  TDynamicMatrix<int> b(2);
  b = a;
  EXPECT_EQ(b[0][0], a[0][0]);
  EXPECT_EQ(b[0][1], a[0][1]);
  EXPECT_EQ(b[1][0], a[1][0]);
  EXPECT_EQ(b[1][1], a[1][1]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  {
    TDynamicMatrix<int> a(2);
    TDynamicMatrix<int> b(4);
    a = b;
    EXPECT_EQ(4, a.size());
  }
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 10;
  a[0][1] = 20;
  a[1][0] = 30;
  a[1][1] = 40;

  TDynamicMatrix<int> b(3);
  b[0][0] = 1;
  b[0][1] = 2;
  b[0][2] = 3;
  b[1][0] = 4;
  b[1][1] = 5;
  b[1][2] = 6;
  b[2][0] = 7;
  b[2][1] = 8;
  b[2][2] = 9;

  a = b;

  EXPECT_EQ(b[0][0], 1);
  EXPECT_EQ(b[0][1], 2);
  EXPECT_EQ(b[0][2], 3);
  EXPECT_EQ(b[1][0], 4);
  EXPECT_EQ(b[1][1], 5);
  EXPECT_EQ(b[1][2], 6);
  EXPECT_EQ(b[2][0], 7);
  EXPECT_EQ(b[2][1], 8);
  EXPECT_EQ(b[2][2], 9);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1;
  a[0][1] = 2;
  a[1][0] = 3;
  a[1][1] = 4;
  TDynamicMatrix<int> b(2);
  b[0][0] = 1;
  b[0][1] = 2;
  b[1][0] = 3;
  b[1][1] = 4;
  EXPECT_EQ(true, b == a);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1;
  a[0][1] = 2;
  a[1][0] = 3;
  a[1][1] = 4;

  EXPECT_EQ(true, a == a);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1;
  a[0][1] = 2;
  a[1][0] = 3;
  a[1][1] = 4;
  TDynamicMatrix<int> b(3);
  b[0][0] = 1;
  b[0][1] = 2;
  b[1][0] = 3;
  b[1][1] = 4;
  EXPECT_NE(true, b == a);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1;
  a[0][1] = 2;
  a[1][0] = 3;
  a[1][1] = 4;
  TDynamicMatrix<int> b(2);
  b[0][0] = 1;
  b[0][1] = 2;
  b[1][0] = 3;
  b[1][1] = 4;

  TDynamicMatrix<int> c(2);

  c = a + b;

  EXPECT_EQ(c[0][0], 2);
  EXPECT_EQ(c[0][1], 4);
  EXPECT_EQ(c[1][0], 6);
  EXPECT_EQ(c[1][1], 8);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> a(5);
  TDynamicMatrix<int> b(2);
  ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1;
  a[0][1] = 2;
  a[1][0] = 3;
  a[1][1] = 4;
  TDynamicMatrix<int> b(2);
  b[0][0] = 1;
  b[0][1] = 2;
  b[1][0] = 3;
  b[1][1] = 4;

  TDynamicMatrix<int> c(2);

  c = a - b;

  EXPECT_EQ(c[0][0], 0);
  EXPECT_EQ(c[0][1], 0);
  EXPECT_EQ(c[1][0], 0);
  EXPECT_EQ(c[1][1], 0);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> a(5);
  TDynamicMatrix<int> b(2);
  ASSERT_ANY_THROW(a - b);
}
