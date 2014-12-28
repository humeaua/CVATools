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
#include "Vector.h"

namespace Utilities
{
    class SimulationDataMultiDim {
    protected:
        //        Date,             Path
        std::map<double, std::map<std::size_t, std::vector<double> > > dData_;
        
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
        virtual const std::map<double, std::map<std::size_t, std::vector<double> > > & GetData() const;
        virtual Utilities::MyVector<double> GetData(double dDate, std::size_t iPath) const;
        
        template<typename Functor>
        void Apply(Functor func)
        {
            std::map<double, std::map<std::size_t, std::vector<double> > >::iterator itDates = dData_.begin();
            for ( ; itDates != dData_.end() ; ++itDates)
            {
                std::map<std::size_t, std::vector<double> >::iterator itPaths = itDates->second.begin();
                for ( ; itPaths != itDates->second.end() ; ++itPaths)
                {
                    for (std::size_t iDim = 0 ; iDim < itPaths->second.size() ; ++iDim)
                    {
                        itPaths->second.at(iDim) = func(itPaths->second.at(iDim));
                    }
                }
            }
        };
    };
}

std::ostream& operator<<(std::ostream & os, const Utilities::SimulationDataMultiDim & obj);

#endif
