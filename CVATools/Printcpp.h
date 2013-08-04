//
//  Printcpp.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 04/08/13.
//
//

#ifndef __CVATools__Printcpp__
#define __CVATools__Printcpp__

#include <iostream>
#include <vector>
#include <map>

namespace Utilities
{
    class PrintCpp
    {
    public:
        PrintCpp();
        PrintCpp(const std::string & cFileName, const bool bAppend, const std::size_t iPrecision);
        
        template<class C> void PrintInFile(const std::vector<C> & dData);
        
        template<class C, class D>
        void PrintInFile(const std::vector<std::pair<C, D> > & dData);
        
        template<class C>
        void PrintInFile(const std::vector<std::vector<C> > & dData);
        
        template<class C, class D, class E>
        void PrintInFile(const std::map<C, std::map<D, E> > & mData);
        
        template<class C, class D, class E>
        void PrintInFile(const std::map<C, std::map<D, std::vector<E> > > & mData, std::size_t iDim);
        
    protected:
        std::string cFileName_;
        bool bAppend_;
        std::size_t iPrecision_; // number of digits after the point for printing
        std::string cPrecision_; // Conversion of iPrecision_ into a std::string value
    };
}

#endif /* defined(__CVATools__Printcpp__) */
