//
//  Matrix.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 23/03/13.
//
//

#ifndef CVATools_Matrix_h
#define CVATools_Matrix_h

class Matrix
{
public:
	Matrix(int N, int M);
	Matrix(const Matrix& m);
	~Matrix();
    
	double& operator ()(int i, int j);
    
	double& operator ()(int i, int j) const;
    
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
void matrixinverse(Matrix& hi, const Matrix& mat);
void matrixLU(Matrix& L, Matrix& U, const Matrix& mat);

#endif