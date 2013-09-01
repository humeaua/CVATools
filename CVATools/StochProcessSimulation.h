//
//  StochProcessSimulation.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 26/08/13.
//
//

#ifndef __CVATools__StochProcessSimulation__
#define __CVATools__StochProcessSimulation__

#include <iostream>

namespace Finance
{
    namespace Processes
    {
        class StochProcessSimulation
        {
        protected:
            bool bFloorSimulation_;
            bool bStartFromFloor_;
            bool bCapSimulation_;
            bool bStartFromCap_;
            
            double dCap_;
            double dFloor_;
            
        public:
            StochProcessSimulation();
            StochProcessSimulation(bool bFloorSimulation, bool bStartFromFloor, bool bCapSimulation, bool bStartFromCap, double dCap, double dFloor);
            
            void SetFloor(double dFloor, bool bStartFromFloor);
            void SetCap(double dCap, bool bStartFromCap);
        };
    }
}

#endif /* defined(__CVATools__StochProcessSimulation__) */
