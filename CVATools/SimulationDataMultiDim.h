//
//  SimulationDataMultiDim.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/03/13.
//
//

#ifndef CVATools_SimulationDataMultiDim_h
#define CVATools_SimulationDataMultiDim_h

#include <vector>
#include <map>
#include "Type.h"
#include "Vector.h"

namespace Utilities
{
    class SimulationDataMultiDim {
    protected:
        //        Date,             Path
        std::map<double, std::map<std::size_t, DVector > > dData_;
        
    public:
        //Default constructor
        SimulationDataMultiDim();
        
        //Overloading constructor
        SimulationDataMultiDim(const std::vector<double> & dDates, std::size_t iNPaths, std::size_t iDimension);
        
        //  Destructor
        virtual ~SimulationDataMultiDim();
        
        //  Put function
        virtual void Put(double dDate, std::size_t iPath, const Utilities::MyVector<double>& dValue);
        virtual void Put(double dDate, std::size_t iPath, std::size_t iDimension, double dValue);
        
        // Getter
        virtual std::map<double, std::map<std::size_t, DVector > > GetData() const;
        virtual Utilities::MyVector<double> GetData(double dDate, std::size_t iPath) const;
        
        //  Apply functions
        virtual void Apply(double (*func)(double));
        template<typename T>
        void Apply(const T& t)
        {
            std::map<double, std::map<std::size_t, DVector> >::iterator itDates = dData_.begin();
            for ( ; itDates != dData_.end() ; ++itDates)
            {
                std::map<std::size_t, DVector>::iterator itPaths = itDates->second.begin();
                for ( ; itPaths != itDates->second.end() ; ++itPaths)
                {
                    for (std::size_t iDim = 0 ; iDim < itPaths->second.size() ; ++iDim)
                    {
                        itPaths->second.at(iDim) = t(itPaths->second.at(iDim));
                    }
                }
            }
        }
    };
}

#endif
