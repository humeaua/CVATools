//
//  PointsSystemStaticData.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/12/14.
//
//

#ifndef __CVATools__PointsSystemStaticData__
#define __CVATools__PointsSystemStaticData__

#include <iostream>
#include "InterExtrapolation.h"

class PointsSystemStaticData
{
private:
    static std::auto_ptr<Utilities::Interp::Interpolator> m_interpolator;
    static std::auto_ptr<std::vector<double> > m_eventRatingValues;
    static std::auto_ptr<std::vector<double> > m_homeRatingValues;
public:
    static Utilities::Interp::Interpolator & GetOWGRInterpolator();
    
    static std::vector<double> & GetEventRatingValues();
    static std::vector<double> & GetHomeRatingValues();
};

#endif /* defined(__CVATools__PointsSystemStaticData__) */
