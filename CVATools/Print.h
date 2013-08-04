//
//  Print.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 16/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef CVATools_Print_h
#define CVATools_Print_h

#include <vector>
#include <map>

namespace Utilities
{
    class PrintC
    {
    public:
        PrintC();
        PrintC(const std::string & cFileName, const bool bAppend, const std::size_t iPrecision);
        
        virtual void PrintInFile(const std::vector<double> & dData);
        virtual void PrintInFile(const std::vector<std::pair<double, std::size_t> > & dData);
        virtual void PrintInFile(const std::vector<std::pair<double, double> > & dData);
        virtual void PrintInFile(const std::vector<std::vector<double> > & dData);
        virtual void PrintInFile(const std::map<double, std::map<double, double> > & mData);
        virtual void PrintInFile(const std::map<double, std::map<std::size_t, double> > & mData);
        virtual void PrintInFile(const std::map<double, std::map<std::size_t, std::vector<double> > > & mData, std::size_t iDim);
    protected:
        std::string cFileName_;
        bool bAppend_;
        std::string cPrecision_; // Conversion of the precision into a std::string value
    };
}
#endif
