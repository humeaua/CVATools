//
//  Matrix.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 23/03/13.
//
//

#include "Matrix.h"
#include <iostream>
#include <cmath>
#include <assert.h>

namespace Utilities
{
    Matrix::Matrix(int N, int M)
    {
        rowsize = N;
        colsize = M;
        data.resize(rowsize*colsize);
    }
    
    Matrix::Matrix(std::size_t N, std::size_t M)
    {
        rowsize = static_cast<int>(N);
        colsize = static_cast<int>(M);
        data.resize(rowsize*colsize);
    }
    
    Matrix::Matrix(const Matrix& m)
    {
        rowsize = m.rowsize;
        colsize = m.colsize;
        data.resize(rowsize*colsize);
        for (std::size_t i = 0 ; i < rowsize ; ++i)
        {
            for (std::size_t j = 0 ; j < colsize ; ++j)
            {
                data[i + j * rowsize] = m(i,j);
            }
        }
    }
    
    template <size_t M>
    Matrix::Matrix(double dData[][M], int N)
    {
        rowsize = N;
        colsize = M;
        data.resize(rowsize*colsize);
        for (std::size_t i = 0 ; i < rowsize; ++i)
        {
            for (std::size_t j = 0 ; j < colsize; ++j)
            {
                data[i + j * rowsize] = dData[i][j];
            }
        }
    }
    
    Matrix::~Matrix()
    {
        if (!data.empty())
            data.clear();
    }
    
    void Matrix::Reallocate(int N, int M)
    {
        data.clear();
        rowsize = N;
        colsize = M;
        data.resize(rowsize * colsize);
    }
    
    double& Matrix::operator ()(int i, int j)
    {
        return data[i + rowsize*j];
    }
    
    double& Matrix::operator ()(int i, int j) const
    {
        return (double&)data[i + rowsize*j];
    }
    
    double& Matrix::operator ()(std::size_t i, std::size_t j)
    {
        return data[i + rowsize*j];
    }
    
    double& Matrix::operator ()(std::size_t i, std::size_t j) const
    {
        return (double&)data[i + rowsize*j];
    }
    
    void Matrix::set(int i, int j, double value)
    {
        data[i + rowsize*j] = value;
    }
    
    void Matrix::set(std::size_t i, std::size_t j, double value)
    {
        data[i + rowsize*j] = value;
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
                double dValue = 0;
                for (int k=0; k<one.getcols();k++)
                {
                    dValue += one(i,k)*two(k,j);
                }
                New1(i,j) = dValue;
            }
        }
    }
    
    void mult(DVector & New, const Matrix & matrix, const DVector & Old)
    {
        assert(matrix.getcols() == Old.size());
        New.resize(matrix.getrows());
        
        for (int i = 0 ; i < matrix.getrows() ; ++i)
        {
            New[i] = 0.;
            for (int j = 0 ; j < matrix.getcols() ; ++j)
            {
                New[i] += matrix(i,j) * Old[j];
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
    
    std::vector<std::vector<double> > CholeskiDecomposition(//  Input
                                                            const std::vector<std::vector<double> > & dMatrix)
    {
        std::size_t iNRows = dMatrix.size();
        std::vector<std::vector<double> > L(iNRows, std::vector<double>(iNRows, 0.0));
        
        L[0][0] = sqrt(dMatrix[0][0]);
        for (std::size_t j = 1 ; j < iNRows ; ++j)
        {
            L[j][0] = dMatrix[j][0] / L[0][0];
        }
        for (std::size_t j = 1 ; j < iNRows ; ++j)
        {
            double dSum1 = 0;
            for (std::size_t k = 0 ; k < j ; ++k)
            {
                dSum1 += L[j][k] * L[j][k];
            }
            L[j][j] = sqrt(dMatrix[j][j] - dSum1);
            for (std::size_t i = j + 1 ; i < iNRows ; ++i)
            {
                double dSum2 = 0;
                for (std::size_t k = 0 ; k < j ; ++k)
                {
                    dSum2 += L[i][k] * L[j][k];
                }
                L[i][j] = (dMatrix[i][j] - dSum2) / L[j][j];
            }
        }
        return L;
    }
    
    void CholeskiDecomposition(//   Input
                               const Matrix & dMatrix,
                               //   Output
                               Matrix & dSquareRoot)
    {
        int iNRows = dMatrix.getrows();
        dSquareRoot.Reallocate(iNRows, iNRows);
        
        std::vector<std::vector<double> > L(iNRows, std::vector<double>(iNRows, 0.0));
        
        L[0][0] = sqrt(dMatrix(0,0));
        for (int j = 1 ; j < iNRows ; ++j)
        {
            L[j][0] = dMatrix(j,0) / L[0][0];
        }
        for (std::size_t j = 1 ; j < iNRows ; ++j)
        {
            double dSum1 = 0;
            for (std::size_t k = 0 ; k < j ; ++k)
            {
                dSum1 += L[j][k] * L[j][k];
            }
            L[j][j] = sqrt(dMatrix(j,j) - dSum1);
            for (std::size_t i = j + 1 ; i < iNRows ; ++i)
            {
                double dSum2 = 0;
                for (std::size_t k = 0 ; k < j ; ++k)
                {
                    dSum2 += L[i][k] * L[j][k];
                }
                L[i][j] = (dMatrix(i,j) - dSum2) / L[j][j];
            }
        }
        for (int i=0;i<iNRows;i++)
        {
            for (int j=0;j<iNRows;j++)
            {
                dSquareRoot(i,j) = L[i][j];
            }
        }
    }
}