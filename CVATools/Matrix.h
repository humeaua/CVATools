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
    class Matrix
    {
    public:
        Matrix(int N, int M);
        Matrix(std::size_t N, std::size_t M);
        Matrix(const Matrix& m);
        template <size_t M>
        Matrix(double dData[][M], int N);
        virtual ~Matrix();
        
        void Reallocate(int N, int M);
        void Reallocate(std::size_t N, std::size_t M);
        
        double& operator ()(int i, int j);
        double& operator ()(int i, int j) const;
        
        double& operator ()(std::size_t i, std::size_t j);
        double& operator ()(std::size_t i, std::size_t j) const;
        
        virtual void set(int i, int j, double value);
        virtual void set(std::size_t i, std::size_t j, double value);
        
        virtual int getrows() const;
        virtual int getcols() const;
        
        void print();
        
    protected:
        int rowsize;
        int colsize;
        //double* data;
        std::vector<double> data;
        
    };
    
    void addmatrix(Matrix& New, const Matrix& One, const Matrix& Two);
    void transpose(Matrix& T, const Matrix& mat);
    void multmatrix(Matrix& New1, const Matrix& one, const Matrix& two);
    void mult(DVector & New, const Matrix & matrix, const DVector & Old);
    void matrixinverse(Matrix& hi, const Matrix& mat);
    void matrixLU(Matrix& L, Matrix& U, const Matrix& mat);
    
    void CholeskiDecomposition(//   Input
                               const Matrix & dMatrix,
                               //   Output
                               Matrix & dSquareRoot);
    
    void Eigendecomposition_jacobi(// Input
                                   const Matrix & dMatrix,
                                   // Output
                                   Matrix & Eigenvectors,
                                   Utilities::MyVector<double> & EigenValues,
                                   int * nrot);
}
#endif