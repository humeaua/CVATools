//
//  Copula.h
//  TP
//
//  Created by Alexandre HUMEAU on 10/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef TP_Copula_h
#define TP_Copula_h

#include "Vector.h"

namespace Maths {
    
    typedef enum
    {
        INDEPENDENT,
        CLAYTON,
        GUMBEL,
        FRANK,
        GAUSSIAN
    } CopulaType;
    
    class Copula
    {
    protected:
        CopulaType eCopulaType_;
    public:
        Copula(const CopulaType eCopulaType);
        
        virtual double CopulaFunction(const Utilities::MyVector<double> & dVariables) const = 0;
        
        virtual double KendallTau() const = 0;
    };
}

#endif
