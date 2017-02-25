#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

/* Contructor */
Matrix::Matrix()
{

}
Matrix::Matrix(int n, int m)
{
    rows = n;
    cols = m;
}
Matrix::~Matrix()
{
}


/* Matrix Operation functions */
Matrix Matrix::add(Matrix &B) const
{
    Matrix A(rows,cols);
    if(rows == B.rows && cols == B.cols)
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                A.setValue(i,j, getValue(i,j)+B.getValue(i,j));
            }
        }
    }
        return A;
}

Matrix Matrix::subtract(Matrix &B) const
{
    Matrix A = B.multiply(-1);
    return add(A);
}
Matrix Matrix::multiply(Matrix &B) const
{
    Matrix P;
    if(cols == B.getRows())
    {
        P.setSize(rows, B.getCols());
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < B.getCols(); j++)
            {
               P.setValue(i,j, dot(B, i, j));
            }
        }
    }
    return P;
}

float Matrix::dot(Matrix &B, int row, int col)  const
/* Computes the dot product of one row of a matrix with the column of another */
{
    float sum = 0;

    for(int i = 0; i < cols; i++)
    {
            sum = sum + getValue(row,i)*B.getValue(i, col);
    }

    return sum;
}

Matrix Matrix::multiply(float c) const
/* Scalar multiplication */
{
    Matrix P;
    P.setSize(rows,cols);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            P.setValue(i,j, c*getValue(i,j));
        }
    }
    return P;
}
Matrix Matrix::inverse() const
{
    // only for square matrices with nonzero determinants
    if(rows > 2)
    {
        Matrix C = cofactor();
        Matrix T = C.transpose();
        return T.multiply(1/det());
    }
    else
    {
        Matrix B(rows,cols);
        B.setValue(0,0, getValue(1,1) / det());
        B.setValue(0,1, -getValue(1,0) / det());
        B.setValue(1,0, -getValue(1,0) / det());
        B.setValue(1,1, getValue(0,0) / det());
        return B;
    }
}
Matrix Matrix::cofactor() const
{
    // only for square matrices
    Matrix A(rows, cols);
    for( int i = 0; i < A.rows; i++)
    {
        for(int j = 0; j < A.cols; j++)
        {
            Matrix B = minor(i,j);

            if(((i%2) == 0 && (j%2 ==0) )|| (i==j))
            { A.setValue(i,j, B.det()); }
            else
            { A.setValue(i,j, -(B.det()));}
        }
    }

    cout << A << endl;
    return A;
}
Matrix Matrix::transpose() const
{
    // only for square matrices
    Matrix tran(rows,cols);
    for( int i = 0; i < tran.rows; i++)
    {
        for(int j = 0; j < tran.cols; j++)
        {
            tran.setValue(i,j, getValue(j,i));
        }
    }
    return tran;
}

float Matrix::det() const
{
//only for square matrices
float sum = 0;
    if(rows > 2)
    {
        for(int j = 0; j < cols; j++)
        {
            Matrix M = minor(0,j);
            if(j%2 == 0)
            {
                sum = sum + (getValue(0,j) * M.det());
            }
            else
            {
                sum = sum - (getValue(0,j) * M.det());
            }
        }
    }

    else
    {
        sum = sum + ((getValue(0,0) * getValue(1,1)) - (getValue(1,0) * getValue(0,1)));
    }

    return sum;

}
Matrix Matrix::minor(int i,int j) const
{
    Matrix min(rows-1,cols-1);

    for(int n = 0; n < min.getRows();n++)
    {
        for(int m = 0; m < min.getCols(); m++)
        {
            if(m >= j && n>=i)
                min.setValue(n,m, getValue(n+1,m+1));
            if (m >= j && n<i)
                    min.setValue(n,m, getValue(n, m+1));
            if(m < j && n>=i)
                min.setValue(n,m, getValue(n+1,m));
            if(n<i && m < j)
                min.setValue(n,m, getValue(n, m));
        }
    }
    return min;
}

ostream& operator<<(ostream &s, Matrix &c)
{
    for(int i = 0; i < c.getRows(); i ++)
    {
        for(int j = 0; j < c.getCols(); j++)
        {
          s << "  " << c.getValue(i,j);
        }
        s<<endl;
    }
    return s;
}
