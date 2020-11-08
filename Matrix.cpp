//
// Created by itayshu on 9/3/2020.
//

#include <iostream>
#include "Matrix.h"
#include "sstream"

/**
 * Default ctor
 */
Matrix::Matrix() : Matrix(1, 1)
{
}

/**
 * Ctor for Matrix
 * @param rows rows of matrix
 * @param cols - cols of matrix
 */
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols)
{
    if (rows < 0 || cols < 0)
    {
        std::cerr << DIMENSION_ERROR;
        exit(EXIT_FAILURE);
    }
    val = new float[cols * rows];
    for (int i = 0; i < rows * cols; ++i)
    {
        val[i] = 0;
    }
}

/**
 * copy ctor
 * @param m  matrix to copy
 */
Matrix::Matrix(Matrix const &m) : rows(m.getRows()), cols(m.getCols()), val(new float[rows * cols])
{
    for (int i = 0; i < rows * cols; ++i)
    {
        this->val[i] = m.val[i];
    }
}

/**
 * dtor for matrix
 */
Matrix::~Matrix()
{
    delete[] val;
}

/**
 * return number of rows
 * @return
 */
int Matrix::getRows() const
{
    return rows;
}

/**
 * return number of cols
 * @return
 */
int Matrix::getCols() const
{
    return cols;
}

/**
 * vecorize the matrix
 */
Matrix &Matrix::vectorize()
{
    rows = cols * rows;
    cols = 1;
    return (*this);
}

/**
 * prints matrix, for const matrix
 */
void Matrix::print() const
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cout << (*this)(i, j) << " ";
        }
        if (i != rows - 1)
        {
            std::cout << std::endl;
        }
    }
}

/**
 *prints matrix
 */
void Matrix::print()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cout << val[i * cols + j] << " ";
        }
        if (i != rows - 1)
        {
            std::cout << std::endl;
        }
    }
}

/**
 * assaigment other to this matrix
 * @param other matrix
 * @return this matrix
 */
Matrix &Matrix::operator=(const Matrix &other)
{
    if (this == &other)
    {
        return *this;
    }
    this->cols = other.getCols();
    this->rows = other.getRows();
    delete[]val;
    val = new float[other.getRows() * other.getCols()];
    for (int i = 0; i < cols * rows; ++i)
    {
        this->val[i] = other[i];
    }
    return *this;
}

/**
 * Matrix multiplication
 * return the result
 */
Matrix Matrix::operator*(const Matrix &other) const
{
    if (this->cols != other.getRows())
    {
        std::cerr << DIMENSION_ERROR;
        exit(EXIT_FAILURE);
    }
    Matrix m(this->rows, other.getCols());
    float sum = 0;
    int mInd = 0;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < other.getCols(); ++j)
        {
            for (int k = 0; k < cols; ++k)
            {
                float a = (*this)(i, k);
                float b = other(k, j);
                sum += a * b;
            }
            m.val[mInd] = sum;
            sum = 0;
            mInd++;
        }
    }
    return m;
}

/**
 * Matrix multiplication with scalar
 * @param c
 * @return result matrix
 */
Matrix Matrix::operator*(float c) const
{
    Matrix m(this->rows, this->cols);
    for (int i = 0; i < cols * rows; ++i)
    {
        m.val[i] = val[i] * c;
    }

    return m;
}

/**
 * Scalar mult. On the right
 * @param c scalar
 * @param m matrix
 * @return result matrix
 */
Matrix operator*(float c, const Matrix &m)
{
    Matrix matrix(m.getRows(), m.getCols());
    matrix = m * c;
    return matrix;
}

/**
 * Scalar mult on this matrix
 * @param c
 */
void Matrix::operator*=(float c)
{
    for (int i = 0; i < cols * rows; ++i)
    {
        val[i] *= c;
    }
}

/**
 * matrix mult.
 * @param m matrix
 * @return this matrix after mult
 */
Matrix &Matrix::operator*=(const Matrix &m)
{
    *this = *this * m;
    return *this;
}

/**
 * Parenthesis indexing
 * @param i rows
 * @param j cols
 * @return val in this index
 */
float &Matrix::operator()(int i, int j)
{
    if (i < 0 || j < 0 || i >= this->rows || j >= this->cols)
    {
        std::cerr << INDEX_ERROR;
        exit(EXIT_FAILURE);
    }
    return this->val[i * cols + j];
}

/**
 * Parenthesis indexing on const matrix
 * @param i rows
 * @param j cols
 * @return val in this index
 */
float &Matrix::operator()(int i, int j) const
{
    if (i < 0 || j < 0 || i >= this->rows || j >= this->cols)
    {
        std::cerr << INDEX_ERROR;
        exit(EXIT_FAILURE);
    }
    return this->val[i * cols + j];
}

