//
//  ArchimedeanCopula.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 04/08/13.
//
//

#include "ArchimedeanCopula.h"

namespace Maths
{
    ArchimedeanCopula::ArchimedeanCopula(CopulaType eCopulaType) : Copula(eCopulaType)
    {}
    
    double ArchimedeanCopula::CopulaFunction(const Utilities::MyVector<double> &dVariables) const
    {
        double dRes = 0;
        for (std::size_t i = 0 ; i < dVariables.size() ; ++i)
        {
            dRes += Generator(dVariables.at(i));
        }
        return GeneratorInverse(dRes);
    }
}