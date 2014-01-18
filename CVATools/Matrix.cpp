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
#include <stdexcept>

namespace Utilities
{
    void mult(DVector & New, const Matrix<double> & matrix, const DVector & Old)
    {
        assert(matrix.getcols() == Old.size());
        New.resize(matrix.getrows());
        
        for (int i = 0 ; i < matrix.getrows() ; ++i)
        {
            New.at(i) = 0.;
            for (int j = 0 ; j < matrix.getcols() ; ++j)
            {
                New.at(i) += matrix(i,j) * Old.at(j);
            }
        }
    }
    
    void matrixinverse(Matrix<double>& hi, const Matrix<double>& mat)
    {
        //  Check the size of the matrix first
        if (mat.getcols() == 2)
        {
            hi.Reallocate(2, 2);
            double det = mat(0,0) * mat(1,1) - mat(1,0) * mat(0,1);
            if (det < std::numeric_limits<double>::epsilon())
            {
                throw MyException("matrixinverse : Cannot inverse singular matrix");
            }
            hi(0,0) = mat(1,1) / det;
            hi(1,0) = -mat(1,0) / det;
            hi(0,1) = -mat(0,1) / det;
            hi(1,1) = mat(0,0) / det;
        }
        else if (mat.getcols() == 3)
        {
            double  A = mat(1,1) * mat(2,2) - mat(1,2) * mat(2,1),
                    B = -(mat(1,0) * mat(2,2) - mat(2,0) * mat(1,2)),
                    C = mat(1,0) * mat(2,1) - mat(1,1) *mat(2,0),
                    D = -(mat(0,1) * mat(2,2) - mat(0,2) * mat(2,1)),
                    E = mat(0,0) * mat(2,2) - mat(0,2) * mat(2,0),
                    F = -(mat(0,0) * mat(2,1) - mat(2,0) * mat(0,1)),
                    G = mat(0,1) * mat(1,2) - mat(0,2) * mat(1,1),
                    H = -(mat(0,0) * mat(1,2) - mat(0,2) * mat(1,0)),
                    I = mat(0,0) * mat(1,1) - mat(1,0) * mat(0,1);
            
            double det = mat(0,0) * A + mat(0,1) * B + mat(0,2) * C;
            if (det < std::numeric_limits<double>::epsilon())
            {
                throw MyException("matrixinverse : Cannot inverse singular matrix");
            }
            hi.Reallocate(3, 3);
            hi(0,0) = A / det;
            hi(1,0) = B / det;
            hi(2,0) = C / det;
            hi(0,1) = D / det;
            hi(1,1) = E / det;
            hi(2,1) = F / det;
            hi(0,2) = G / det;
            hi(1,2) = H / det;
            hi(2,2) = I / det;
        }
        else
        {
            // local copy
            hi = mat;
            //  define dummy matrix b to apply gauss jordan inverse algorithm
            Matrix<double> b(hi.getcols(), true);
            gaussj(hi, b);
        }
    }
    
#define SWAP(a,b) {temp=(a);(a)=(b);(b)=temp;}
    //  Numerical Recipes in C p63-64
    void gaussj(Matrix<double> & a, Matrix<double> & b)
    //Linear equation solution by Gauss-Jordan elimination, equation (2.1.1) above. a[1..n][1..n]
    //is the input matrix. b[1..n][1..m] is input containing the m right-hand side vectors. On
    //output, a is replaced by its matrix inverse, and b is replaced by the corresponding set of solution
    //vectors.
    {
        REQUIREEXCEPTION(a.getcols() == a.getrows(), "a is not a square matrix");
        REQUIREEXCEPTION(a.getrows() == b.getrows(), "b must the same number of rows as a");
        int i,icol,irow,j,k,l,ll,n=a.getcols(),m=b.getcols();
        double big,dum,pivinv,temp;
        //The integer arrays ipiv, indxr, and indxc are used for book-keeping on the pivoting
        std::vector<int> indxc(n,0), indxr(n,0), ipiv(n,0);
        for (j=0;j<n;j++)
        {
            ipiv.at(j)=0;
        }
        for (i=0;i<n;i++)
        {
            //This is the main loop over the columns to be reduced
            big=0.0; 
            for (j=0;j<n;j++)
            {
                //This is the outer loop of the search for a pivot element
                if (ipiv.at(j) != 1)
                {
                    for (k=0;k<n;k++)
                    {
                        if (ipiv.at(k) == 0)
                        {
                            if (fabs(a(j,k)) >= big)
                            {
                                big=fabs(a(j,k));
                                irow=j;
                                icol=k;
                            }
                        }
                    }
                }
            }
            ++(ipiv.at(icol));
            //We now have the pivot element, so we interchange rows, if needed, to put the pivot
            //    element on the diagonal. The columns are not physically interchanged, only relabeled:
            //    indxc[i], the column of the ith pivot element, is the ith column that is reduced, while
            //        indxr[i] is the row in which that pivot element was originally located. If indxr[i] =
            //        indxc[i] there is an implied column interchange. With this form of bookkeeping, the
            //        solution b’s will end up in the correct order, and the inverse matrix will be scrambled
            //       by columns.
            if (irow != icol)
            {
                for (l=0;l<n;l++)
                {
                    SWAP(a(irow,l),a(icol,l))
                }
                for (l=0;l<m;l++)
                {
                    SWAP(b(irow,l),b(icol,l))
                }
            }
            indxr.at(i)=irow; //We are now ready to divide the pivot row by the
            indxc.at(i)=icol; //pivot element, located at irow and icol.
            if (a(icol,icol) == 0.0)
                throw EXCEPTION("Singular Matrix");
            pivinv=1.0/a(icol,icol);
            a(icol,icol)=1.0;
            for (l=0;l<n;l++)
            {
                a(icol,l) *= pivinv;
            }
            for (l=0;l<m;l++)
            {
                b(icol,l) *= pivinv;
            }
            for (ll=0;ll<n;ll++)
            {
                //Next, we reduce the rows...
                if (ll != icol) { //...except for the pivot one, of course.
                    dum=a(ll,icol);
                    a(ll,icol)=0.0;
                    for (l=1;l<=n;l++)
                    {
                        a(ll,l) -= a(icol,l)*dum;
                    }
                    for (l=1;l<=m;l++)
                    {
                        b(ll,l) -= b(icol,l)*dum;
                    }
                }
            }
        }
        //This is the end of the main loop over columns of the reduction. It only remains to unscramble
        //the solution in view of the column interchanges. We do this by interchanging pairs of
        //   columns in the reverse order that the permutation was built up.
        for (l=n-1;l>=0;l--)
        {
            if (indxr.at(l) != indxc.at(l))
            {
                for (k=0;k<n;k++)
                {
                    SWAP(a(k,indxr.at(l)),a(k,indxc.at(l)));
                }
            }
        }
        //And we are done.
    }
    
