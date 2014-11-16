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
#include "Exception.h"

namespace Utilities
{
    template<class T>
    class Matrix
    {
    public:
        Matrix();
        Matrix(std::size_t N, std::size_t M, const T& value = T());
        
        template <size_t M>
        Matrix(T dData[][M], int N);
        
        Matrix(const std::vector<std::vector<T> > & data);
        
        virtual void Reallocate(std::size_t N, std::size_t M);
        
        virtual const T& operator ()(std::size_t row_index, std::size_t column_index) const;
        virtual T& operator ()(std::size_t row_index, std::size_t column_index);
        
        virtual size_t getrows() const;
        virtual size_t getcols() const;
        std::ostream & print(std::ostream & os);
        
        class row;
        const row & operator[](size_t index) const;
        row & operator[](size_t index);
        
        virtual const std::vector<T> & data() const;
        
    private:
        size_t m_rowsize;
        size_t m_colsize;
        std::vector<T> m_data;
        
        void CheckIndexes(size_t row_index, size_t col_index) const;
    };
    
    template<typename T>
    class Matrix<T>::row
    {
    public:
        row(double * data, size_t colsize);
        T & operator[](size_t column_index);
        const T& operator[](size_t column_index) const;
    private:
        double * m_data;
        size_t m_colsize;
    };
    
    template<typename T>
    Matrix<T>::Matrix() : m_rowsize(0), m_colsize(0), m_data(0)
    {}
    
    template<typename T>
    Matrix<T>::Matrix(std::size_t N, std::size_t M,const T& value)
    {
        m_rowsize = N;
        m_colsize = M;
        m_data.resize(m_rowsize*m_colsize, value);
    }
    
    template<typename T>
    template<size_t M>
    Matrix<T>::Matrix(T dData[][M], int N)
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
    
    template<typename T>
    Matrix<T>::Matrix(const std::vector<std::vector<T> > & data)
    {
        m_rowsize = data.size();
        m_colsize = data.front().size();
        m_data.resize(m_colsize * m_rowsize);
        for (std::size_t i = 0 ; i < m_rowsize; ++i)
        {
            for (std::size_t j = 0 ; j < m_colsize; ++j)
            {
                (*this)(i,j) = data[i][j];
            }
        }
    }
    
    template<typename T>
    void Matrix<T>::Reallocate(std::size_t N, std::size_t M)
    {
        m_data.clear();
        m_rowsize = N;
        m_colsize = M;
        m_data.resize(m_rowsize * m_colsize, T());
    }
    
    template<typename T>
    void Matrix<T>::CheckIndexes(size_t row_index, size_t column_index) const
    {
        if (static_cast<int>(column_index) < 0)
        {
            throw EXCEPTION("Index is negative");
        }
        if (column_index > m_colsize)
        {
            throw EXCEPTION("column index out of range");
        }
        if (static_cast<int>(row_index) < 0)
        {
            throw EXCEPTION("Index is negative");
        }
        if (row_index > m_rowsize)
        {
            throw EXCEPTION("column index out of range");
        }
    }
    
    template<typename T>
    T& Matrix<T>::operator ()(std::size_t row_index, std::size_t column_index)
    {
        CheckIndexes(row_index, column_index);
        return m_data.at(row_index + m_rowsize * column_index);
    }
    
    template<typename T>
    const T& Matrix<T>::operator ()(std::size_t row_index, std::size_t column_index) const
    {
        CheckIndexes(row_index, column_index);
        return m_data.at(row_index + m_rowsize * column_index);
    }
    
    template<typename T>
    size_t Matrix<T>::getrows() const
    {
        return m_rowsize;
    }
    
    template<typename T>
    size_t Matrix<T>::getcols() const
    {
        return m_colsize;
    }
    
    template<typename T>
    std::ostream & Matrix<T>::print(std::ostream & os)
    {
        for (int i=0; i<m_rowsize; i++)
        {
            for (int j=0; j<m_colsize; j++)
            {
                os << (*this)(i,j) << '\t';
            }
            os << std::endl;
        }
        return os;
    }
    
    template<typename T>
    const std::vector<T> & Matrix<T>::data() const
    {
        return m_data;
    }
    
    template<typename T>
    const typename Matrix<T>::row & Matrix<T>::operator[](size_t index) const
    {
        if (static_cast<int>(index) < 0)
        {
            throw EXCEPTION("Index is negative");
        }
        if (index > m_rowsize)
        {
            throw EXCEPTION("column index out of range");
        }
        return Matrix<T>::row(&m_data[index * m_rowsize],m_colsize);
    }
    
    template<typename T>
    typename Matrix<T>::row & Matrix<T>::operator[](size_t index)
    {
        if (static_cast<int>(index) < 0)
        {
            throw EXCEPTION("Index is negative");
        }
        if (index > m_rowsize)
        {
            throw EXCEPTION("column index out of range");
        }
        //  local static to avoid warning
        static Matrix<T>::row row(&m_data[index * m_rowsize],m_colsize);
        return row;
    }
    
    template<typename T>
    Matrix<T>::row::row(double * data, size_t colsize) : m_data(data), m_colsize(colsize)
    {}
    
    template<typename T>
    const T & Matrix<T>::row::operator[](size_t column_index) const
    {
        if (static_cast<int>(column_index) < 0)
        {
            throw EXCEPTION("Index is negative");
        }
        if (column_index > m_colsize)
        {
            throw EXCEPTION("column index out of range");
        }
        return m_data[column_index];
    }
    
    template<typename T>
    T & Matrix<T>::row::operator[](size_t column_index)
    {
        if (static_cast<int>(column_index) < 0)
        {
            throw EXCEPTION("Index is negative");
        }
        if (column_index > m_colsize)
        {
            throw EXCEPTION("column index out of range");
        }
        return m_data[column_index];
    }

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
    
    template<class T>
    void eigsrt(MyVector<T>& d, Matrix<T> & v)
    //Given the eigenvalues d[1..n] and eigenvectors v[1..n][1..n] as output from jacobi
    //(§11.1) or tqli (§11.3), this routine sorts the eigenvalues into descending order, and rearranges
    //the columns of v correspondingly. The method is straight insertion.
    {
        const size_t n=v.getrows();
        size_t k;
        for (size_t i=0;i<n-1;i++)
        {
            T p=d.at(k=i);
            for (size_t j=i+1;j<n;j++)
            {
                if (d.at(j) >= p)
                {
                    p=d.at(k=j);
                }
            }
            if (k != i)
            {
                d.at(k)=d.at(i);
                d.at(i)=p;
                for (size_t j=0;j<n;j++)
                {
                    std::swap(v(j,i),v(j,k));
                }
            }
        }
    }
}
#endif