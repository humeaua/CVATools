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
    static std::auto_ptr<Utilities::Interp::Interpolator> m_totalRatingTo1stPointInterpolator;
    static std::auto_ptr<std::vector<double> > m_pointComparedTo1st;
    
    // Disable Copy
    PointsSystemStaticData();
    PointsSystemStaticData(const PointsSystemStaticData &);
    PointsSystemStaticData & operator= (const PointsSystemStaticData &);
public:
    static Utilities::Interp::Interpolator & GetOWGRInterpolator();
    
    static std::vector<double> & GetEventRatingValues();
    static std::vector<double> & GetHomeRatingValues();
    
    static Utilities::Interp::Interpolator & GetTotalRatingToFirstPointInterpolator();
    
    static std::vector<double> & PointsComparedTo1st();
};

#endif /* defined(__CVATools__PointsSystemStaticData__) */
