#include "matrix.h"

#include <exception>
#include <iostream>

/**
 * @brief Демонстрирует операции над матрицами.
 * @return 0 при успехе, 1 при ошибке.
 */
int main() {
    Matrix a{nullptr, 0, 0};
    Matrix b{nullptr, 0, 0};
    Matrix sum{nullptr, 0, 0};
    Matrix product{nullptr, 0, 0};

    int result = 0;

    try {
        double values_a[] = {1, 2, 3, 4};
        double values_b[] = {5, 6, 7, 8};

        a = matrix_from_array(values_a, 2, 2);
        b = matrix_from_array(values_b, 2, 2);

        std::cout << "Matrix A:\n";
        print_matrix(a);

        std::cout << "\nMatrix B:\n";
        print_matrix(b);

        sum = matrix_add(a, b);
        std::cout << "\nA + B:\n";
        print_matrix(sum);

        product = matrix_multiply(a, b);
        std::cout << "\nA * B:\n";
        print_matrix(product);
        std::cout << std::boolalpha;
        std::cout << "\nVariant 5: matrix comparison\n";

        std::cout << "A equals A: "
                  << matrix_equals(a, a, 0.001) << '\n';

        std::cout << "A equals B: "
                  << matrix_equals(a, b, 0.001) << '\n';

        b.data[0][0] = 1.0001;
        b.data[0][1] = 2;
        b.data[1][0] = 3;
        b.data[1][1] = 4;

        std::cout << "Close matrices, tolerance 0.001: "
                  << matrix_equals(a, b, 0.001) << '\n';

        std::cout << "Close matrices, tolerance 0.00001: "
                  << matrix_equals(a, b, 0.00001) << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        result = 1;
    }

    free_matrix(a);
    free_matrix(b);
    free_matrix(sum);
    free_matrix(product);

    return result;

}
