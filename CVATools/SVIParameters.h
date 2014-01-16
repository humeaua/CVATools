//
//  SVIParameters.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/06/13.
//
//

#ifndef __CVATools__SVIParameters__
#define __CVATools__SVIParameters__

#include <iostream>
#include <map>
#include <vector>

namespace Finance
{
    namespace Volatility
    {
        class SVIParameters {
        private:
            virtual void FillStrikesAndVols(// inputs
                                            const std::map<long, std::map<double, double> > & sVolSurface,
                                            long lExpiry,
                                            //outputs
                                            std::vector<double> & dStrikes,
                                            std::vector<double> & dVols) const;
        protected:
            std::vector<double> dA_, dB_, dRho_, dM_, dSigma_;
            std::vector<double> dExpiries_;
            double dSpot_;
        public:
            SVIParameters(double dSpot);
            
            virtual double Volatility(double k, double t) const;
            virtual double Variance(double k, double t) const;
            
            virtual void Calibrate(const std::map<long, std::map<double, double> > & sVolSurface);
        };
    }
}

#endif /* defined(__CVATools__SVIParameters__) */
