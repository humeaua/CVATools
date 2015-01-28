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
std::auto_ptr<Utilities::Interp::Interpolator> PointsSystemStaticData::m_totalRatingTo1stPointInterpolator;
std::auto_ptr<OWGRVectorWrapper<double> > PointsSystemStaticData::m_pointComparedTo1st;

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

Utilities::Interp::Interpolator & PointsSystemStaticData::GetTotalRatingToFirstPointInterpolator()
{
    if (m_totalRatingTo1stPointInterpolator.get() == NULL)
    {
        std::vector<double> variables, values;
        
        variables.push_back(0);
        values.push_back(6);
        
        variables.push_back(1);
        values.push_back(7);
        
        variables.push_back(5);
        values.push_back(7);
        
        variables.push_back(6);
        values.push_back(8);
        
        variables.push_back(10);
        values.push_back(8);
        
        variables.push_back(11);
        values.push_back(9);
        
        variables.push_back(15);
        values.push_back(9);
        
        variables.push_back(16);
        values.push_back(10);
        
        variables.push_back(20);
        values.push_back(10);
        
        variables.push_back(21);
        values.push_back(11);
        
        variables.push_back(25);
        values.push_back(11);
        
        variables.push_back(26);
        values.push_back(12);
        
        variables.push_back(30);
        values.push_back(12);
        
        variables.push_back(31);
        values.push_back(13);
        
        variables.push_back(35);
        values.push_back(13);
        
        variables.push_back(36);
        values.push_back(14);
        
        variables.push_back(40);
        values.push_back(14);
        
        variables.push_back(41);
        values.push_back(15);
        
        variables.push_back(45);
        values.push_back(15);
        
        variables.push_back(46);
        values.push_back(16);
        
        variables.push_back(50);
        values.push_back(16);
        
        variables.push_back(51);
        values.push_back(17);
        
        variables.push_back(55);
        values.push_back(17);
        
        variables.push_back(56);
        values.push_back(18);
        
        variables.push_back(60);
        values.push_back(18);
        
        variables.push_back(61);
        values.push_back(19);
        
        variables.push_back(65);
        values.push_back(19);
        
        variables.push_back(66);
        values.push_back(20);
        
        variables.push_back(70);
        values.push_back(20);
        
        variables.push_back(71);
        values.push_back(21);
        
        variables.push_back(75);
        values.push_back(21);
        
        variables.push_back(76);
        values.push_back(22);
        
        variables.push_back(85);
        values.push_back(22);
        
        variables.push_back(86);
        values.push_back(23);
        
        variables.push_back(90);
        values.push_back(23);
        
        variables.push_back(91);
        values.push_back(24);
        
        variables.push_back(105);
        values.push_back(24);
        
        variables.push_back(106);
        values.push_back(26);
        
        variables.push_back(120);
        values.push_back(26);
        
        variables.push_back(121);
        values.push_back(28);
        
        variables.push_back(135);
        values.push_back(28);
        
        variables.push_back(136);
        values.push_back(30);
        
        variables.push_back(150);
        values.push_back(30);
        
        variables.push_back(151);
        values.push_back(32);
        
        variables.push_back(165);
        values.push_back(32);
        
        variables.push_back(166);
        values.push_back(34);
        
        variables.push_back(180);
        values.push_back(34);
        
        variables.push_back(181);
        values.push_back(36);
        
        variables.push_back(195);
        values.push_back(36);
        
        variables.push_back(196);
        values.push_back(38);
        
        variables.push_back(210);
        values.push_back(38);
        
        variables.push_back(211);
        values.push_back(40);
        
        variables.push_back(225);
        values.push_back(40);
        
        variables.push_back(226);
        values.push_back(42);
        
        variables.push_back(240);
        values.push_back(42);
        
        variables.push_back(241);
        values.push_back(44);
        
        variables.push_back(255);
        values.push_back(44);
        
        variables.push_back(256);
        values.push_back(46);
        
        variables.push_back(285);
        values.push_back(46);
        
        variables.push_back(286);
        values.push_back(48);
        
        variables.push_back(315);
        values.push_back(48);
        
        variables.push_back(316);
        values.push_back(50);
        
        variables.push_back(345);
        values.push_back(50);
        
        variables.push_back(346);
        values.push_back(52);
        
        variables.push_back(375);
        values.push_back(52);
        
        variables.push_back(376);
        values.push_back(54);
        
        variables.push_back(405);
        values.push_back(54);
        
        variables.push_back(406);
        values.push_back(56);
        
        variables.push_back(435);
        values.push_back(56);
        
        variables.push_back(436);
        values.push_back(58);
        
        variables.push_back(465);
        values.push_back(58);
        
        variables.push_back(466);
        values.push_back(60);
        
        variables.push_back(495);
        values.push_back(60);
        
        variables.push_back(496);
        values.push_back(62);
        
        variables.push_back(525);
        values.push_back(62);
        
        variables.push_back(526);
        values.push_back(64);
        
        variables.push_back(555);
        values.push_back(64);
        
        variables.push_back(556);
        values.push_back(66);
        
        variables.push_back(585);
        values.push_back(66);
        
        variables.push_back(586);
        values.push_back(68);
        
        variables.push_back(630);
        values.push_back(68);
        
        variables.push_back(631);
        values.push_back(70);
        
        variables.push_back(675);
        values.push_back(70);
        
        variables.push_back(676);
        values.push_back(72);
        
        variables.push_back(720);
        values.push_back(72);
        
        variables.push_back(721);
        values.push_back(74);
        
        variables.push_back(765);
        values.push_back(74);
        
        variables.push_back(766);
        values.push_back(76);
        
        variables.push_back(810);
        values.push_back(76);
        
        variables.push_back(811);
        values.push_back(78);
        
        variables.push_back(905);
        values.push_back(78);
        
        variables.push_back(906);
        values.push_back(80);
        
        variables.push_back(1000);
        values.push_back(80);
        
        m_totalRatingTo1stPointInterpolator.reset(new Utilities::Interp::LinearInterpolator(variables, values));
    }
    return *m_totalRatingTo1stPointInterpolator;
}

