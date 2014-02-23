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
#include "Vector.h"

namespace Utilities
{
    template<class T>
    class Matrix
    {
    public:
        Matrix(int N, int M)
        {
            m_rowsize = N;
            m_colsize = M;
            m_data.resize(m_rowsize*m_colsize, T());
        }
        
        Matrix(int N, int M, T& value)
        {
            m_rowsize = N;
            m_colsize = M;
            m_data.resize(m_rowsize*m_colsize, value);
        }
        
        Matrix(std::size_t N, std::size_t M)
        {
            m_rowsize = static_cast<int>(N);
            m_colsize = static_cast<int>(M);
            m_data.resize(m_rowsize*m_colsize, T());
        }
        
        Matrix(std::size_t N, std::size_t M,T& value)
        {
            m_rowsize = static_cast<int>(N);
            m_colsize = static_cast<int>(M);
            m_data.resize(m_rowsize*m_colsize, value);
        }
        
        Matrix(std::size_t N, bool bIsIdentity)
        {
            m_rowsize = static_cast<int>(N);
            m_colsize = static_cast<int>(N);
            m_data.resize(m_rowsize*m_colsize, T());
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
            m_rowsize = N;
            m_colsize = N;
            m_data.resize(m_rowsize*m_colsize, T());
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
            m_rowsize = m.m_rowsize;
            m_colsize = m.m_colsize;
            m_data.resize(m_rowsize*m_colsize);
            m_data = m.m_data;
        }
        
        template <size_t M>
        Matrix(T dData[][M], int N)
        {
            m_rowsize = N;
            m_colsize = M;
            m_data.resize(m_rowsize*m_colsize);
            for (std::size_t i = 0 ; i < m_rowsize; ++i)
            {
                for (std::size_t j = 0 ; j < m_colsize; ++j)
                {
                    (*this)(i,j) = dData[i][j];
                }
            }
        }
        
        Matrix(const std::vector<std::vector<T> > & data)
        {
            m_rowsize = data.size();
            m_colsize = data.front().size();
            for (std::size_t i = 0 ; i < m_rowsize; ++i)
            {
                for (std::size_t j = 0 ; j < m_colsize; ++j)
                {
                    (*this)(i,j) = data[i][j];
                }
            }
        }
        
        virtual void Reallocate(int N, int M)
        {
            m_data.clear();
            m_rowsize = N;
            m_colsize = M;
            m_data.resize(m_rowsize * m_colsize, T());
        }
        
        virtual void Reallocate(std::size_t N, std::size_t M)
        {
            m_data.clear();
            m_rowsize = static_cast<int>(N);
            m_colsize = static_cast<int>(M);
            m_data.resize(m_rowsize * m_colsize, T());
        }
        
        virtual T& operator ()(int i, int j)
        {
            return m_data.at(i + m_rowsize*j);
        }
        
        virtual T& operator ()(int i, int j) const
        {
            return (T&)m_data.at(i + m_rowsize*j);
        }
        
        virtual T& operator ()(std::size_t i, std::size_t j)
        {
            return m_data.at(i + m_rowsize*j);
        }
        
        virtual T& operator ()(std::size_t i, std::size_t j) const
        {
            return (T&)m_data.at(i + m_rowsize*j);
        }
                          
        virtual int getrows() const
        {
            return m_rowsize;
        }
        
        virtual int getcols() const
        {
            return m_colsize;
        }
        
        void print(std::ostream & os)
        {
            for (int i=0; i<m_rowsize; i++)
            {
                for (int j=0; j<m_colsize; j++)
                {
                    os << (*this)(i,j) << '\t';
                }
                os << std::endl;
            }
        }
        
    protected:
        int m_rowsize;
        int m_colsize;
        std::vector<T> m_data;
    };
    
    
    
    template<typename T>
    void addmatrix(Matrix<T>& New, const Matrix<T>& One, const Matrix<T>& Two)
    {
        for (int i=0;i<One.getrows();i++)
        {
            for (int j=0;j<One.getcols();j++)
            {
                New(i,j) = One(i,j) + Two(i,j);
            }
        }
    };
    
    template<typename T>
    void transpose(Matrix<T>& Transpose, const Matrix<T>& mat)
    {
        for (int i=0; i<mat.getcols(); i++)
        {
            for (int j=0; j<mat.getrows(); j++)
            {
                T(i,j) = mat(j,i);
            }
        }
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
    
    template<typename T>
    void mult(std::vector<T> & New, const Matrix<T> & matrix, const std::vector<T> & Old)
    {
        REQUIREEXCEPTION(matrix.getcols() == Old.size(), "Need same size in vector as in matrix number of rows");
        New.resize(matrix.getrows());
        
        for (int i = 0 ; i < matrix.getrows() ; ++i)
        {
            New.at(i) = 0.;
            for (int j = 0 ; j < matrix.getcols() ; ++j)
            {
                New.at(i) += matrix(i,j) * Old.at(j);
            }
        }
    };
    
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