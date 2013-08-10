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

#include <fstream>

namespace Utilities
{
    class PrintCpp
    {
    public:
        PrintCpp(const std::string & cFileName, const bool bAppend, const std::size_t iPrecision) : cFileName_(cFileName), bAppend_(bAppend)
        {}
        
        template<class C> void PrintInFile(const std::vector<C> & dData)
        {
            std::ofstream myfile;
            myfile.open(cFileName_.c_str(), bAppend_ ? std::ofstream::app : std::ofstream::out);
            for (std::vector<double>::const_iterator it = dData.begin() ; it != dData.end() ; ++it)
            {
                myfile << *it << "\n";
            }
            myfile.close();
        }
        
        template<class C, class D>
        void PrintInFile(const std::vector<std::pair<C, D> > & dData)
        {
            std::ofstream myfile;
            myfile.open(cFileName_.c_str(), bAppend_ ? std::ofstream::app : std::ofstream::out);
            for (std::size_t i = 0 ; i < dData.size() ; ++i)
            {
                myfile << dData[i].first << "," << dData[i].second << "\n";
            }
            myfile.close();
        }
        
        template<class C>
        void PrintInFile(const std::vector<std::vector<C> > & dData)
        {
            std::ofstream myfile;
            myfile.open(cFileName_.c_str(), bAppend_ ? std::ofstream::app : std::ofstream::out);
            for (std::size_t i = 0 ; i != dData.size() ; ++i)
            {
                myfile << dData[i][0] ;
                for (std::size_t j = 0 ; i < dData[i].size() ; ++j)
                {
                    myfile << "," << dData[i][j] ;
                }
                myfile << "\n";
            }
            myfile.close();
        }
        
        template<class C, class D, class E>
        void PrintInFile(const std::map<C, std::map<D, E> > & mData)
        {
            std::ofstream myfile;
            myfile.open(cFileName_.c_str(), bAppend_ ? std::ofstream::app : std::ofstream::out);
            typename std::map<C, std::map<D, E> >::const_iterator iter = mData.begin();
            for (typename std::map<D, E>::const_iterator it = iter->second.begin() ; it != iter->second.end() ; ++it)
            {
                myfile << it->first << "," ;
            }
            myfile << "\n" ;
            for ( ; iter != mData.end() ; ++iter)
            {
                myfile << iter->first << "," ;
                for (typename std::map<D, E>::const_iterator it = iter->second.begin() ; it != iter->second.end() ; ++it)
                {
                    myfile << it->second;
                }
                myfile << "\n" ;
            }
            myfile.close();
        }
        
        template<class C, class D, class E>
        void PrintInFile(const std::map<C, std::map<D, std::vector<E> > > & mData, std::size_t iDim)
        {
            std::ofstream myfile;
            myfile.open(cFileName_.c_str(), bAppend_ ? std::ofstream::app : std::ofstream::out);
            typename std::map<C, std::map<D, std::vector<E> > >::const_iterator iter = mData.begin();
            for (typename std::map<D, std::vector<E> >::const_iterator it = iter->second.begin() ; it != iter->second.end() ; ++it)
            {
                myfile << it->first << "," ;
            }
            myfile << "\n" ;
            for ( ; iter != mData.end() ; ++iter)
            {
                myfile << iter->first << "," ;
                for (typename std::map<D, std::vector<E> >::const_iterator it = iter->second.begin() ; it != iter->second.end() ; ++it)
                {
                    myfile << it->second[iDim];
                }
                myfile << "\n" ;
            }
            myfile.close();
        }
        
    protected:
        std::string cFileName_;
        bool bAppend_;
        std::size_t iPrecision_; // number of digits after the point for printing
        std::string cPrecision_; // Conversion of iPrecision_ into a std::string value
    };
}

#endif /* defined(__CVATools__Printcpp__) */
