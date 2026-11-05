#include "matrix.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }

    Matrix m{nullptr, rows, cols};

    // Скобки () заполняют указатели значениями nullptr.
    m.data = new double*[rows]();

    try {
        for (int i = 0; i < rows; i++) {
            // Скобки () заполняют элементы нулями.
            m.data[i] = new double[cols]();
        }
    } catch (...) {
        // Освобождаем уже выделенную память при ошибке.
        free_matrix(m);
        throw;
    }

    return m;
}

void free_matrix(Matrix m) {
    if (m.data == nullptr) {
        return;
    }

    for (int i = 0; i < m.rows; i++) {
        delete[] m.data[i];
    }

    delete[] m.data;
}

Matrix matrix_add(Matrix a, Matrix b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Matrix sizes must match");
    }

    Matrix result = create_matrix(a.rows, a.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }

    return result;
}

Matrix matrix_multiply(Matrix a, Matrix b) {
    if (a.cols != b.rows) {
        throw std::invalid_argument("Incompatible matrix sizes");
    }

    Matrix result = create_matrix(a.rows, b.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int k = 0; k < a.cols; k++) {
            for (int j = 0; j < b.cols; j++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }

    return result;
}

void print_matrix(Matrix m) {
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        std::cout << "[Empty matrix]\n";
        return;
    }

    for (int i = 0; i < m.rows; i++) {
        std::cout << "|";

        for (int j = 0; j < m.cols; j++) {
            std::cout << std::setw(10) << m.data[i][j];
        }

        std::cout << " |\n";
    }
}

Matrix matrix_from_array(double* data, int rows, int cols) {
    if (data == nullptr || rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Invalid array or matrix dimensions");
    }

    Matrix m = create_matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.data[i][j] = data[i * cols + j];
        }
    }

    return m;
}
bool matrix_equals(Matrix a, Matrix b, double tolerance) {
    if (!std::isfinite(tolerance) || tolerance < 0) {
        throw std::invalid_argument("Invalid tolerance");
    }

    if (a.rows != b.rows || a.cols != b.cols) {
        return false;
    }

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            double x = a.data[i][j];
            double y = b.data[i][j];

            if (x == y) {
                continue;
            }

            if (!std::isfinite(x) || !std::isfinite(y) ||
                std::fabs(x - y) > tolerance) {
                return false;
            }
        }
    }

    return true;
}