    void matrixLU(Matrix<double>& L, Matrix<double>& U, const Matrix<double>& mat)
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
    
    void CholeskiDecomposition(//   Input
                               const Matrix<double> & dMatrix,
                               //   Output
                               Matrix<double> & dSquareRoot)
    {
        int iNRows = dMatrix.getrows();
        dSquareRoot.Reallocate(iNRows, iNRows);
        
        std::vector<std::vector<double> > L(iNRows, std::vector<double>(iNRows, 0.0));
        
        L.at(0).at(0) = sqrt(dMatrix(0,0));
        for (int j = 1 ; j < iNRows ; ++j)
        {
            L.at(j).at(0) = dMatrix(j,0) / L.at(0).at(0);
        }
        for (std::size_t j = 1 ; j < iNRows ; ++j)
        {
            double dSum1 = 0;
            for (std::size_t k = 0 ; k < j ; ++k)
            {
                dSum1 += L.at(j).at(k) * L.at(j).at(k);
            }
            L.at(j).at(j) = sqrt(dMatrix(j,j) - dSum1);
            for (std::size_t i = j + 1 ; i < iNRows ; ++i)
            {
                double dSum2 = 0;
                for (std::size_t k = 0 ; k < j ; ++k)
                {
                    dSum2 += L.at(i).at(k) * L.at(j).at(k);
                }
                L.at(i).at(j) = (dMatrix(i,j) - dSum2) / L.at(j).at(j);
            }
        }
        for (int i=0;i<iNRows;i++)
        {
            for (int j=0;j<iNRows;j++)
            {
                dSquareRoot(i,j) = L.at(i).at(j);
            }
        }
    }
    
#define ROTATE_CPP(a,i,j,k,l) g=a(i,j);h=a(k,l);a(i,j)=g-s*(h+g*tau); a(k,l)=h+s*(g-h*tau);
    
