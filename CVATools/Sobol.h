//
//  Sobol.h
//  MyNewLibrary
//
//  Created by Alexandre HUMEAU on 16/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MyNewLibrary_Sobol_h
#define MyNewLibrary_Sobol_h

//****************************************************************************80 
// 
//  Purpose: 
// 
//    I4_BIT_HI1 returns the position of the high 1 bit base 2 in an integer. 
// 
//  Example: 
// 
//       N    Binary    Hi 1 
//    ----    --------  ---- 
//       0           0     0  
//       1           1     1 
//       2          10     2 
//       3          11     2  
//       4         100     3 
//       5         101     3 
//       6         110     3 
//       7         111     3 
//       8        1000     4 
//       9        1001     4 
//      10        1010     4 
//      11        1011     4 
//      12        1100     4 
//      13        1101     4 
//      14        1110     4 
//      15        1111     4 
//      16       10000     5 
//      17       10001     5 
//    1023  1111111111    10 
//    1024 10000000000    11 
//    1025 10000000001    11 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    13 March 2003 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Parameters: 
// 
//    Input, int N, the integer to be measured. 
//    N should be nonnegative.  If N is nonpositive, I4_BIT_HI1 
//    will always be 0. 
// 
//    Output, int I4_BIT_HI1, the location of the high order bit. 
// 
int i4_bit_hi1 ( int n );

//****************************************************************************80 
// 
//  Purpose: 
// 
//    I4_BIT_LO0 returns the position of the low 0 bit base 2 in an integer. 
// 
//  Example: 
// 
//       N    Binary    Lo 0 
//    ----    --------  ---- 
//       0           0     1 
//       1           1     2 
//       2          10     1 
//       3          11     3  
//       4         100     1 
//       5         101     2 
//       6         110     1 
//       7         111     4 
//       8        1000     1 
//       9        1001     2 
//      10        1010     1 
//      11        1011     3 
//      12        1100     1 
//      13        1101     2 
//      14        1110     1 
//      15        1111     5 
//      16       10000     1 
//      17       10001     2 
//    1023  1111111111     1 
//    1024 10000000000     1 
//    1025 10000000001     1 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    13 March 2003 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Parameters: 
// 
//    Input, int N, the integer to be measured. 
//    N should be nonnegative. 
// 
//    Output, int I4_BIT_LO0, the position of the low 1 bit. 
// 
int i4_bit_lo0 ( int n );

