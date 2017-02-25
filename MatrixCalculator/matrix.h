#ifndef MATRIX_H
#define MATRIX_H
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#define MAXROWS 100
#define MAXCOLS 100

using namespace std;
class Matrix
{
    public:
    /* Contructor */
    Matrix();
    Matrix(int n, int m);
    ~Matrix();

    /* Accessor functions */
    inline void setSize(int n, int m)
    {
        rows = n;
        cols = m;
    }
    inline int getRows() const
    {
        return rows;
    }
    inline int getCols() const
    {
        return cols;
    }
    inline float getValue(int n, int m) const
    {
        return M[n][m];
    }
    inline void setValue(int n, int m, float x)
    {
        M[n][m] = x;
    }

    /* Matrix Operation functions */
    Matrix add(Matrix &B) const;
    Matrix subtract(Matrix &B) const;
    Matrix multiply(Matrix &B) const;
    Matrix multiply(float c) const; /* Scalar multiplication */
    Matrix inverse() const;
    Matrix cofactor() const; //used for inverse
    Matrix transpose() const; // used for inverse
    float dot(Matrix &B, int row, int col) const;
    float det() const; /* determinant */
    Matrix minor(int i,int j) const; /* used in determinant */

    friend ostream& operator<<(ostream &s, Matrix &c);

private:
    int rows;
    int cols;
    float M[MAXROWS][MAXCOLS];
};

#endif // MATRIX_H
