//
//  Printcpp.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 04/08/13.
//
//

#include "Printcpp.h"
#include <fstream>

namespace Utilities
{
    PrintCpp::PrintCpp()
    {}
    PrintCpp::PrintCpp(const std::string & cFileName, const bool bAppend, const std::size_t iPrecision) : cFileName_(cFileName), bAppend_(bAppend)
    {}
    
    template<class C>
    void PrintCpp::PrintInFile(const std::vector<C> & dData)
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
    void PrintCpp::PrintInFile(const std::vector<std::pair<C, D> > & dData)
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
    void PrintCpp::PrintInFile(const std::vector<std::vector<C> > & dData)
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
    void PrintCpp::PrintInFile(const std::map<C, std::map<D, E> > & mData)
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
    void PrintCpp::PrintInFile(const std::map<C, std::map<D, std::vector<E> > > & mData, std::size_t iDim)
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
}