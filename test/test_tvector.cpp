#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
  int a[4] = {1, 2, 3, 4};
  TDynamicVector<int> b(a, 4);
  TDynamicVector<int> c(b);
  EXPECT_EQ(b, c);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  int a[4] = {1, 2, 3, 4};
  TDynamicVector<int> b(a, 4);

  TDynamicVector<int> c;
  c = b;
  c[0] = 10;
  EXPECT_NE(b[0], 10);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(4);

  ASSERT_ANY_THROW(v[-1]);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(4);

  ASSERT_ANY_THROW(v[10]);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(4);
  ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> v(4);
  TDynamicVector<int> b(4);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  v[3] = 4;
  // b[0] = 1; b[1] = 2; b[2] = 3; b[3] = 4;
  b = v;
  EXPECT_EQ(b[0], v[0]);
  EXPECT_EQ(b[1], v[1]);
  EXPECT_EQ(b[2], v[2]);
  EXPECT_EQ(b[3], v[3]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> v(4);
  TDynamicVector<int> b(5);
  v = b;
  EXPECT_EQ(5, v.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> v(4);
  TDynamicVector<int> b(5);
  ASSERT_NO_THROW(b = v);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> v(4);
  TDynamicVector<int> b(v);
  EXPECT_EQ(true, v == b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> v(4);
  EXPECT_EQ(true, v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> v(4);
  TDynamicVector<int> b(5);
  EXPECT_NE(true, v == b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> v(4);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  v[3] = 4;
  v = v + 2;
  EXPECT_EQ(3, v[0]);
  EXPECT_EQ(4, v[1]);
  EXPECT_EQ(5, v[2]);
  EXPECT_EQ(6, v[3]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> v(4);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  v[3] = 4;
  v = v - 1;
  EXPECT_EQ(0, v[0]);
  EXPECT_EQ(1, v[1]);
  EXPECT_EQ(2, v[2]);
  EXPECT_EQ(3, v[3]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> v(4);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  v[3] = 4;
  v = v * 2;
  EXPECT_EQ(2, v[0]);
  EXPECT_EQ(4, v[1]);
  EXPECT_EQ(6, v[2]);
  EXPECT_EQ(8, v[3]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> v(4);
  TDynamicVector<int> b(4);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  v[3] = 4;
  b[0] = 1;
  b[1] = 2;
  b[2] = 3;
  b[3] = 4;
  v = v + b;
  EXPECT_EQ(2, v[0]);
  EXPECT_EQ(4, v[1]);
  EXPECT_EQ(6, v[2]);
  EXPECT_EQ(8, v[3]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(4);
  TDynamicVector<int> b(5);
  ASSERT_ANY_THROW(v + b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> v(4);
  TDynamicVector<int> b(4);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  v[3] = 4;
  b[0] = 1;
  b[1] = 2;
  b[2] = 3;
  b[3] = 4;
  v = v - b;
  EXPECT_EQ(0, v[0]);
  EXPECT_EQ(0, v[1]);
  EXPECT_EQ(0, v[2]);
  EXPECT_EQ(0, v[3]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(4);
  TDynamicVector<int> b(5);
  ASSERT_ANY_THROW(v - b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> v(4);
  TDynamicVector<int> b(4);
  int c;
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  v[3] = 4;
  b[0] = 1;
  b[1] = 2;
  b[2] = 3;
  b[3] = 4;
  c = v * b;
  EXPECT_EQ(30, c);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(4);
  TDynamicVector<int> b(5);
  ASSERT_ANY_THROW(v * b);
}
