#include "matrix.h"

#include <gtest/gtest.h>
#include <stdexcept>

TEST(MatrixTest, CreateFilledWithZeros) {
    Matrix a = create_matrix(2, 3);

    EXPECT_EQ(a.rows, 2);
    EXPECT_EQ(a.cols, 3);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            EXPECT_DOUBLE_EQ(a.data[i][j], 0.0);
        }
    }

    free_matrix(a);
}

TEST(MatrixTest, InvalidDimensions) {
    EXPECT_THROW(create_matrix(0, 3), std::invalid_argument);
    EXPECT_THROW(create_matrix(2, -1), std::invalid_argument);
}

TEST(MatrixTest, FromArrayCopiesData) {
    double values[] = {1, 2, 3, 4, 5, 6};
    Matrix a = matrix_from_array(values, 2, 3);

    values[0] = 100;

    EXPECT_DOUBLE_EQ(a.data[0][0], 1);
    EXPECT_DOUBLE_EQ(a.data[1][0], 4);
    EXPECT_DOUBLE_EQ(a.data[1][2], 6);

    free_matrix(a);
}

TEST(MatrixTest, NullArray) {
    EXPECT_THROW(
        matrix_from_array(nullptr, 2, 2),
        std::invalid_argument
    );
}

TEST(MatrixTest, Addition) {
    double x[] = {1, 2, 3, 4};
    double y[] = {5, 6, 7, 8};

    Matrix a = matrix_from_array(x, 2, 2);
    Matrix b = matrix_from_array(y, 2, 2);
    Matrix c = matrix_add(a, b);

    EXPECT_DOUBLE_EQ(c.data[0][0], 6);
    EXPECT_DOUBLE_EQ(c.data[0][1], 8);
    EXPECT_DOUBLE_EQ(c.data[1][0], 10);
    EXPECT_DOUBLE_EQ(c.data[1][1], 12);

    free_matrix(a);
    free_matrix(b);
    free_matrix(c);
}

TEST(MatrixTest, AdditionWrongSize) {
    Matrix a = create_matrix(2, 2);
    Matrix b = create_matrix(2, 3);

    EXPECT_THROW(matrix_add(a, b), std::invalid_argument);

    free_matrix(a);
    free_matrix(b);
}

TEST(MatrixTest, RectangularMultiplication) {
    double x[] = {1, 2, 3, 4, 5, 6};
    double y[] = {7, 8, 9, 10, 11, 12};

    Matrix a = matrix_from_array(x, 2, 3);
    Matrix b = matrix_from_array(y, 3, 2);
    Matrix c = matrix_multiply(a, b);

    EXPECT_EQ(c.rows, 2);
    EXPECT_EQ(c.cols, 2);
    EXPECT_DOUBLE_EQ(c.data[0][0], 58);
    EXPECT_DOUBLE_EQ(c.data[0][1], 64);
    EXPECT_DOUBLE_EQ(c.data[1][0], 139);
    EXPECT_DOUBLE_EQ(c.data[1][1], 154);

    free_matrix(a);
    free_matrix(b);
    free_matrix(c);
}

TEST(MatrixTest, MultiplicationWrongSize) {
    Matrix a = create_matrix(2, 3);
    Matrix b = create_matrix(2, 2);

    EXPECT_THROW(matrix_multiply(a, b), std::invalid_argument);

    free_matrix(a);
    free_matrix(b);
}

TEST(MatrixTest, MinimumSize) {
    double x[] = {3};
    double y[] = {4};

    Matrix a = matrix_from_array(x, 1, 1);
    Matrix b = matrix_from_array(y, 1, 1);
    Matrix c = matrix_multiply(a, b);

    EXPECT_EQ(c.rows, 1);
    EXPECT_EQ(c.cols, 1);
    EXPECT_DOUBLE_EQ(c.data[0][0], 12);

    free_matrix(a);
    free_matrix(b);
    free_matrix(c);
}

TEST(MatrixTest, EqualsWithTolerance) {
    double x[] = {1, 2};
    double y[] = {1.0001, 2};

    Matrix a = matrix_from_array(x, 1, 2);
    Matrix b = matrix_from_array(y, 1, 2);

    EXPECT_TRUE(matrix_equals(a, b, 0.001));
    EXPECT_FALSE(matrix_equals(a, b, 0.00001));
    EXPECT_TRUE(matrix_equals(a, a, 0));

    free_matrix(a);
    free_matrix(b);
}

TEST(MatrixTest, EqualsAtToleranceBoundary) {
    double x[] = {1};
    double y[] = {1.5};

    Matrix a = matrix_from_array(x, 1, 1);
    Matrix b = matrix_from_array(y, 1, 1);

    EXPECT_TRUE(matrix_equals(a, b, 0.5));
    EXPECT_FALSE(matrix_equals(a, b, 0.49));

    free_matrix(a);
    free_matrix(b);
}

TEST(MatrixTest, EqualsWrongSize) {
    Matrix a = create_matrix(2, 2);
    Matrix b = create_matrix(2, 3);

    EXPECT_FALSE(matrix_equals(a, b, 0.001));

    free_matrix(a);
    free_matrix(b);
}

TEST(MatrixTest, NegativeTolerance) {
    Matrix a = create_matrix(1, 1);

    EXPECT_THROW(matrix_equals(a, a, -0.1), std::invalid_argument);

    free_matrix(a);
}

TEST(MatrixTest, FreeEmptyMatrix) {
    Matrix a{nullptr, 0, 0};

    EXPECT_NO_THROW(free_matrix(a));
    EXPECT_NO_THROW(free_matrix(a));
}