OWGRVectorWrapper<double> & PointsSystemStaticData::PointsComparedTo1st()
{
    if (m_pointComparedTo1st.get() == NULL)
    {
        m_pointComparedTo1st.reset(new OWGRVectorWrapper<double>());
        m_pointComparedTo1st->push_back(100);
        m_pointComparedTo1st->push_back(60);
        m_pointComparedTo1st->push_back(40);
        m_pointComparedTo1st->push_back(30);
        m_pointComparedTo1st->push_back(24);
        m_pointComparedTo1st->push_back(20);
        m_pointComparedTo1st->push_back(18);
        m_pointComparedTo1st->push_back(16);
        m_pointComparedTo1st->push_back(15);
        m_pointComparedTo1st->push_back(14);
        m_pointComparedTo1st->push_back(13);
        m_pointComparedTo1st->push_back(12);
        m_pointComparedTo1st->push_back(11);
        m_pointComparedTo1st->push_back(10);
        m_pointComparedTo1st->push_back(9.5);
        m_pointComparedTo1st->push_back(9);
        m_pointComparedTo1st->push_back(8.5);
        m_pointComparedTo1st->push_back(8);
        m_pointComparedTo1st->push_back(7.5);
        m_pointComparedTo1st->push_back(7);
        m_pointComparedTo1st->push_back(6.5);
        m_pointComparedTo1st->push_back(6);
        m_pointComparedTo1st->push_back(5.8);
        m_pointComparedTo1st->push_back(5.6);
        m_pointComparedTo1st->push_back(5.4);
        m_pointComparedTo1st->push_back(5.2);
        m_pointComparedTo1st->push_back(5);
        m_pointComparedTo1st->push_back(4.8);
        m_pointComparedTo1st->push_back(4.6);
        m_pointComparedTo1st->push_back(4.5);
        m_pointComparedTo1st->push_back(4.4);
        m_pointComparedTo1st->push_back(4.3);
        m_pointComparedTo1st->push_back(4.2);
        m_pointComparedTo1st->push_back(4.1);
        m_pointComparedTo1st->push_back(4);
        m_pointComparedTo1st->push_back(3.9);
        m_pointComparedTo1st->push_back(3.8);
        m_pointComparedTo1st->push_back(3.7);
        m_pointComparedTo1st->push_back(3.6);
        m_pointComparedTo1st->push_back(3.5);
        m_pointComparedTo1st->push_back(3.4);
        m_pointComparedTo1st->push_back(3.3);
        m_pointComparedTo1st->push_back(3.2);
        m_pointComparedTo1st->push_back(3.1);
        m_pointComparedTo1st->push_back(3);
        m_pointComparedTo1st->push_back(2.9);
        m_pointComparedTo1st->push_back(2.8);
        m_pointComparedTo1st->push_back(2.7);
        m_pointComparedTo1st->push_back(2.6);
        m_pointComparedTo1st->push_back(2.5);
        m_pointComparedTo1st->push_back(2.4);
        m_pointComparedTo1st->push_back(2.3);
        m_pointComparedTo1st->push_back(2.2);
        m_pointComparedTo1st->push_back(2.1);
        m_pointComparedTo1st->push_back(2);
        m_pointComparedTo1st->push_back(1.9);
        m_pointComparedTo1st->push_back(1.8);
        m_pointComparedTo1st->push_back(1.7);
        m_pointComparedTo1st->push_back(1.6);
        m_pointComparedTo1st->push_back(1.5);
        m_pointComparedTo1st->push_back(1.5);
        m_pointComparedTo1st->push_back(1.5);
        m_pointComparedTo1st->push_back(1.5);
        m_pointComparedTo1st->push_back(1.5);
        m_pointComparedTo1st->push_back(1.5);
    }
    return *m_pointComparedTo1st;
}