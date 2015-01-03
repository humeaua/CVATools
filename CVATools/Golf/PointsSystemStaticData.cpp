//
//  PointsSystemStaticData.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/12/14.
//
//

#include "PointsSystemStaticData.h"

std::auto_ptr<Utilities::Interp::Interpolator> PointsSystemStaticData::m_interpolator;
std::auto_ptr<std::vector<double> > PointsSystemStaticData::m_eventRatingValues;
std::auto_ptr<std::vector<double> > PointsSystemStaticData::m_homeRatingValues;

Utilities::Interp::Interpolator & PointsSystemStaticData::GetOWGRInterpolator()
{
    if (m_interpolator.get() == NULL)
    {
        std::vector<double> variables, values;
        variables.push_back(-0.00001);
        values.push_back(0.0);
        
        variables.push_back(0.0);
        values.push_back(1.0);
        
        variables.push_back(0.25);
        values.push_back(1.0);
        
        variables.push_back(2.0);
        values.push_back(0.0);
        
        variables.push_back(2.00001);
        values.push_back(0.0);
        
        m_interpolator.reset(new Utilities::Interp::LinearInterpolator(variables, values));
    }
    return *m_interpolator;
}

std::vector<double> & PointsSystemStaticData::GetEventRatingValues()
{
    if (m_eventRatingValues.get() == NULL)
    {
        /*
         Event Rating Values
         World Event Rating Value
         1          45
         2          37
         3          32
         4          27
         5          24
         6          21
         7          20
         8          19
         9          18
         10         17
         11         16
         12         15
         13         14
         14         13
         15         12
         16-30      11
         31-34      10
         35-38      9
         39-43      8
         44-50      7
         51-55      6
         56-60      5
         61-70      4
         71-80      3
         81-100     2
         101-200	1
         */
        m_eventRatingValues.reset(new std::vector<double>());
        m_eventRatingValues->push_back(45);
        m_eventRatingValues->push_back(37);
        m_eventRatingValues->push_back(32);
        m_eventRatingValues->push_back(27);
        m_eventRatingValues->push_back(24);
        m_eventRatingValues->push_back(21);
        m_eventRatingValues->push_back(20);
        m_eventRatingValues->push_back(19);
        m_eventRatingValues->push_back(18);
        m_eventRatingValues->push_back(17);
        m_eventRatingValues->push_back(16);
        m_eventRatingValues->push_back(15);
        m_eventRatingValues->push_back(14);
        m_eventRatingValues->push_back(13);
        m_eventRatingValues->push_back(12);
        for (size_t i = 0 ; i < 15 ; ++i)
        {
            m_eventRatingValues->push_back(11);
        }
        for (size_t i = 0 ; i < 4 ; ++i)
        {
            m_eventRatingValues->push_back(10);
        }
        for (size_t i = 0 ; i < 4 ; ++i)
        {
            m_eventRatingValues->push_back(9);
        }
        for (size_t i = 0 ; i < 5 ; ++i)
        {
            m_eventRatingValues->push_back(8);
        }
        for (size_t i = 0 ; i < 7 ; ++i)
        {
            m_eventRatingValues->push_back(7);
        }
        for (size_t i = 0 ; i < 5 ; ++i)
        {
            m_eventRatingValues->push_back(6);
        }
        for (size_t i = 0 ; i < 5 ; ++i)
        {
            m_eventRatingValues->push_back(5);
        }
        for (size_t i = 0 ; i < 10 ; ++i)
        {
            m_eventRatingValues->push_back(4);
        }
        for (size_t i = 0 ; i < 10 ; ++i)
        {
            m_eventRatingValues->push_back(3);
        }
        for (size_t i = 0 ; i < 20 ; ++i)
        {
            m_eventRatingValues->push_back(2);
        }
        for (size_t i = 0 ; i < 100 ; ++i)
        {
            m_eventRatingValues->push_back(1);
        }
    }
    return *m_eventRatingValues;
}

std::vector<double> & PointsSystemStaticData::GetHomeRatingValues()
{
    if (m_homeRatingValues.get() == NULL)
    {
        m_homeRatingValues.reset(new std::vector<double>());
        /*
         Home Rating Value
         1          8
         2          7
         3          6
         4          5
         5          4
         6-15       3
         16-30      1
         */
        m_homeRatingValues->push_back(8);
        m_homeRatingValues->push_back(7);
        m_homeRatingValues->push_back(6);
        m_homeRatingValues->push_back(5);
        m_homeRatingValues->push_back(4);
        for (size_t i = 0 ; i < 10 ; ++i)
        {
            m_homeRatingValues->push_back(3);
        }
        for (size_t i = 0 ; i < 15 ; ++i)
        {
            m_homeRatingValues->push_back(1);
        }
    }
    return *m_homeRatingValues;
}