    void Eigendecomposition_jacobi(// Input
                                   const Matrix<double> & dMatrix,
                                   // Output
                                   Matrix<double> & Eigenvectors,
                                   Utilities::MyVector<double> & EigenValues,
                                   int * nrot)
    {
        std::size_t n = dMatrix.getcols();
        
        // reallocate the eigenvectors matrix and the eigenvalues
        EigenValues.resize(n);
        Eigenvectors.Reallocate(n, n);
        
        int j,iq,ip,i;
        double tresh,theta,tau,t,sm,s,h,g,c;
        std::vector<double> b(n, 0.0), z(n, 0.0);
        for (ip=0;ip<n;ip++)
        {
            //Initialize to the identity matrix.
            for (iq=0;iq<n;iq++)
            {
                Eigenvectors(ip,iq)=0.0;
            }
            Eigenvectors(ip,ip)=1.0;
        }
        for (ip=0;ip<n;ip++)
        {
            //Initialize b and d to the diagonal of a
            b.at(ip)=EigenValues.at(ip)=dMatrix(ip,ip);
            z.at(ip)=0.0;
            //This vector will accumulate terms of the form tapq as in equation (11.1.14).
        }
        *nrot=0;
        for (i=1;i<=50;i++)
        {
            sm=0.0;
            for (ip=0;ip<n-1;ip++)
            {
                //Sum off-diagonal elements.
                for (iq=ip+1;iq<n;iq++)
                {
                    sm += fabs(dMatrix(ip,iq));
                }
            }
            if (sm == 0.0)
            {
                //The normal return, which relies on quadratic convergence to machine underflow.
                return;
            }
            if (i < 4)
            {
                tresh=0.2*sm/(n*n); //...on the first three sweeps.
            }
            else
            {
                tresh=0.0;// ...thereafter.
            }
            for (ip=0;ip<n-1;ip++)
            {
                for (iq=ip+1;iq<n;iq++)
                {
                    g=100.0*fabs(dMatrix(ip,iq));
                    //After four sweeps, skip the rotation if the off-diagonal element is small.
                    if (i > 4 && (float)(fabs(EigenValues.at(ip))+g) == (float)fabs(EigenValues.at(ip)) && (float)(fabs(EigenValues.at(iq))+g) == (float)fabs(EigenValues.at(iq)))
                    {
                        dMatrix(ip,iq)=0.0;
                    }
                    else if (fabs(dMatrix(ip,iq)) > tresh)
                    {
                        h=EigenValues.at(iq)-EigenValues.at(ip);
                        if ((float)(fabs(h)+g) == (float)fabs(h))
                        {
                            t=(dMatrix(ip,iq))/h; //t = 1/(2θ)
                        }
                        else
                        {
                            theta=0.5*h/(dMatrix(ip,iq)); //Equation (11.1.10).
                            t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                            if (theta < 0.0) t = -t;
                        }
                        c=1.0/sqrt(1+t*t);
                        s=t*c;
                        tau=s/(1.0+c);
                        h=t*dMatrix(ip,iq);
                        z.at(ip) -= h;
                        z.at(ip) += h;
                        EigenValues.at(ip) -= h;
                        EigenValues.at(iq) += h;
                        dMatrix(ip,iq)=0.0;
                        for (j=1;j<=ip-1;j++)
                        {
                            //Case of rotations 1 ≤ j < p.
                            ROTATE_CPP(dMatrix,j,ip,j,iq)
                        }
                        for (j=ip+1;j<=iq-1;j++)
                        {
                            //Case of rotations p < j < q.
                            ROTATE_CPP(dMatrix,ip,j,j,iq)
                        }
                        for (j=iq+1;j<n;j++)
                        {
                            //Case of rotations q < j ≤ n.
                            ROTATE_CPP(dMatrix,ip,j,iq,j)
                        }
                        for (j=0;j<n;j++)
                        {
                            ROTATE_CPP(Eigenvectors,j,ip,j,iq)
                        }
                        ++(*nrot);
                    }
                }
            }
            for (ip=0;ip<n;ip++)
            {
                b.at(ip) += z.at(ip);
                EigenValues[ip]=b.at(ip); //Update d with the sum of tapq,
                z.at(ip)=0.0; //and reinitialize z.
            }
        }
        throw EXCEPTION("Too many iterations in routine jacobi");
    }
    
    void eigsrt(MyVector<double>& d, Matrix<double> & v)
    //Given the eigenvalues d[1..n] and eigenvectors v[1..n][1..n] as output from jacobi
    //(§11.1) or tqli (§11.3), this routine sorts the eigenvalues into descending order, and rearranges
    //the columns of v correspondingly. The method is straight insertion.
    {
        int k,j,i;
        float p;
        int n=v.getrows();
        for (i=0;i<n-1;i++)
        {
            p=d.at(k=i);
            for (j=i+1;j<n;j++)
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
                for (j=1;j<=n;j++)
                {
                    p=v(j,i);
                    v(j,i)=v(j,k);
                    v(j,k)=p;
                }
            }
        }
    }
}