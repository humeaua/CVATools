//
//  OfficialWorldGolfRankings.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 13/10/13.
//
//

#include "OfficialWorldGolfRankings.h"
#include <vector>
#include "Exception.h"

namespace Golf
{
    Utilities::Interp::InterExtrapolation1D OfficialWorldGolfRankings::GetOWGRDiscountCurve() const
    {
        std::vector<double> dVariables(4), dValues(4);
        dVariables.at(0) = -2.01;
        dValues.at(0) = 0.0;
        dVariables.at(1) = -2.0;
        dValues.at(1) = 0.0;
        dVariables.at(2) = -0.25;
        dValues.at(2) = 1.0;
        dVariables.at(3) = 0.0;
        dValues.at(3) = 1.0;
        
        return Utilities::Interp::InterExtrapolation1D(dVariables, dValues, Utilities::Interp::LIN);
    }
    
    Utilities::Interp::InterExtrapolation1D OfficialWorldGolfRankings::GetTennisDiscountCurve() const
    {
        std::vector<double> dVariables(4), dValues(4);
        dVariables.at(0) = -1.01;
        dValues.at(0) = 0.0;
        dVariables.at(1) = -1.00001;
        dValues.at(1) = 0.0;
        dVariables.at(2) = -1.0;
        dValues.at(2) = 1.0;
        dVariables.at(3) = 0.0;
        dValues.at(3) = 1.0;
        
        return Utilities::Interp::InterExtrapolation1D(dVariables, dValues, Utilities::Interp::LIN);
    }
    
    Utilities::Interp::InterExtrapolation1D OfficialWorldGolfRankings::GetDiscountCurve(DiscountType eDiscountType) const
    {
        switch (eDiscountType) {
            case TENNIS:
                return GetTennisDiscountCurve();
                break;
            case GOLF:
            case OWGR:
                return GetOWGRDiscountCurve();
                break;
                
            default:
                throw Utilities::MyException("OfficialWorldGolfRankings::GetDiscountCurve : discount curve not recognized. Must input a valid discount curve");
                break;
        }
    }
}