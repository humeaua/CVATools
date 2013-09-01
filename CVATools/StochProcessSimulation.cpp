//
//  StochProcessSimulation.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 26/08/13.
//
//

#include "StochProcessSimulation.h"

namespace Finance
{
    namespace Processes
    {
        StochProcessSimulation::StochProcessSimulation() : bFloorSimulation_(false), bStartFromFloor_(false), bCapSimulation_(false), bStartFromCap_(false), dCap_(std::numeric_limits<double>::infinity()), dFloor_(-std::numeric_limits<double>::infinity())
        {}
        
        StochProcessSimulation::StochProcessSimulation(bool bFloorSimulation, bool bStartFromFloor, bool bCapSimulation, bool bStartFromCap, double dCap, double dFloor) :
        bFloorSimulation_(bFloorSimulation),
        bStartFromFloor_(bStartFromFloor),
        bStartFromCap_(bStartFromCap),
        bCapSimulation_(bCapSimulation),
        dCap_(dCap),
        dFloor_(dFloor)
        {}
        
        void StochProcessSimulation::SetCap(double dCap, bool bStartFromCap)
        {
            dCap_ = dCap;
            bStartFromCap_ = bStartFromCap;
            bCapSimulation_ = true;
        }
        
        void StochProcessSimulation::SetFloor(double dFloor, bool bStartFromFloor)
        {
            dFloor_ = dFloor;
            bStartFromFloor_ = bStartFromFloor;
            bFloorSimulation_ = true;
        }
    }
}