/**
 * Brackets indexing
 * @param i
 * @return value in val index
 */
float &Matrix::operator[](int i)
{
    if (i < 0 || i >= this->cols * this->rows)
    {
        std::cerr << INDEX_ERROR;
        exit(EXIT_FAILURE);
    }
    return this->val[i];
}

/**
 * Brackets indexing for const matrix
 * @param i
 * @return value in val index
 */
float &Matrix::operator[](int i) const
{
    if (i < 0 || i >= this->cols * this->rows)
    {
        std::cerr << INDEX_ERROR;
        exit(EXIT_FAILURE);
    }
    return this->val[i];
}

/**
 * Equality between matrixs
 * @param m
 * @return bool for this Equality
 */
bool Matrix::operator==(const Matrix &m) const
{
    if (this->rows == m.getRows() && this->cols == m.getCols())
    {
        for (int i = 0; i < cols * rows; ++i)
        {
            if ((*this)[i] != m[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

/**
 * Not equal between matrixs
 * @param m
 * @return bool for this Not equal
 */
bool Matrix::operator!=(const Matrix &m) const
{
    return !((*this) == m);
}

/**
 * Fills matrix elements. Reads from given input stream.
 * @param is - input stream
 * @param matrix - matrix
 * @return return the input stream
 */
std::istream &operator>>(std::istream &is, Matrix &matrix)
{
    if (!is.good())
    {
        std::cerr << FILE_ERROR;
        exit(EXIT_FAILURE);
    }
    std::string line;
    std::getline(is, line);
    std::stringstream ss(line);
    float s;
    int i = 0;
    while (i < matrix.getRows() * matrix.getCols())
    {
        if (ss >> s)
        {
            matrix[i] = s;
            ++i;
        }
        else if (std::getline(is, line))
        {
            ss = std::stringstream(line);
        }
        else
        {
            std::cerr << FILE_ERROR;
            exit(EXIT_FAILURE);
        }
    }
    return is;
}

/**
 * Fills file elements. Reads from given matrix.
 * @param os - output stream
 * @param matrix - matrix
 * @return output stream
 */
std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
{
    for (int i = 0; i < matrix.getRows(); ++i)
    {
        for (int j = 0; j < matrix.getCols(); ++j)
        {
            os << matrix(i, j);
            if (j != matrix.getCols() - 1)
            {
                os << " ";
            }
        }
        if (i != matrix.getRows() - 1)
        {
            os << std::endl;
        }
    }
    return os;
}

/**
 * Matrix addition
 * @param m
 * @return res matrix after addition
 */
Matrix Matrix::operator+(const Matrix &m)
{
    if (this->rows != m.getRows() || this->cols != m.getCols())
    {
        std::cerr << DIMENSION_ERROR;
        exit(EXIT_FAILURE);
    }
    Matrix matrix(this->rows, this->cols);
    for (int i = 0; i < rows * cols; ++i)
    {
        matrix[i] = (*this)[i] + m[i];
    }
    return matrix;
}

/**
 * Scalar division on the right
 * @param c
 * @return result matrix
 */
Matrix Matrix::operator/(float c) const
{
    if (c == 0)
    {
        std::cerr << ZERO_DIV_ERROR;
        exit(EXIT_FAILURE);
    }
    return (*this) * (1 / c);
}

/**
 * Divide by scalar
 * @param c
 * @return this matrix after divide
 */
Matrix &Matrix::operator/=(float c)
{
    if (c == 0)
    {
        std::cerr << ZERO_DIV_ERROR;
        exit(EXIT_FAILURE);
    }
    (*this) *= (1 / c);
    return (*this);
}

/**
 * Matrix addition accumulation with matrix
 * @param m
 * @return this matrix after matrix addition
 */
Matrix &Matrix::operator+=(const Matrix &m)
{
    for (int i = 0; i < cols * rows; ++i)
    {
        (*this)[i] += m[i];
    }
    return (*this);
}

/**
 * Matrix addition accumulation with scalar
 * @param m
 * @return this matrix after matrix addition
 */
Matrix &Matrix::operator+=(const float c)
{
    for (int i = 0; i < rows * cols; ++i)
    {
        (*this)[i] += c;
    }
    return (*this);
}

/**
 * Matrix addition
 * @param m
 * @return result matrix
 */
Matrix Matrix::operator+(const Matrix &m) const
{
    Matrix matrix(this->rows, this->cols);
    for (int i = 0; i < rows * cols; ++i)
    {
        matrix[i] = (*this)[i] + m[i];
    }
    return matrix;
}





