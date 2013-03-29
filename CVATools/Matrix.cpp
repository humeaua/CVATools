//
//  Matrix.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 23/03/13.
//
//

#include "Matrix.h"
#include <iostream>

Matrix::Matrix(int N, int M)
{
    rowsize = N;
    colsize = M;
    data=new double[rowsize*colsize];
}

Matrix::Matrix(std::size_t N, std::size_t M)
{
    rowsize = static_cast<int>(N);
    colsize = static_cast<int>(M);
    data=new double[rowsize*colsize];
}

Matrix::Matrix(const Matrix& m)
{
    rowsize = m.rowsize;
    colsize = m.colsize;
    data = new double[rowsize*colsize];
    memcpy(m.data, data, rowsize*colsize*sizeof(double));
}

Matrix::~Matrix()
{
    
    delete [] data; data=0;
}

double& Matrix::operator ()(int i, int j)
{
    return data[i + rowsize*j];
}

double& Matrix::operator ()(int i, int j) const
{
    return data[i + rowsize*j];
}

double& Matrix::operator ()(std::size_t i, std::size_t j)
{
    return data[i + rowsize*j];
}

double& Matrix::operator ()(std::size_t i, std::size_t j) const
{
    return data[i + rowsize*j];
}

int Matrix::getrows() const
{
    return rowsize;
}
int Matrix::getcols() const
{
    return colsize;
}

void Matrix::print()
{
    for (int i=0; i<rowsize; i++)
    {
        for (int j=0; j<colsize; j++)
        {
            std::cout << data[i+rowsize*j] << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << "rows: " << rowsize << "  cols: " << colsize << "  data: " << data << std::endl;
}

void addmatrix(Matrix& New, const Matrix& One, const Matrix& Two)
{
    for (int i=0;i<One.getrows();i++)
        for (int j=0;j<One.getcols();j++)
            New(i,j) = One(i,j) + Two(i,j);
}

void transpose(Matrix& T, const Matrix& mat)
{
    for (int i=0; i<mat.getcols(); i++)
        for (int j=0; j<mat.getrows(); j++)
            T(i,j) = mat(j,i);
}

void multmatrix(Matrix& New1, const Matrix& one, const Matrix& two)
{
    for (int i=0; i<one.getrows();i++)
    {
        for (int j=0; j<two.getcols();j++)
        {
            New1(i,j)=0;
            for (int k=0; k<one.getcols();k++)
            {
                New1(i,j) += one(i,k)*two(k,j);
            }
        }
    }
}

void matrixinverse(Matrix& hi, const Matrix& mat)
{
    double J[mat.getrows()][2*mat.getrows()];
    for (int i=0;i<mat.getrows();i++)
    {
        int j =0;
        while (j < mat.getcols())
        {
            J[i][j]=mat(i,j);
            j++;
        }
        while (j < 2*mat.getcols())
        {
            if (j == i+mat.getcols())
            {
                J[i][j] = 1;
                j++;
            }
            else
            {
                J[i][j] = 0;
                j++;
            }
            
        }
    }
    
    //gauss jordan
    for (int index=0;index < mat.getrows();index++)
    {
        if (J[index][index] == 0)
        {
            int gotit = 0;
            int check = index +1;
            
            while (gotit != 1)
            {
                if (J[check][check] != 0)
                {
                    double swit[2*mat.getcols()];
                    for (int colcount = 0; colcount < 2*mat.getcols();colcount++)
                    {
                        swit[colcount] = J[index][colcount];
                        J[index][colcount] = J[check][colcount];
                        J[check][colcount] = swit[colcount];
                    }
                    gotit = 1;
                }
                
                else
                {check++;}
            }
        }
        
        double beta = J[index][index];
        
        for (int j=index; j< 2*mat.getcols(); j++)
        {
            J[index][j] = J[index][j]/beta;
        }
        
        for (int k=0;k< mat.getrows();k++)
        {
            if (k != index)
            {
                double alpha = J[k][index];
                for (int l=index; l<2*mat.getcols();l++)
                {
                    J[k][l] += (-alpha)*(J[index][l]);
                }
            }
        }
    }
    
    for (int i=0;i<mat.getrows();i++)
    {
        for (int j=0;j<mat.getcols();j++)
        {
            hi(i,j) = J[i][mat.getcols()+ j];
        }
    }
}

void matrixLU(Matrix& L, Matrix& U, const Matrix& mat)
{
    double J[mat.getrows()][2*mat.getrows()];
    
    for (int i=0;i<mat.getrows();i++)
    {
        int j =0;
        while (j < mat.getcols())
        {
            J[i][j]=mat(i,j);
            j++;
        }
        while (j < 2*mat.getcols())
        {
            if (j == i+mat.getcols())
            {
                J[i][j] = 1;
                j++;
            }
            else
            {
                J[i][j] = 0;
                j++;
            }
            
        }
    }
    
    double LL[mat.getrows()][mat.getrows()];
    
    for(int i=0;i<mat.getrows();i++)
    {
        for(int j=0;j<mat.getcols();j++)
        {
            if (j == i)
                LL[i][j] = 1;
            else
                LL[i][j] = 0;
        }
    }
    
    for (int index=0;index < mat.getrows();index++)
    {
        
        for(int k = index+1;k<mat.getrows();k++)
        {
            double alpha = J[k][index]/J[index][index];
            for(int l = index;l<2*mat.getcols();l++)
            {
                J[k][l] += -alpha*J[index][l];
            }
            
            LL[k][index] = alpha;
            std::cout << alpha << std::endl;
        }
    }
    
    for (int i=0;i<mat.getrows();i++)
    {
        for (int j=0;j<mat.getcols();j++)
        {
            U(i,j) = J[i][j];
        }
    }
    
    for (int i=0;i<mat.getrows();i++)
    {
        for (int j=0;j<mat.getcols();j++)
        {
            L(i,j) = LL[i][j];
        }
    }
}
