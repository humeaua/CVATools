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
public:
    static Utilities::Interp::Interpolator & GetOWGRInterpolator();
};

#endif /* defined(__CVATools__PointsSystemStaticData__) */
