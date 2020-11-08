//
// Created by ITAY on 9/4/2020.
//

#include <cmath>
#include "Matrix.h"

#define MAX_SHADE 255

#define MIN_SHADE 0

#define NUMBER_OF_SHADES 256

void checkWhichMult(const Matrix &matrix, int i, int j, int k, Matrix &image, float &sum);

/**
 * Performs quantization on the input image by the given
 * number of levels. Returns new matrix which is the result
 * of running the operator on the image
 * @param image
 * @param levels
 * @return
 */
Matrix quantization(const Matrix &image, int levels)
{
    Matrix m(image.getRows(), image.getCols());
    int numOfShades = (NUMBER_OF_SHADES / levels) + 1;
    int *shades = new int[numOfShades];
    shades[0] = 0;
    for (int i = 1; i < levels + 1; ++i)
    {
        shades[i] = (NUMBER_OF_SHADES / levels) * i;
    }

    int *avgShades = new int[NUMBER_OF_SHADES / levels];
    for (int j = 0; j < levels; ++j)
    {
        avgShades[j] = ((shades[j] + shades[j + 1] - 1) / 2);
    }
    for (int k = 0; k < image.getCols() * image.getRows(); ++k)
    {
        for (int i = 0; i < levels; ++i)
        {
            if (shades[i] <= (int) image[k] && (int) image[k] < shades[i + 1])
            {
                m[k] = (float) avgShades[i];
                break;
            }
        }
    }
    delete[] shades;
    delete[] avgShades;
    return m;
}

/**
 * convolution of two matrix
 * @param image
 * @param matrix 3X3 matrix
 * @return result of convolution
 */
Matrix convolution(Matrix image, const Matrix &matrix)
{
    float sum = 0;
    Matrix resMatrix(image.getRows(), image.getCols());

    for (int i = 0; i < image.getRows(); ++i)
    {
        for (int j = 0; j < image.getCols(); ++j)
        {
            for (int k = 0; k < matrix.getRows() * matrix.getCols(); ++k)
            {
                checkWhichMult(matrix, i, j, k, image, sum);
            }
            resMatrix(i, j) = rintf(sum);
            sum = 0;
        }
    }
    return resMatrix;
}

/**
 * check which index of image should we multiplay with the matrix
 * @param matrix
 * @param i rows of image
 * @param j cols if image
 * @param k index of matrix
 * @param image
 * @param sum - sum of mult
 */
void checkWhichMult(const Matrix &matrix, int i, int j, int k, Matrix &image, float &sum)
{
    if (k == 0)
    {
        if (!(i == 0 || j == 0))
        {
            sum += image(i - 1, j - 1) * matrix[k];
        }
    }
    if (k == 1)
    {
        if (i != 0)
        {
            sum += image(i - 1, j) * matrix[k];
        }
    }
    if (k == 2)
    {
        if (!(i == 0 || j == image.getCols() - 1))
        {
            sum += image(i - 1, j + 1) * matrix[k];
        }
    }
    if (k == 3)
    {
        if (j != 0)
        {
            sum += image(i, j - 1) * matrix[k];
        }
    }
    if (k == 4)
    {
        sum += image(i, j) * matrix[k];
    }
    if (k == 5)
    {
        if (j != image.getCols() - 1)
        {
            sum += image(i, j + 1) * matrix[k];
        }
    }
    if (k == 6)
    {
        if (!(i == image.getRows() - 1 || j == 0))
        {
            sum += image(i + 1, j - 1) * matrix[k];
        }
    }
    if (k == 7)
    {
        if (i != image.getRows() - 1)
        {
            sum += image(i + 1, j) * matrix[k];
        }
    }
    if (k == 8)
    {
        if (!(i == image.getRows() - 1 || j == image.getCols() - 1))
        {
            sum += image(i + 1, j + 1) * matrix[k];
        }
    }
}

/**
 * checks if we're not exceed our color range limit
 * @param resMat
 * @return normalize the result matrix
 */
Matrix &normalizeMatrix(Matrix &resMat)
{
    for (int i = 0; i < resMat.getRows() * resMat.getCols(); ++i)
    {
        if (resMat[i] > MAX_SHADE)
        {
            resMat[i] = MAX_SHADE;
        }
        if (resMat[i] < MIN_SHADE)
        {
            resMat[i] = MIN_SHADE;
        }
    }
    return resMat;
}

/**
 * Performs gaussian blurring on the input image. Returns
 * new matrix which is the result of running the operator
 * on the image.
 * @return
 */
Matrix blur(const Matrix &image)
{
    Matrix matrix(3, 3);
    matrix[0] = (float) 1 / 16, matrix[1] = (float) 2 / 16, matrix[2] = (float) 1 / 16;
    matrix[3] = (float) 2 / 16, matrix[4] = (float) 4 / 16, matrix[5] = (float) 2 / 16;
    matrix[6] = (float) 1 / 16, matrix[7] = (float) 2 / 16, matrix[8] = (float) 1 / 16;

    Matrix resMat(image.getRows(), image.getCols());
    resMat = convolution(image, matrix);
    resMat = normalizeMatrix(resMat);
    return resMat;
}

/**
 * Performs sobel edge detection on the input image.
 * Returns new matrix which is the result of running the
 * operator on the image.
 * @param image
 * @return
 */
Matrix sobel(const Matrix &image)
{
    Matrix matrixGx(3, 3);
    matrixGx[0] = (float) 1 / 8, matrixGx[1] = 0, matrixGx[2] = (float) -1 / 8;
    matrixGx[3] = (float) 2 / 8, matrixGx[4] = (float) 0 / 8, matrixGx[5] = (float) -2 / 8;
    matrixGx[6] = (float) 1 / 8, matrixGx[7] = 0, matrixGx[8] = (float) -1 / 8;

    Matrix matrixGy(3, 3);
    matrixGy[0] = (float) 1 / 8, matrixGy[1] = (float) 2 / 8, matrixGy[2] = (float) 1 / 8;
    matrixGy[3] = 0, matrixGy[4] = (float) 0 / 8, matrixGy[5] = 0;
    matrixGy[6] = (float) -1 / 8, matrixGy[7] = (float) -2 / 8, matrixGy[8] = (float) -1 / 8;

    Matrix resMat(image.getRows(), image.getCols());
    resMat = convolution(image, matrixGx) + convolution(image, matrixGy);
    resMat = normalizeMatrix(resMat);
    return resMat;
}
