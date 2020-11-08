//
// Created by itayshu on 9/3/2020.
//

#ifndef MATRIX_H
#define MATRIX_H

#define DIMENSION_ERROR "Invalid matrix dimensions.\n"

#define ZERO_DIV_ERROR "Division by zero.\n"

#define INDEX_ERROR "Index out of range.\n"

#define FILE_ERROR "Error loading from input stream.\n"

#include <iostream>

/**
 * Matrix class
 */
class Matrix
{

    int rows;
    int cols;
    float *val;

public:
    /**
    * Ctor for Matrix
    * @param rows rows of matrix
    * @param cols - cols of matrix
    */
    Matrix(int rows, int cols);

    /**
    * Default ctor
    */
    Matrix();

    /**
    * copy ctor
    * @param m  matrix to copy
    */
    Matrix(Matrix const &m);

    /**
     * dtor for matrix
     */
    ~Matrix();

    /**
     * return number of rows
     * @return
     */
    int getRows() const;

    /**
     * return number of cols
     * @return
     */
    int getCols() const;

    /**
     * vecorize the matrix
     */
    Matrix &vectorize();

    /**
     *prints matrix
     */
    void print();

    /**
     * assaigment other to this matrix
     * @param other matrix
     * @return this matrix
     */
    Matrix &operator=(const Matrix &a);

    /**
     * Matrix multiplication
     * return the result
     */
    Matrix operator*(const Matrix &other) const;

    /**
     * Matrix multiplication with scalar
     * @param c
     * @return result matrix
     */
    Matrix operator*(float c) const;

    /**
     * Scalar mult. On the right
     * @param c scalar
     * @param m matrix
     * @return result matrix
     */
    friend Matrix operator*(float c, const Matrix &m);

    /**
     * Scalar mult on this matrix
     * @param c
     */
    void operator*=(float c);

    /**
     * matrix mult.
     * @param m matrix
     * @return this matrix after mult
     */
    Matrix &operator*=(const Matrix &m);

    /**
     * Scalar division on the right
     * @param c
     * @return result matrix
     */
    Matrix operator/(float c) const;

    /**
     * Divide by scalar
     * @param c
     * @return this matrix after divide
     */
    Matrix &operator/=(float c);

    /**
     * Matrix addition
     * @param m
     * @return res matrix after addition
     */
    Matrix operator+(const Matrix &m);

    /**
     * Matrix addition
     * @param m
     * @return result matrix
     */
    Matrix operator+(const Matrix &m) const;

    /**
     * Matrix addition accumulation with matrix
     * @param m
     * @return this matrix after matrix addition
     */
    Matrix &operator+=(const Matrix &m);

    /**
     * Matrix addition accumulation with scalar
     * @param m
     * @return this matrix after matrix addition
     */
    Matrix &operator+=(float c);

    /**
     * Parenthesis indexing
     * @param i rows
     * @param j cols
     * @return val in this index
     */
    float &operator()(int i, int j);

    /**
     * Parenthesis indexing on const matrix
     * @param i rows
     * @param j cols
     * @return val in this index
     */
    float &operator()(int i, int j) const;

    /**
     * Brackets indexing
     * @param i
     * @return value in val index
     */
    float &operator[](int i);

    /**
     * Brackets indexing for const matrix
     * @param i
     * @return value in val index
     */
    float &operator[](int i) const;

    /**
     * Equality between matrixs
     * @param m
     * @return bool for this Equality
     */
    bool operator==(const Matrix &m) const;

    /**
     * Not equal between matrixs
     * @param m
     * @return bool for this Not equal
     */
    bool operator!=(const Matrix &m) const;

    /**
     * Fills matrix elements. Reads from given input stream.
     * @param is - input stream
     * @param matrix - matrix
     * @return return the input stream
     */
    friend std::istream &operator>>(std::istream &is, Matrix &matrix);

    /**
     * Fills file elements. Reads from given matrix.
     * @param os - output stream
     * @param matrix - matrix
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

    /**
     * prints matrix, for const matrix
     */
    void print() const;
};


#endif //MATRIX_H
