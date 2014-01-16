//
//  Matrix.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 23/03/13.
//
//

#ifndef CVATools_Matrix_h
#define CVATools_Matrix_h

#include <iostream>
#include "Type.h"
#include "Vector.h"

namespace Utilities
{
    template<class T>
    class Matrix
    {
    public:
        Matrix(int N, int M)
        {
            rowsize = N;
            colsize = M;
            data.resize(rowsize*colsize, T());
        }
        
        Matrix(int N, int M, T& value)
        {
            rowsize = N;
            colsize = M;
            data.resize(rowsize*colsize, value);
        }
        
        Matrix(std::size_t N, std::size_t M)
        {
            rowsize = static_cast<int>(N);
            colsize = static_cast<int>(M);
            data.resize(rowsize*colsize, T());
        }
        
        Matrix(std::size_t N, std::size_t M,T& value)
        {
            rowsize = static_cast<int>(N);
            colsize = static_cast<int>(M);
            data.resize(rowsize*colsize, value);
        }
        
        Matrix(std::size_t N, bool bIsIdentity)
        {
            rowsize = static_cast<int>(N);
            colsize = static_cast<int>(N);
            data.resize(rowsize*colsize, T());
            if (bIsIdentity)
            {
                for (std::size_t i = 0 ; i < N ; ++i)
                {
                    (*this)(i,i) = 1.0;
                }
            }
        }
        
        Matrix(int N, bool bIsIdentity)
        {
            rowsize = N;
            colsize = N;
            data.resize(rowsize*colsize, T());
            if (bIsIdentity)
            {
                for (std::size_t i = 0 ; i < N ; ++i)
                {
                    (*this)(i,i) = 1.0;
                }
            }
        }
        
        Matrix(const Matrix& m)
        {
            rowsize = m.rowsize;
            colsize = m.colsize;
            data.resize(rowsize*colsize);
            data = m.data;
        }
        
        template <size_t M>
        Matrix(T dData[][M], int N)
        {
            rowsize = N;
            colsize = M;
            data.resize(rowsize*colsize);
            for (std::size_t i = 0 ; i < rowsize; ++i)
            {
                for (std::size_t j = 0 ; j < colsize; ++j)
                {
                    (*this)(i,j) = dData[i][j];
                }
            }
        }
        
        virtual void Reallocate(int N, int M)
        {
            data.clear();
            rowsize = N;
            colsize = M;
            data.resize(rowsize * colsize, T());
        }
        
        virtual void Reallocate(std::size_t N, std::size_t M)
        {
            data.clear();
            rowsize = static_cast<int>(N);
            colsize = static_cast<int>(M);
            data.resize(rowsize * colsize, T());
        }
        
        virtual T& operator ()(int i, int j)
        {
            return data.at(i + rowsize*j);
        }
        
        virtual T& operator ()(int i, int j) const
        {
            return (T&)data.at(i + rowsize*j);
        }
        
        virtual T& operator ()(std::size_t i, std::size_t j)
        {
            return data.at(i + rowsize*j);
        }
        
        virtual T& operator ()(std::size_t i, std::size_t j) const
        {
            return (T&)data.at(i + rowsize*j);
        }
        
        virtual int getrows() const
        {
            return rowsize;
        }
        
        virtual int getcols() const
        {
            return colsize;
        }
        
        void print()
        {
            for (int i=0; i<rowsize; i++)
            {
                for (int j=0; j<colsize; j++)
                {
                    std::cout << (*this)(i,j) << '\t';
                }
                std::cout << std::endl;
            }
        }
        
    protected:
        int rowsize;
        int colsize;
        std::vector<T> data;
        
    };
    
    template<typename T>
    void addmatrix(Matrix<T>& New, const Matrix<T>& One, const Matrix<T>& Two)
    {
        for (int i=0;i<One.getrows();i++)
            for (int j=0;j<One.getcols();j++)
                New(i,j) = One(i,j) + Two(i,j);
    };
    
    template<typename T>
    void transpose(Matrix<T>& Transpose, const Matrix<T>& mat)
    {
        for (int i=0; i<mat.getcols(); i++)
            for (int j=0; j<mat.getrows(); j++)
                T(i,j) = mat(j,i);
    };
    
    template<typename T>
    void multmatrix(Matrix<T>& New1, const Matrix<T>& one, const Matrix<T>& two)
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
    };
    
    void mult(DVector & New, const Matrix<double> & matrix, const DVector & Old);
    void matrixinverse(Matrix<double> & hi, const Matrix<double> & mat);
    void gaussj(Matrix<double> & a, Matrix<double> & b);
    
    void matrixLU(Matrix<double>& L, Matrix<double>& U, const Matrix<double>& mat);
    
    void CholeskiDecomposition(//   Input
                               const Matrix<double> & dMatrix,
                               //   Output
                               Matrix<double> & dSquareRoot);
    
    void Eigendecomposition_jacobi(// Input
                                   const Matrix<double> & dMatrix,
                                   // Output
                                   Matrix<double> & Eigenvectors,
                                   Utilities::MyVector<double> & EigenValues,
                                   int * nrot);
    
    void eigsrt(MyVector<double>& d, Matrix<double> & v);
}
#endif