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
	TDynamicMatrix<int> m1(2);

	m1[0][0] = 7;

	TDynamicMatrix<int> m2(m1);

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(m1);

	EXPECT_NE(&m1, &m2);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(7);

	EXPECT_EQ(7, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(4);

	int* arr = new int[5] { 1, 2, 0, 1 };

	TDynamicVector<int> v(arr, 4);

	delete[] arr;

	m[1] = v;

	EXPECT_EQ(v, m[1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(4);

	int* arr = new int[5] { 1, 1, 1, 1 };

	TDynamicVector<int> v(arr, 4);

	delete[] arr;

	ASSERT_ANY_THROW(m.at(-2) = v);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(4);

	int* arr = new int[4] { 1, 1, 1, 1 };

	TDynamicVector<int> v(arr, 4);

	delete[] arr;

	ASSERT_ANY_THROW(m.at(4) = v);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m1(5);
	
	m1[0][0] = 5;

	TDynamicMatrix<int> m2(m1);

	m1 = m1;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(2);

	m1[0][0] = 7;
	m1 = m2;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(4);

	m1 = m2;

	EXPECT_EQ(4, m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(4);

	m1 = m2;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(2);

	m1[0][0] = 7;
	m2[0][0] = 7;

	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(2);

	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);

	EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);
	TDynamicMatrix<int> m3(5);

	m1[0][0] = 5;
	m2[0][0] = 5;
	m3[0][0] = 10;

	EXPECT_EQ(m3, m1 + m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);

	m1[0][0] = 10;
	m2[0][0] = 5;

	EXPECT_EQ(m2, m1 - m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);

	ASSERT_ANY_THROW(m2 - m1);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_scalar)
{
	TDynamicMatrix<int> m(3);

	int* arr = new int[3] { 1, 3, 5 };

	TDynamicVector<int> v(arr, 3);

	delete[] arr;

	m[0] = v;

	TDynamicMatrix<int> res(3);

	res[0] = v * 3;

	EXPECT_EQ(res, m * 3);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_vector_equal_size)
{
	TDynamicMatrix<int> m(3);

	int* arr1 = new int[3] { 2, 1, 4 };
	int* arr2 = new int[3] { 1, 0, 2 };

	TDynamicVector<int> v1(arr1, 3);
	TDynamicVector<int> v2(arr2, 3);

	delete[] arr1;
	delete[] arr2;

	m[0] = v1;

	TDynamicVector<int> res(3);

	res[0] = 10;

	EXPECT_EQ(res, m * v2);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_vector_not_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicVector<int> v(2);

	ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(3);

	int* arr1 = new int[5] { 1, 1, 2 };
	int* arr2 = new int[5] { 0, 2, 1 };

	TDynamicVector<int> v1(arr1, 3);
	TDynamicVector<int> v2(arr2, 3);

	delete[] arr1;
	delete[] arr2;

	m1[2] = v1;
	m2[2] = v2;

	TDynamicMatrix<int> res(3);

	res[2] = v2 * 2;

	EXPECT_EQ(res, m1 * m2);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(2);

	ASSERT_ANY_THROW(m1 * m2);
}