void i4_sobol ( int dim_num, int *seed, float quasi[ ] ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    I4_SOBOL generates a new quasirandom Sobol vector with each call. 
// 
//  Discussion: 
// 
//    The routine adapts the ideas of Antonov and Saleev. 
// 
//    This routine uses INT for integers and FLOAT for real values. 
// 
//    Thanks to Steffan Berridge for supplying (twice) the properly 
//    formatted V data needed to extend the original routine's dimension 
//    limit from 40 to 1111, 05 June 2007. 
// 
//    Thanks to Francis Dalaudier for pointing out that the range of allowed 
//    values of DIM_NUM should start at 1, not 2!  17 February 2009. 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    17 February 2009 
// 
//  Author: 
// 
//    Original FORTRAN77 version by Bennett Fox. 
//    C++ version by John Burkardt 
// 
//  Reference: 
// 
//    IA Antonov, VM Saleev, 
//    An Economic Method of Computing LP Tau-Sequences, 
//    USSR Computational Mathematics and Mathematical Physics, 
//    Volume 19, 1980, pages 252 - 256. 
// 
//    Paul Bratley, Bennett Fox, 
//    Algorithm 659: 
//    Implementing Sobol's Quasirandom Sequence Generator, 
//    ACM Transactions on Mathematical Software, 
//    Volume 14, Number 1, pages 88-100, 1988. 
// 
//    Bennett Fox, 
//    Algorithm 647: 
//    Implementation and Relative Efficiency of Quasirandom  
//    Sequence Generators, 
//    ACM Transactions on Mathematical Software, 
//    Volume 12, Number 4, pages 362-376, 1986. 
// 
//    Stephen Joe, Frances Kuo 
//    Remark on Algorithm 659: 
//    Implementing Sobol's Quasirandom Sequence Generator, 
//    ACM Transactions on Mathematical Software, 
//    Volume 29, Number 1, pages 49-57, March 2003. 
// 
//    Ilya Sobol, 
//    USSR Computational Mathematics and Mathematical Physics, 
//    Volume 16, pages 236-242, 1977. 
// 
//    Ilya Sobol, YL Levitan,  
//    The Production of Points Uniformly Distributed in a Multidimensional  
//    Cube (in Russian), 
//    Preprint IPM Akad. Nauk SSSR,  
//    Number 40, Moscow 1976. 
// 
//  Parameters: 
// 
//    Input, int DIM_NUM, the number of spatial dimensions. 
//    DIM_NUM must satisfy 1 <= DIM_NUM <= 1111. 
// 
//    Input/output, int *SEED, the "seed" for the sequence. 
//    This is essentially the index in the sequence of the quasirandom 
//    value to be generated.  On output, SEED has been set to the 
//    appropriate next value, usually simply SEED+1. 
//    If SEED is less than 0 on input, it is treated as though it were 0. 
//    An input value of 0 requests the first (0-th) element of the sequence. 
// 
//    Output, float QUASI[DIM_NUM], the next quasirandom vector. 
// 

float *i4_sobol_generate ( int m, int n, int skip ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    I4_SOBOL_GENERATE generates a Sobol dataset. 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    12 December 2009 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Parameters: 
// 
//    Input, int M, the spatial dimension. 
// 
//    Input, int N, the number of points to generate. 
// 
//    Input, int SKIP, the number of initial points to skip. 
// 
//    Output, float I4_SOBOL_GENERATE[M*N], the points. 
// 

int i4_uniform ( int a, int b, int *seed ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    I4_UNIFORM returns a scaled pseudorandom I4. 
// 
//  Discussion: 
// 
//    The pseudorandom number should be uniformly distributed 
//    between A and B. 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    12 November 2006 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Reference: 
// 
//    Paul Bratley, Bennett Fox, Linus Schrage, 
//    A Guide to Simulation, 
//    Springer Verlag, pages 201-202, 1983. 
// 
//    Pierre L'Ecuyer, 
//    Random Number Generation, 
//    in Handbook of Simulation, 
//    edited by Jerry Banks, 
//    Wiley Interscience, page 95, 1998. 
// 
//    Bennett Fox, 
//    Algorithm 647: 
//    Implementation and Relative Efficiency of Quasirandom 
//    Sequence Generators, 
//    ACM Transactions on Mathematical Software, 
//    Volume 12, Number 4, pages 362-376, 1986. 
// 
//    Peter Lewis, Allen Goodman, James Miller 
//    A Pseudo-Random Number Generator for the System/360, 
//    IBM Systems Journal, 
//    Volume 8, pages 136-143, 1969. 
// 
//  Parameters: 
// 
//    Input, int A, B, the limits of the interval. 
// 
//    Input/output, int *SEED, the "seed" value, which should NOT be 0. 
//    On output, SEED has been updated. 
// 
//    Output, int I4_UNIFORM, a number between A and B. 
// 

int i8_bit_hi1 ( long long int n ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    I8_BIT_HI1 returns the position of the high 1 bit base 2 in an integer. 
// 
//  Example: 
// 
//       N    Binary    Hi 1 
//    ----    --------  ---- 
//       0           0     0 
//       1           1     1 
//       2          10     2 
//       3          11     2  
//       4         100     3 
//       5         101     3 
//       6         110     3 
//       7         111     3 
//       8        1000     4 
//       9        1001     4 
//      10        1010     4 
//      11        1011     4 
//      12        1100     4 
//      13        1101     4 
//      14        1110     4 
//      15        1111     4 
//      16       10000     5 
//      17       10001     5 
//    1023  1111111111    10 
//    1024 10000000000    11 
//    1025 10000000001    11 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    12 May 2007 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Parameters: 
// 
//    Input, long long int N, the integer to be measured. 
//    N should be nonnegative.  If N is nonpositive, I8_BIT_HI1 
//    will always be 0. 
// 
//    Output, int I8_BIT_HI1, the number of bits base 2. 
// 

int i8_bit_lo0 ( long long int n ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    I8_BIT_LO0 returns the position of the low 0 bit base 2 in an integer. 
// 
//  Example: 
// 
//       N    Binary    Lo 0 
//    ----    --------  ---- 
//       0           0     1 
//       1           1     2 
//       2          10     1 
//       3          11     3  
//       4         100     1 
//       5         101     2 
//       6         110     1 
//       7         111     4 
//       8        1000     1 
//       9        1001     2 
//      10        1010     1 
//      11        1011     3 
//      12        1100     1 
//      13        1101     2 
//      14        1110     1 
//      15        1111     5 
//      16       10000     1 
//      17       10001     2 
//    1023  1111111111     1 
//    1024 10000000000     1 
//    1025 10000000001     1 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    12 May 2007 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Parameters: 
// 
//    Input, long long int N, the integer to be measured. 
//    N should be nonnegative. 
// 
//    Output, int I8_BIT_LO0, the position of the low 1 bit. 
// 

void i8_sobol ( int dim_num, long long int *seed, double quasi[ ] ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    I8_SOBOL generates a new quasirandom Sobol vector with each call. 
// 
//  Discussion: 
// 
//    The routine adapts the ideas of Antonov and Saleev. 
// 
//    This routine uses LONG LONG INT for integers and DOUBLE for real values. 
// 
//    Thanks to Steffan Berridge for supplying (twice) the properly 
//    formatted V data needed to extend the original routine's dimension 
//    limit from 40 to 1111, 05 June 2007. 
// 
//    Thanks to Francis Dalaudier for pointing out that the range of allowed 
//    values of DIM_NUM should start at 1, not 2!  17 February 2009. 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    17 February 2009 
// 
//  Author: 
// 
//    FORTRAN77 original version by Bennett Fox. 
//    C++ version by John Burkardt 
// 
//  Reference: 
// 
//    IA Antonov, VM Saleev, 
//    An Economic Method of Computing LP Tau-Sequences, 
//    USSR Computational Mathematics and Mathematical Physics, 
//    Volume 19, 1980, pages 252 - 256. 
// 
//    Paul Bratley, Bennett Fox, 
//    Algorithm 659: 
//    Implementing Sobol's Quasirandom Sequence Generator, 
//    ACM Transactions on Mathematical Software, 
//    Volume 14, Number 1, pages 88-100, 1988. 
// 
//    Bennett Fox, 
//    Algorithm 647: 
//    Implementation and Relative Efficiency of Quasirandom  
//    Sequence Generators, 
//    ACM Transactions on Mathematical Software, 
//    Volume 12, Number 4, pages 362-376, 1986. 
// 
//    Stephen Joe, Frances Kuo 
//    Remark on Algorithm 659: 
//    Implementing Sobol's Quasirandom Sequence Generator, 
//    ACM Transactions on Mathematical Software, 
//    Volume 29, Number 1, pages 49-57, March 2003. 
// 
//    Ilya Sobol, 
//    USSR Computational Mathematics and Mathematical Physics, 
//    Volume 16, pages 236-242, 1977. 
// 
//    Ilya Sobol, YL Levitan,  
//    The Production of Points Uniformly Distributed in a Multidimensional  
//    Cube (in Russian), 
//    Preprint IPM Akad. Nauk SSSR,  
//    Number 40, Moscow 1976. 
// 
//  Parameters: 
// 
//    Input, int DIM_NUM, the number of spatial dimensions. 
//    DIM_NUM must satisfy 1 <= DIM_NUM <= 1111. 
// 
//    Input/output, long long int *SEED, the "seed" for the sequence. 
//    This is essentially the index in the sequence of the quasirandom 
//    value to be generated.  On output, SEED has been set to the 
//    appropriate next value, usually simply SEED+1. 
//    If SEED is less than 0 on input, it is treated as though it were 0. 
//    An input value of 0 requests the first (0-th) element of the sequence. 
// 
//    Output, double QUASI[DIM_NUM], the next quasirandom vector. 
// 

double *i8_sobol_generate ( int m, int n, int skip ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    I8_SOBOL_GENERATE generates a Sobol dataset. 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    12 December 2009 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Parameters: 
// 
//    Input, int M, the spatial dimension. 
// 
//    Input, int N, the number of points to generate. 
// 
//    Input, int SKIP, the number of initial points to skip. 
// 
//    Output, double I8_SOBOL_GENERATE[M*N], the points. 
//


float r4_abs ( float x ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    R4_ABS returns the absolute value of an R4. 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    01 December 2006 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Parameters: 
// 
//    Input, float X, the quantity whose absolute value is desired. 
// 
//    Output, float R4_ABS, the absolute value of X. 
// 

int r4_nint ( float x ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    R4_NINT returns the nearest integer to an R4. 
// 
//  Example: 
// 
//        X         R4_NINT 
// 
//      1.3         1 
//      1.4         1 
//      1.5         1 or 2 
//      1.6         2 
//      0.0         0 
//     -0.7        -1 
//     -1.1        -1 
//     -1.6        -2 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    14 November 2006 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Parameters: 
// 
//    Input, float X, the value. 
// 
//    Output, int R4_NINT, the nearest integer to X. 
// 

long long int i8_uniform ( long long int a, long long int b, int *seed ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    I8_UNIFORM returns a scaled pseudorandom I8. 
// 
//  Discussion: 
// 
//    The pseudorandom number should be uniformly distributed 
//    between A and B. 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    12 May 2007 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Reference: 
// 
//    Paul Bratley, Bennett Fox, Linus Schrage, 
//    A Guide to Simulation, 
//    Springer Verlag, pages 201-202, 1983. 
// 
//    Pierre L'Ecuyer, 
//    Random Number Generation, 
//    in Handbook of Simulation, 
//    edited by Jerry Banks, 
//    Wiley Interscience, page 95, 1998. 
// 
//    Bennett Fox, 
//    Algorithm 647: 
//    Implementation and Relative Efficiency of Quasirandom 
//    Sequence Generators, 
//    ACM Transactions on Mathematical Software, 
//    Volume 12, Number 4, pages 362-376, 1986. 
// 
//    Peter Lewis, Allen Goodman, James Miller 
//    A Pseudo-Random Number Generator for the System/360, 
//    IBM Systems Journal, 
//    Volume 8, pages 136-143, 1969. 
// 
//  Parameters: 
// 
//    Input, long long int A, B, the limits of the interval. 
// 
//    Input/output, int *SEED, the "seed" value, which should NOT be 0. 
//    On output, SEED has been updated. 
// 
//    Output, long long int I8_UNIFORM, a number between A and B. 
// 

float r4_uniform_01 ( int *seed ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    R4_UNIFORM_01 returns a unit pseudorandom R4. 
// 
//  Discussion: 
// 
//    This routine implements the recursion 
// 
//      seed = 16807 * seed mod ( 2**31 - 1 ) 
//      r4_uniform_01 = seed / ( 2**31 - 1 ) 
// 
//    The integer arithmetic never requires more than 32 bits, 
//    including a sign bit. 
// 
//    If the initial seed is 12345, then the first three computations are 
// 
//      Input     Output      R4_UNIFORM_01 
//      SEED      SEED 
// 
//         12345   207482415  0.096616 
//     207482415  1790989824  0.833995 
//    1790989824  2035175616  0.947702 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    16 November 2004 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Reference: 
// 
//    Paul Bratley, Bennett Fox, Linus Schrage, 
//    A Guide to Simulation, 
//    Springer Verlag, pages 201-202, 1983. 
// 
//    Pierre L'Ecuyer, 
//    Random Number Generation, 
//    in Handbook of Simulation 
//    edited by Jerry Banks, 
//    Wiley Interscience, page 95, 1998. 
// 
//    Bennett Fox, 
//    Algorithm 647: 
//    Implementation and Relative Efficiency of Quasirandom 
//    Sequence Generators, 
//    ACM Transactions on Mathematical Software, 
//    Volume 12, Number 4, pages 362-376, 1986. 
// 
//    Peter Lewis, Allen Goodman, James Miller, 
//    A Pseudo-Random Number Generator for the System/360, 
//    IBM Systems Journal, 
//    Volume 8, pages 136-143, 1969. 
// 
//  Parameters: 
// 
//    Input/output, int *SEED, the "seed" value.  Normally, this 
//    value should not be 0.  On output, SEED has been updated. 
// 
//    Output, float R4_UNIFORM_01, a new pseudorandom variate, strictly between 
//    0 and 1. 
// 

int r8_nint ( double x ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    R8_NINT returns the nearest integer to an R8. 
// 
//  Examples: 
// 
//        X         R8_NINT 
// 
//      1.3         1 
//      1.4         1 
//      1.5         1 or 2 
//      1.6         2 
//      0.0         0 
//     -0.7        -1 
//     -1.1        -1 
//     -1.6        -2 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    14 November 2006 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Parameters: 
// 
//    Input, double X, the value. 
// 
//    Output, int R8_NINT, the nearest integer to X. 
// 

double r8_uniform_01 ( int *seed ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    R8_UNIFORM_01 returns a unit pseudorandom R8. 
// 
//  Discussion: 
// 
//    This routine implements the recursion 
// 
//      seed = 16807 * seed mod ( 2**31 - 1 ) 
//      r8_uniform_01 = seed / ( 2**31 - 1 ) 
// 
//    The integer arithmetic never requires more than 32 bits, 
//    including a sign bit. 
// 
//    If the initial seed is 12345, then the first three computations are 
// 
//      Input     Output      R8_UNIFORM_01 
//      SEED      SEED 
// 
//         12345   207482415  0.096616 
//     207482415  1790989824  0.833995 
//    1790989824  2035175616  0.947702 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    11 August 2004 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Reference: 
// 
//    Paul Bratley, Bennett Fox, Linus Schrage, 
//    A Guide to Simulation, 
//    Springer Verlag, pages 201-202, 1983. 
// 
//    Pierre L'Ecuyer, 
//    Random Number Generation, 
//    in Handbook of Simulation 
//    edited by Jerry Banks, 
//    Wiley Interscience, page 95, 1998. 
// 
//    Bennett Fox, 
//    Algorithm 647: 
//    Implementation and Relative Efficiency of Quasirandom 
//    Sequence Generators, 
//    ACM Transactions on Mathematical Software, 
//    Volume 12, Number 4, pages 362-376, 1986. 
// 
//    Peter Lewis, Allen Goodman, James Miller, 
//    A Pseudo-Random Number Generator for the System/360, 
//    IBM Systems Journal, 
//    Volume 8, pages 136-143, 1969. 
// 
//  Parameters: 
// 
//    Input/output, int *SEED, the "seed" value.  Normally, this 
//    value should not be 0.  On output, SEED has been updated. 
// 
//    Output, double R8_UNIFORM_01, a new pseudorandom variate,  
//    strictly between 0 and 1. 
// 

void r8mat_write ( std::string output_filename, int m, int n, double table[] );

//****************************************************************************80 
// 
//  Purpose: 
// 
//    R8MAT_WRITE writes an R8MAT file. 
// 
//  Discussion: 
// 
//    An R8MAT is an array of R8's. 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    29 June 2009 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Parameters: 
// 
//    Input, string OUTPUT_FILENAME, the output filename. 
// 
//    Input, int M, the spatial dimension. 
// 
//    Input, int N, the number of points. 
// 
//    Input, double TABLE[M*N], the table data. 
// 

int tau_sobol ( int dim_num ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    TAU_SOBOL defines favorable starting seeds for Sobol sequences. 
// 
//  Discussion: 
// 
//    For spatial dimensions 1 through 13, this routine returns  
//    a "favorable" value TAU by which an appropriate starting point 
//    in the Sobol sequence can be determined. 
// 
//    These starting points have the form N = 2**K, where 
//    for integration problems, it is desirable that 
//      TAU + DIM_NUM - 1 <= K 
//    while for optimization problems, it is desirable that 
//      TAU < K. 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    12 December 2009 
// 
//  Author: 
// 
//    Original FORTRAN77 version by Bennett Fox. 
//    C++ version by John Burkardt. 
// 
//  Reference: 
// 
//    IA Antonov, VM Saleev, 
//    USSR Computational Mathematics and Mathematical Physics, 
//    Volume 19, 1980, pages 252 - 256. 
// 
//    Paul Bratley, Bennett Fox, 
//    Algorithm 659: 
//    Implementing Sobol's Quasirandom Sequence Generator, 
//    ACM Transactions on Mathematical Software, 
//    Volume 14, Number 1, pages 88-100, 1988. 
// 
//    Bennett Fox, 
//    Algorithm 647: 
//    Implementation and Relative Efficiency of Quasirandom  
//    Sequence Generators, 
//    ACM Transactions on Mathematical Software, 
//    Volume 12, Number 4, pages 362-376, 1986. 
// 
//    Stephen Joe, Frances Kuo 
//    Remark on Algorithm 659: 
//    Implementing Sobol's Quasirandom Sequence Generator, 
//    ACM Transactions on Mathematical Software, 
//    Volume 29, Number 1, pages 49-57, March 2003. 
// 
//    Ilya Sobol, 
//    USSR Computational Mathematics and Mathematical Physics, 
//    Volume 16, pages 236-242, 1977. 
// 
//    Ilya Sobol, YL Levitan,  
//    The Production of Points Uniformly Distributed in a Multidimensional  
//    Cube (in Russian), 
//    Preprint IPM Akad. Nauk SSSR,  
//    Number 40, Moscow 1976. 
// 
//  Parameters: 
// 
//    Input, int DIM_NUM, the spatial dimension.  Only values 
//    of 1 through 13 will result in useful responses. 
// 
//    Output, int TAU_SOBOL, the value TAU. 
// 

void timestamp ( ) ;

//****************************************************************************80 
// 
//  Purpose: 
// 
//    TIMESTAMP prints the current YMDHMS date as a time stamp. 
// 
//  Example: 
// 
//    May 31 2001 09:45:54 AM 
// 
//  Licensing: 
// 
//    This code is distributed under the GNU LGPL license.  
// 
//  Modified: 
// 
//    04 October 2003 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Parameters: 
// 
//    None 
// 



#endif
