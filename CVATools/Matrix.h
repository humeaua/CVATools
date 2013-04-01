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
#include <vector>
#include "Type.h"

class Matrix
{
public:
	Matrix(int N, int M);
    Matrix(std::size_t N, std::size_t M);
	Matrix(const Matrix& m);
	~Matrix();
    
    void Reallocate(int N, int M);
    
	double& operator ()(int i, int j);
	double& operator ()(int i, int j) const;
    
    double& operator ()(std::size_t i, std::size_t j);
	double& operator ()(std::size_t i, std::size_t j) const;
    
	int getrows() const;
	int getcols() const;
    
	void print();
    
protected:
	int rowsize;
	int colsize;
	double* data;
    
};

void addmatrix(Matrix& New, const Matrix& One, const Matrix& Two);
void transpose(Matrix& T, const Matrix& mat);
void multmatrix(Matrix& New1, const Matrix& one, const Matrix& two);
void mult(DVector & New, const Matrix & matrix, const DVector & Old);
void matrixinverse(Matrix& hi, const Matrix& mat);
void matrixLU(Matrix& L, Matrix& U, const Matrix& mat);

std::vector<std::vector<double> > CholeskiDecomposition(//  Input
                                                        const std::vector<std::vector<double> > & dMatrix);
void CholeskiDecomposition(//   Input
                           const Matrix & dMatrix,
                           //   Output
                           Matrix & dSquareRoot);

#endif