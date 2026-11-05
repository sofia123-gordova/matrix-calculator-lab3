#ifndef MATRIX_H
#define MATRIX_H

/**
 * @file matrix.h
 * @brief Библиотека операций над матрицами.
 */

/**
 * @brief Матрица с динамически выделенной памятью.
 */
struct Matrix {
    double** data; ///< Указатели на строки матрицы.
    int rows;      ///< Количество строк.
    int cols;      ///< Количество столбцов.
};

/**
 * @brief Создаёт матрицу, заполненную нулями.
 * @param rows Количество строк, больше нуля.
 * @param cols Количество столбцов, больше нуля.
 * @return Созданная матрица.
 * @throws std::invalid_argument При некорректных размерах.
 * @throws std::bad_alloc При нехватке памяти.
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Освобождает память матрицы.
 * @param m Матрица для освобождения.
 * @note После вызова исходную структуру нужно обнулить.
 */
void free_matrix(Matrix m);

/**
 * @brief Складывает две матрицы одинакового размера.
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Новая матрица с результатом сложения.
 * @throws std::invalid_argument Если размеры различаются.
 */
Matrix matrix_add(Matrix a, Matrix b);

/**
 * @brief Умножает две матрицы.
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Новая матрица с результатом умножения.
 * @throws std::invalid_argument Если a.cols не равно b.rows.
 */
Matrix matrix_multiply(Matrix a, Matrix b);

/**
 * @brief Выводит матрицу в терминал.
 * @param m Матрица для вывода.
 */
void print_matrix(Matrix m);

/**
 * @brief Создаёт матрицу из одномерного массива по строкам.
 * @param data Массив минимум из rows * cols элементов.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Матрица с копией элементов массива.
 * @throws std::invalid_argument При неверных параметрах.
 */
Matrix matrix_from_array(double* data, int rows, int cols);
/**
 * @brief Проверяет равенство матриц с заданной точностью.
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @param tolerance Допустимая абсолютная разница элементов.
 * @return true, если размеры совпадают и разницы не больше tolerance.
 * @throws std::invalid_argument Если точность отрицательная или не конечная.
 */
bool matrix_equals(Matrix a, Matrix b, double tolerance);
#endif