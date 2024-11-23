#include "tmatrix.h"

#include <gtest.h>

class TDynamicVectorTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		v1 = new TDynamicVector<int>(5);
		v2 = new TDynamicVector<int>(5);
		v3 = new TDynamicVector<int>(3);
	}

	void TearDown() override
	{
		delete v1;
		delete v2;
		delete v3;
	}

	TDynamicVector<int>* v1;
	TDynamicVector<int>* v2;
	TDynamicVector<int>* v3;
};

TEST_F(TDynamicVectorTest, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST_F(TDynamicVectorTest, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST_F(TDynamicVectorTest, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST_F(TDynamicVectorTest, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST_F(TDynamicVectorTest, copied_vector_is_equal_to_source_one)
{
	(*v1)[0] = 2;

	TDynamicVector<int> v2(*v1);

	EXPECT_EQ(*v1, v2);
}

TEST_F(TDynamicVectorTest, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v2(*v1);

	EXPECT_NE(v1, &v2);
}

TEST_F(TDynamicVectorTest, can_get_size)
{
	EXPECT_EQ(5, v1->size());
}

TEST_F(TDynamicVectorTest, can_set_and_get_element)
{
	(*v1)[0] = 4;

	EXPECT_EQ(4, (*v1)[0]);
}

TEST_F(TDynamicVectorTest, throws_when_set_element_with_negative_index)
{
	ASSERT_ANY_THROW((*v1).at(-1) = 7);
}

TEST_F(TDynamicVectorTest, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW((*v1).at(6) = 7);
}

TEST_F(TDynamicVectorTest, can_assign_vector_to_itself)
{
	*v1 = *v1;

	EXPECT_EQ(*v1, *v1);
}

TEST_F(TDynamicVectorTest, can_assign_vectors_of_equal_size)
{
	(*v2)[1] = 7;
	*v1 = *v2;

	EXPECT_EQ(*v1, *v2);
}

TEST_F(TDynamicVectorTest, assign_operator_change_vector_size)
{
	*v1 = *v3;

	EXPECT_EQ(3, v1->size());
}

TEST_F(TDynamicVectorTest, can_assign_vectors_of_different_size)
{
	(*v1)[0] = 4;
	*v1 = *v3;

	EXPECT_EQ(*v1, *v3);
}

TEST_F(TDynamicVectorTest, compare_equal_vectors_return_true)
{
	(*v1)[1] = 7;
	(*v2)[1] = 7;

	EXPECT_TRUE(*v1 == *v2);
}

TEST_F(TDynamicVectorTest, compare_vector_with_itself_return_true)
{
	(*v1)[0] = 4;

	EXPECT_TRUE(*v1 == *v1);
}

TEST_F(TDynamicVectorTest, vectors_with_different_size_are_not_equal)
{
	EXPECT_TRUE(*v1 != *v3);
}

TEST_F(TDynamicVectorTest, can_add_scalar_to_vector)
{
	TDynamicVector<int> res(5);

	for (size_t i = 0; i < 5; i++)
	{
		res[i] = 4;
	}

	*v1 = *v1 + 4;

	EXPECT_EQ(*v1, res);
}

TEST_F(TDynamicVectorTest, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> res(5);

	for (size_t i = 0; i < 5; i++)
	{
		res[i] = -4;
	}

	*v1 = *v1 - 4;

	EXPECT_EQ(*v1, res);
}

TEST_F(TDynamicVectorTest, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> res(5);

	for (size_t i = 0; i < 5; i++)
	{
		res[i] = 10;
	}

	for (size_t i = 0; i < 5; i++)
	{
		(*v1)[i] = 5;
	}

	*v1 = *v1 * 2;

	EXPECT_EQ(*v1, res);
}

TEST_F(TDynamicVectorTest, can_add_vectors_with_equal_size)
{
	for (size_t i = 0; i < 5; i++)
	{
		(*v1)[i] = 8;
		(*v2)[i] = 4;
	}

	TDynamicVector<int> res(5);

	for (size_t i = 0; i < 5; i++)
	{
		res[i] = 12;
	}

	*v2 = *v1 + *v2;
	
	EXPECT_EQ(res, *v2);
}

TEST_F(TDynamicVectorTest, cant_add_vectors_with_not_equal_size)
{
	ASSERT_ANY_THROW(*v1 + *v3);
}

TEST_F(TDynamicVectorTest, can_subtract_vectors_with_equal_size)
{
	for (size_t i = 0; i < 5; i++)
	{
		(*v1)[i] = 10;
	}
	for (size_t i = 0; i < 3; i++)
	{
		(*v2)[i] = 5;
	}

	TDynamicVector<int> res(5);

	res[0] = 5;
	res[1] = 5;
	res[2] = 5;
	res[3] = 10;
	res[4] = 10;

	*v1 = *v1 - *v2;

	EXPECT_EQ(res, *v1);
}

TEST_F(TDynamicVectorTest, cant_subtract_vectors_with_not_equal_size)
{
	ASSERT_ANY_THROW(*v1 - *v3);
}

TEST_F(TDynamicVectorTest, can_multiply_vectors_with_equal_size)
{
	(*v1)[2] = 2;
	(*v2)[2] = 1;

	EXPECT_EQ(2, *v1 * *v2);
}

TEST_F(TDynamicVectorTest, cant_multiply_vectors_with_not_equal_size)
{
	ASSERT_ANY_THROW(*v1 * *v3);
}